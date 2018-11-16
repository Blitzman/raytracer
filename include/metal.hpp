#ifndef METAL_HPP_
#define METAL_HPP_

#include "material.hpp"
#include "utils.hpp"

class Metal : public Material
{
  public:

    Metal(const Vec3<float> & a): m_albedo(a) { }

    virtual bool scatter(const Ray & rayIn, const HitRecord & record, Vec3<float> & attenuation, Ray & rayScattered) const
    {
      Vec3<float> reflected_ = reflect(rayIn.direction().unit_vector(), record.normal);
      rayScattered = Ray(record.p, reflected_);
      attenuation = m_albedo;
      return (rayScattered.direction().dot(record.normal) > 0);
    }

  private:

    Vec3<float> m_albedo;

    Vec3<float> reflect(const Vec3<float> & v, const Vec3<float> & n) const
    {
      return v - 2 * v.dot(n) * n;
    }
};

#endif