#ifndef HITABLE_HPP_
#define HITABLE_HPP_

#include "ray.hpp"

struct HitRecord
{
  float t;
  Vec3<float> p;
  Vec3<float> normal;
};

class Hitable
{
  public:

    virtual bool hit(const Ray & r, float tMin, float tMax, HitRecord & record) const = 0;
};

#endif