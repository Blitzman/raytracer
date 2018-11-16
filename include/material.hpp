#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "hitable.hpp"
#include "ray.hpp"

struct HitRecord;

class Material
{
  public:

    virtual bool scatter(const Ray & rayIn, const HitRecord & record, Vec3<float> & attenuation, Ray & rayScattered) const = 0;
};

#endif