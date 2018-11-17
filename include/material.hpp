#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "hitable.hpp"
#include "ray.hpp"

struct HitRecord;

class Material
{
  public:

    virtual bool scatter(const Ray & rayIn, const HitRecord & record, Vec3<float> & attenuation, Ray & rayScattered) const = 0;

    Vec3<float> reflect(const Vec3<float> & v, const Vec3<float> & n) const
    {
      return v - 2 * v.dot(n) * n;
    }

    bool refract(const Vec3<float> & v, const Vec3<float> & n, float niOverNt, Vec3<float> & refracted) const
    {
      Vec3<float> uv_ = v.unit_vector();

      float dt_ = uv_.dot(n);
      float discriminant_ = 1.0f - niOverNt * niOverNt * (1.0f - dt_ * dt_);

      if (discriminant_ > 0.0f)
      {
        refracted = niOverNt * (uv_ - n * dt_) - n * sqrt(discriminant_);
        return true;
      }
      else
      {
        return false;
      }
    }

    float schlick(float cosine, float ridx) const
    {
      float r0_ = (1.0f - ridx) / (1.0f + ridx);
      r0_ *= r0_;

      return r0_ + (1.0f - r0_) * pow((1.0f - cosine), 5.0f);
    }
};

#endif