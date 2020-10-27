#include "hit.h"
#include "object.h"

vec3 Hit::Normal() const
{
    return object->Normal(location);
}
