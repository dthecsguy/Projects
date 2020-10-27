#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include <algorithm>

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;

    vec3 I_a = color_ambient * world.ambient_color * world.ambient_intensity;
    vec3 I_d(0.00, 0.00, 0.00), I_s(0.00, 0.00, 00.00);

    for (Light* L : world.lights) {

        vec3 l = (L->position - intersection_point).normalized();
        vec3 l_r = (intersection_point - L->position).normalized();
        vec3 v = (world.camera.position - intersection_point).normalized();
        vec3 n = normal;
        vec3 r = ((2 * dot(n, v) * n) - v).normalized();

        vec3 L_d = L->Emitted_Light(l_r);
        vec3 R_d = color_diffuse;

        vec3 R_s = color_specular;
        vec3 L_s = L->Emitted_Light(l_r);

        vec3 temp_d = R_d * L_d * std::max(dot(l, normal), 0.00);
        vec3 temp_s = R_s * L_s * pow(std::max(dot(r, v), 0.00), specular_power);

        I_d += temp_d;
        I_s += temp_s;
    }

    color = I_a + I_d + I_s;

    return color;
}
