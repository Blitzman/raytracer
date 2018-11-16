#ifndef HITABLE_HPP_
#define HITABLE_HPP_

#include "material.hpp"
#include "ray.hpp"

class Material;

struct HitRecord
{
  float t;
  Vec3<float> p;
  Vec3<float> normal;
  Material *material;
};

class Hitable
{
  public:

    virtual bool hit(const Ray & r, float tMin, float tMax, HitRecord & record) const = 0;
};

#endif