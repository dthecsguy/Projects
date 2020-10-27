#include "sphere.h"
#include "ray.h"
#include "hit.h"
#include <cmath>

// Determine if the ray intersects with the sphere
void Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    double a, b, c;

    a = ray.direction.magnitude_squared();
    b = 2 * dot(ray.direction, ray.endpoint - center);
    c = (ray.endpoint - center).magnitude_squared() - std::pow(radius, 2);

    double discriminant = pow(b, 2) - 4 * a * c;

    double t_0 = ((-1 * b) - (std::sqrt(discriminant))) / (2 * a);

    if (t_0 >= 0 && t_0 > small_t) {
        Hit* h_0 = new Hit();
        h_0->object = this;
        h_0->t = t_0;
        h_0->location = ray.endpoint + t_0 * ray.direction;
        h_0->ray_exiting = false;
        hits.push_back(*h_0);
    }

    double t_1 = ((-1 * b) + (std::sqrt(discriminant))) / (2 * a);

    if (t_1 >= 0 && t_1 > small_t) {
        Hit* h_1 = new Hit();
        h_1->object = this;
        h_1->t = t_1;
        h_1->location = ray.endpoint + t_1 * ray.direction;
        h_1->ray_exiting = true;
        hits.push_back(*h_1);
    }
}

vec3 Sphere::Normal(const vec3& point) const
{
    return (point - center).normalized();
}

// set this->bounding_box so that it contains the sphere as tightly as possible.
void Sphere::Update_Bounding_Box()
{
    this->bounding_box.Make_Full();
    infinite_box=false;
}

