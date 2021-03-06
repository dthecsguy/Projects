#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include <climits>
#include "light.h"
#include "ray.h"


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{
    double t_hat = INT_MAX;
    Object* o_hat = nullptr;

    for (Object* o : objects) {
        std::vector<Hit> hits;
        o->Intersection(ray, hits);
        if (hits.size() > 0) {
            if (hits[hits.size() - 2].t < t_hat) {
                t_hat = hits[hits.size() - 2].t;
                o_hat = o;
                hit = hits[hits.size() - 2];
            }
        }
    }
    return o_hat;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{

    // set up the initial view ray here
    Ray* ray = new Ray();
    ray->endpoint = camera.position;

    vec3 pixel_position = camera.World_Position(pixel_index);

    vec3 the_vec = pixel_position - ray->endpoint;

    ray->direction = the_vec.normalized();

    vec3 color=Cast_Ray(*ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render(){
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray, int recursion_depth)
{
    vec3 color;
    Hit* h = new Hit();

    Object* o = Closest_Intersection(ray, *h);

    color = (o == nullptr) ? background_shader->Shade_Surface(ray, ray.direction, cross(camera.horizontal_vector, camera.vertical_vector), recursion_depth) : o->material_shader->Shade_Surface(ray, h->location, h->Normal(), recursion_depth);

    if (debug_pixel) {
        std::cout << "cast ray: " << "end = " << ray.endpoint << std::endl;
        std::cout << "dir = " << ray.direction << std::endl;
        std::cout << color << std::endl;
    }

    return color;
}
