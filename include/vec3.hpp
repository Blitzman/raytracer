#ifndef VEC3F_HPP_
#define VEC3F_HPP_

#include <cmath>
#include <iostream>

template <class T>
class Vec3
{
  public:

    Vec3() { }

    Vec3(const T & crE0, const T & crE1, const T & crE2)
    {
      m_values[0] = crE0;
      m_values[1] = crE1;
      m_values[2] = crE2;
    }

    const Vec3& operator+() const { return *this; }
    Vec3& operator-() const { return Vec3(-m_values[0], -m_values[1], -m_values[2]); }
    T operator[] (const int & crIdx) const { return m_values[crIdx]; }
    T& operator[] (const int & crIdx) { return m_values[crIdx]; }

    T x() const { return m_values[0]; }
    T y() const { return m_values[1]; }
    T z() const { return m_values[2]; }

    Vec3& operator+=(const Vec3 & v)
    {
      m_values[0] += v[0];
      m_values[1] += v[1];
      m_values[2] += v[2];
      return *this;
    }

    Vec3& operator-=(const Vec3 & v)
    {
      m_values[0] -= v[0];
      m_values[1] -= v[1];
      m_values[2] -= v[2];
      return *this;
    }

    Vec3& operator*=(const Vec3 & v)
    {
      m_values[0] *= v[0];
      m_values[1] *= v[1];
      m_values[2] *= v[2];
      return *this;
    }

    Vec3& operator/=(const Vec3 & v)
    {
      m_values[0] /= v[0];
      m_values[1] /= v[1];
      m_values[2] /= v[2];
      return *this;
    }

    Vec3& operator*=(const T & a)
    {
      m_values[0] *= a;
      m_values[1] *= a;
      m_values[2] *= a;
      return *this;
    }

    Vec3& operator/=(const T & a)
    {
      m_values[0] /= a;
      m_values[1] /= a;
      m_values[2] /= a;
    }

    friend Vec3 operator+(const Vec3 & v1, const Vec3 &v2) { return Vec3(v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]); }
    friend Vec3 operator-(const Vec3 & v1, const Vec3 &v2) { return Vec3(v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]); }
    friend Vec3 operator*(const Vec3 & v1, const Vec3 &v2) { return Vec3(v1[0]*v2[0], v1[1]*v2[1], v1[2]*v2[2]); }
    friend Vec3 operator/(const Vec3 & v1, const Vec3 &v2) { return Vec3(v1[0]/v2[0], v1[1]/v2[1], v1[2]/v2[2]); }
    friend Vec3 operator*(const Vec3 & v1, const float & t) { return Vec3(v1[0]*t, v1[1]*t, v1[2]*t); }
    friend Vec3 operator*(const T & t, const Vec3 &v1) { return Vec3(v1[0]*t, v1[1]*t, v1[2]*t); }
    friend Vec3 operator/(const Vec3 & v1, const float & t) { return Vec3(v1[0]/t, v1[1]/t, v1[2]/t); }
    friend Vec3 operator/(const T & t, const Vec3 &v1) { return Vec3(v1[0]/t, v1[1]/t, v1[2]/t); }

    T dot(const Vec3 & v1, const Vec3 & v2) { return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]; }
    Vec3 cross(const Vec3 & v1, const Vec3 & v2)
    {
      return Vec3(  (v1[1] * v2[2] - v1[2] * v2[1]),
                    (-(v1[0] * v2[2] - v1[2] * v2[0])),
                    (v1[0] * v2[1] - v1[1] * v2[0]));
    }

    float squared_length() const { return m_values[0]*m_values[0] + m_values[1]*m_values[1] + m_values[2]*m_values[2]; }

    float length() const { return sqrt(this->squared_length()); }

    void make_unit()
    {
      float k_ = 1.0 / length();
      m_values[0] *= k_;
      m_values[1] *= k_;
      m_values[2] *= k_;
    }

    Vec3 unit_vector()
    {
      return (*this) / this->length();
    }

    friend std::ostream& operator<<(std::ostream & os, const Vec3 & t)
    {
      os << t[0] < " " << t[1] << " " << t[2];
      return os;
    }

    friend std::istream& operator>>(std::istream & is, Vec3 & t)
    {
      is >> t[0] >> t[1] >> t[2];
      return is;
    }

  private:

    T m_values[3];
};

#endif