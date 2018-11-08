#ifndef RAY_HPP_
#define RAY_HPP_

#include "vec3.hpp"

class Ray
{
  public:

    Ray() { }

    Ray(const Vec3<float> & a, const Vec3<float> & b)
    {
      m_a = a;
      m_b = b; 
    }

    Vec3<float> origin() const { return m_a; }
    Vec3<float> direction() const { return m_b; }
    Vec3<float> point_at_parameter(const float & t) const { return m_a + m_b * t; }

  private:

    Vec3<float> m_a;
    Vec3<float> m_b;
};

#endif