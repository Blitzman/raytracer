#ifndef HITABLE_HPP_
#define HITABLE_HPP_

#include "aabb.hpp"
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
    virtual bool bounding_box(float t0, float t1, AABB & box) const = 0;

  protected:

    AABB surrounding_box(const AABB & box0, const AABB & box1) const
    {
      Vec3<float> a_(fmin(box0.min().x(), box1.min().x()),
                      fmin(box0.min().y(), box1.min().y()),
                      fmin(box0.min().z(), box1.min().z()));

      Vec3<float> b_(fmax(box0.max().x(), box1.max().x()),
                      fmax(box0.max().y(), box1.max().y()),
                      fmax(box0.max().z(), box1.max().z()));

      return AABB(a_, b_);         
    }
};

#endif