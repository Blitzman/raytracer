#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "ray.hpp"

class Camera
{
  public:

    Camera(Vec3<float> lookFrom, Vec3<float> lookAt, Vec3<float> up, float vfov, float aspect)
    {
      Vec3<float> u_, v_, w_;

      // Convert vertical FoV in degres to radians
      float theta_ = vfov * M_PI / 180.0f;

      float half_height_ = tan(theta_ / 2.0f);
      float half_width_ = aspect * half_height_;

      m_origin = lookFrom;

      w_ = (lookFrom - lookAt).unit_vector();
      u_ = up.cross(w_).unit_vector();
      v_ = w_.cross(u_);

      m_lower_left_corner = Vec3<float>(-half_width_, -half_height_, -1.0f);
      m_lower_left_corner = m_origin - half_width_ * u_ - half_height_ * v_ - w_;
      m_horizontal = 2.0f * half_width_ * u_;
      m_vertical = 2.0f * half_height_ * v_;
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