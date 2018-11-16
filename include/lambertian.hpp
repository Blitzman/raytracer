#ifndef LAMBERTIAN_HPP_
#define LAMBERTIAN_HPP_

#include "material.hpp"
#include "utils.hpp"

class Lambertian: public Material
{
  public:

    Lambertian(const Vec3<float> & a): m_albedo(a) { }

    virtual bool scatter(const Ray & rayIn, const HitRecord & record, Vec3<float> & attenuation, Ray & rayScattered) const
    {
      Vec3<float> target_ = record.p + record.normal + random_in_unit_sphere();
      rayScattered = Ray(record.p, target_ - record.p);
      attenuation = m_albedo;
      return true;
    }

  private:

    Vec3<float> m_albedo;
};

#endif