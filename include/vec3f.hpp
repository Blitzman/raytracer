#ifndef VEC3F_HPP_
#define VEC3F_HPP_

#include <cmath>
#include <iostream>

class Vec3f
{
  public:

    Vec3f()
    {

    }

    Vec3f(const float & crE0, const float & crE1, const float & crE2)
    {
      m_values[0] = crE0;
      m_values[1] = crE1;
      m_values[2] = crE2;
    }

    float operator[] (const int & crIdx) const
    {
      return m_values[crIdx];
    }

    float& operator[] (const int & crIdx)
    {
      return m_values[crIdx];
    }

  private:

    float m_values[3];
};

#endif