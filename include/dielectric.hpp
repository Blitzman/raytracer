#ifndef DIELECTRIC_HPP_
#define DIELECTRIC_HPP_

#include "material.hpp"
#include "utils.hpp"

class Dielectric : public Material
{
  public:

    Dielectric(float ri): m_ridx(ri)
    {

    }

    virtual bool scatter(const Ray & rayIn, const HitRecord & record, Vec3<float> & attenuation, Ray & rayScattered) const
    {
        Vec3<float> outward_normal_;
        Vec3<float> reflected_ = reflect(rayIn.direction(), record.normal);

        float ni_over_nt_;

        attenuation = Vec3<float>(1.0f, 1.0f, 1.0f);
        Vec3<float> refracted_;

        float reflect_probability_;
        float cosine_;

        if (rayIn.direction().dot(record.normal) > 0 )
        {
          outward_normal_ = -1.0f * record.normal;
          ni_over_nt_ = m_ridx;
          cosine_ = m_ridx * rayIn.direction().dot(record.normal) / rayIn.direction().length();
        }
        else
        {
          outward_normal_ = record.normal;
          ni_over_nt_ = 1.0f / m_ridx;
          cosine_ = -1.0f * rayIn.direction().dot(record.normal) / rayIn.direction().length();
        }

        if (refract(rayIn.direction(), outward_normal_, ni_over_nt_, refracted_))
          reflect_probability_ = schlick(cosine_, m_ridx);
        else
          reflect_probability_ = 1.0f;

        if (random_in_0_1() < reflect_probability_)
          rayScattered = Ray(record.p, reflected_);
        else
          rayScattered = Ray(record.p, refracted_);

        return true;
    }
  
  private:

    float m_ridx;
};

#endif
