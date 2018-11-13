#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "ray.hpp"

class Camera
{
  public:

    Camera()
    {
      m_lower_left_corner = Vec3<float>(-2.0f, -1.0f, -1.0f);
      m_horizontal = Vec3<float>(4.0f, 0.0f, 0.0f);
      m_vertical = Vec3<float>(0.0f, 2.0f, 0.0f);
      m_origin = Vec3<float>(0.0f, 0.0f, 0.0f);
    }

    Ray get_ray(float u, float v)
    {
      return Ray(m_origin, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin);
    }

  private:

    Vec3<float> m_lower_left_corner;
    Vec3<float> m_horizontal;
    Vec3<float> m_vertical;
    Vec3<float> m_origin;
};

#endif