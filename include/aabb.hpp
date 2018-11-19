#ifndef AABB_HPP_
#define AABB_HPP_

#include "ray.hpp"
#include "vec3.hpp"

class AABB
{

  public:

    AABB()
    {

    }

    AABB(const Vec3<float> & a, const Vec3<float> & b)
    {
      m_min = a;
      m_max = b;
    }

    Vec3<float> min() const { return m_min; }
    Vec3<float> max() const { return m_max; }

    bool hit(const Ray & ray, float tMin, float tMax) const
    {
      for (int a = 0; a < 3; ++a)
      {
        float inv_d_ = 1.0f / ray.direction()[a];

        float t0_ = (m_min[a] - ray.origin()[a]) * inv_d_;
        float t1_ = (m_max[a] - ray.origin()[a]) * inv_d_;

        if (inv_d_ < 0.0f)
          std::swap(t0_, t1_);

        tMin = t0_ > tMin ? t0_ : tMin;
        tMax = t1_ < tMax ? t1_ : tMax;

        if (tMax <= tMin)
          return false;
      }

      return true;
    }

  private:

    Vec3<float> m_min;
    Vec3<float> m_max;
};

#endif