#ifndef RAY_HPP_
#define RAY_HPP_

#include "vec3.hpp"

class Ray
{
  public:

    Ray() { }

    Ray(const Vec3<float> & a, const Vec3<float> & b, float ti = 0.0f)
    {
      m_a = a;
      m_b = b;
      m_time = ti;
    }

    Vec3<float> origin() const { return m_a; }
    Vec3<float> direction() const { return m_b; }
    float time() const { return m_time; }
    
    Vec3<float> point_at_parameter(float t) const { return m_a + m_b * t; }

  private:

    Vec3<float> m_a;
    Vec3<float> m_b;

    float m_time;
};

#endif