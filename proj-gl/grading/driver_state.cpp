#include "driver_state.h"
#include <cstring>

driver_state::driver_state()
{
}

driver_state::~driver_state()
{
    delete [] image_color;
    delete [] image_depth;
}

// This function should allocate and initialize the arrays that store color and
// depth.  This is not done during the constructor since the width and height
// are not known when this class is constructed.
void initialize_render(driver_state& state, int width, int height)
{
    state.image_width=width;
    state.image_height=height;
    state.image_color = new pixel[width * height];
    state.image_depth = new float[width * height];

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            state.image_color[row * width + col] = make_pixel(0, 0, 0);
            state.image_depth[row * width + col] = 1;
        }
    } 
}

// This function will be called to render the data that has been stored in this class.
// Valid values of type are:
//   render_type::triangle - Each group of three vertices corresponds to a triangle.
//   render_type::indexed -  Each group of three indices in index_data corresponds
//                           to a triangle.  These numbers are indices into vertex_data.
//   render_type::fan -      The vertices are to be interpreted as a triangle fan.
//   render_type::strip -    The vertices are to be interpreted as a triangle strip.
void render(driver_state& state, render_type type)
{
    data_geometry* dg_objects = new data_geometry[state.num_vertices];

    for (int i = 0; i < state.num_vertices; i++) {
        dg_objects[i].data = &state.vertex_data[i * state.floats_per_vertex];

    }

    for (int i = 0; i < state.num_vertices; i++) {
        data_vertex dv;

        dv.data = &state.vertex_data[i * state.floats_per_vertex];
        state.vertex_shader(dv, dg_objects[i], state.uniform_data);
    }

    switch (type)
    {
    case render_type::invalid:
        break;
    case render_type::indexed:
        break;
    case render_type::triangle:
        for (int i = 0; i < state.num_vertices; i += 3) {
            clip_triangle(state, dg_objects[i], dg_objects[i + 1], dg_objects[i + 2]);
        }
        break;
    case render_type::fan:
        break;
    case render_type::strip:
        break;
    default:
        break;
    }

    delete[] dg_objects;
}


// This function clips a triangle (defined by the three vertices in the "in" array).
// It will be called recursively, once for each clipping face (face=0, 1, ..., 5) to
// clip against each of the clipping faces in turn.  When face=6, clip_triangle should
// simply pass the call on to rasterize_triangle.
void clip_triangle(driver_state& state, const data_geometry& v0,
    const data_geometry& v1, const data_geometry& v2,int face)
{
    if(face==6)
    {
        rasterize_triangle(state, v0, v1, v2);
        return;
    }

    clip_triangle(state,v0,v1,v2,face+1);
}

// Rasterize the triangle defined by the three vertices in the "in" array.  This
// function is responsible for rasterization, interpolation of data to
// fragments, calling the fragment shader, and z-buffering.
void rasterize_triangle(driver_state& state, const data_geometry& v0,
    const data_geometry& v1, const data_geometry& v2)
{
    data_geometry triangle[] = { v0, v1, v2 };

    float A_i = (triangle[0].gl_Position[0] / triangle[0].gl_Position[3] + 1) / 2 * state.image_width;
    float A_j = (triangle[0].gl_Position[1] / triangle[0].gl_Position[3] + 1) / 2 * state.image_height;

    float B_i = (triangle[1].gl_Position[0] / triangle[1].gl_Position[3] + 1) / 2 * state.image_width;
    float B_j = (triangle[1].gl_Position[1] / triangle[1].gl_Position[3] + 1) / 2 * state.image_height;

    float C_i = (triangle[2].gl_Position[0] / triangle[2].gl_Position[3] + 1) / 2 * state.image_width;
    float C_j = (triangle[2].gl_Position[1] / triangle[2].gl_Position[3] + 1) / 2 * state.image_height;

    

    float a[2] = { A_i, A_j };
    float b[2] = { B_i, B_j };
    float c[2] = { C_i, C_j };


    for (int row = 0; row < state.image_height; row++) {
        for (int col = 0; col < state.image_width; col++) {
            float P[2] = { col, row };

            float alpha = getArea(P, b, c) / getArea(a, b, c);
            float beta = getArea(a, P, c) / getArea(a, b, c);
            float gamma = getArea(a, b, P) / getArea(a, b, c);

            data_fragment df;
            df.data = new float[MAX_FLOATS_PER_VERTEX];

            data_output dout;

            if (alpha >= 0 && beta >= 0 && gamma >= 0) {
                for (int i = 0; i < MAX_FLOATS_PER_VERTEX; i++) {
                    switch (state.interp_rules[i]) {
                        case interp_type::flat: {

                            df.data[i] = v0.data[i];
                            break;
                        }
                        

                        case interp_type::smooth: {
                            break; 
                        }
                        

                        case interp_type::noperspective: {

                            df.data[i] = alpha * v0.data[i] + beta * v1.data[i] + gamma * v2.data[i];
                            break;

                        }
                        case interp_type::invalid:
                            break;

                        }
                }

                state.fragment_shader(df, dout, state.uniform_data);
                state.image_color[row * state.image_width + col] = make_pixel(dout.output_color[0] * 255, dout.output_color[1] * 255, dout.output_color[2] * 255);
            }
           
        }
    }

}

float getArea(float* A, float* B, float* C) {
    return 0.5 * ((B[0] * C[1] - C[0] * B[1]) + (C[0] * A[1] - A[0]*C[1]) + (A[0] * B[1] - A[1] * B[0]));
}

