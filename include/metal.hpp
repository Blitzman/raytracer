#ifndef METAL_HPP_
#define METAL_HPP_

#include "material.hpp"
#include "utils.hpp"

class Metal : public Material
{
  public:

    Metal(const Vec3<float> & a, float f) : m_albedo(a)
    {
      if (f < 1.0f)
        m_fuzzy = f;
      else
        m_fuzzy = 1.0f;
    }

    virtual bool scatter(const Ray & rayIn, const HitRecord & record, Vec3<float> & attenuation, Ray & rayScattered) const
    {
      Vec3<float> reflected_ = reflect(rayIn.direction().unit_vector(), record.normal);
      rayScattered = Ray(record.p, reflected_ + m_fuzzy * random_in_unit_sphere());
      attenuation = m_albedo;
      return (rayScattered.direction().dot(record.normal) > 0);
    }

  private:

    Vec3<float> m_albedo;
    float m_fuzzy;
};

#endif