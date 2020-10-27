#include "plane.h"
#include "ray.h"
#include <cfloat>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
void Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{

    double num = dot((x1 - ray.endpoint), normal);
    double den = dot(ray.direction, normal);

    if (den > 0)
        return;
    else {
        double t_0 = num / den;

        if (t_0 >= 0 && t_0 > small_t) {
            Hit* h_0 = new Hit();
            h_0->object = this;
            h_0->t = t_0;
            h_0->location = ray.endpoint + t_0 * ray.direction;
            h_0->ray_exiting = false;
            hits.push_back(*h_0);

            Hit* h_1 = new Hit();
            h_1->object = this;
            h_1->t = t_0;
            h_1->location = ray.endpoint + t_0 * ray.direction;
            h_1->ray_exiting = true;
            hits.push_back(*h_1);
        }

    }
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}

void Plane::Update_Bounding_Box()
{
    bounding_box.Make_Full();
    infinite_box=true;
}

