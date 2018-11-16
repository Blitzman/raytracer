#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "hitable.hpp"

class Sphere : public Hitable
{
  public:

    Sphere()
    {

    }

    Sphere(Vec3<float> center, float radius, Material * material) : m_center(center), m_radius(radius), m_material(material)
    {

    }

    virtual bool hit(const Ray & r, float tMin, float tMax, HitRecord & record) const
    {
      Vec3<float> oc_ = r.origin() - m_center;

      float a_ = r.direction().dot(r.direction());
      float b_ = oc_.dot(r.direction());
      float c_ = oc_.dot(oc_) - m_radius * m_radius;

      float discriminant_ = b_ * b_ - a_ * c_;

      if (discriminant_ > 0)
      {
        float temp_ = (-b_ - sqrt(b_ * b_ - a_ * c_)) / a_;
        
        if (temp_ < tMax && temp_ > tMin)
        {
          record.t = temp_;
          record.p = r.point_at_parameter(record.t);
          record.normal = (record.p - m_center) / m_radius;
          record.material = m_material;
          return true;
        }

        temp_ = (-b_ + sqrt(b_ * b_ - a_ * c_)) / a_;

        if (temp_ < tMax && temp_ > tMin)
        {
          record.t = temp_;
          record.p = r.point_at_parameter(record.t);
          record.normal = (record.p - m_center) / m_radius;
          record.material = m_material;
          return true;
        }
      }

      return false;
    }

  private:

    Vec3<float> m_center;
    float m_radius;
    Material *m_material;
};

#endif