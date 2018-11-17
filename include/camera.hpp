#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "ray.hpp"
#include "utils.hpp"

class Camera
{
  public:

    Camera(Vec3<float> lookFrom, Vec3<float> lookAt, Vec3<float> up, float vfov, float aspect, float aperture, float focusDistance)
    {
      m_lens_radius = aperture / 2.0f;

      // Convert vertical FoV in degres to radians
      float theta_ = vfov * M_PI / 180.0f;

      float half_height_ = tan(theta_ / 2.0f);
      float half_width_ = aspect * half_height_;

      m_origin = lookFrom;

      m_w = (lookFrom - lookAt).unit_vector();
      m_u = up.cross(m_w).unit_vector();
      m_v = m_w.cross(m_u);

      m_lower_left_corner = m_origin - half_width_ * focusDistance * m_u - half_height_ * focusDistance * m_v - focusDistance * m_w;
      m_horizontal = 2.0f * half_width_ * focusDistance * m_u;
      m_vertical = 2.0f * half_height_ * focusDistance * m_v;
    }

    Ray get_ray(float s, float t)
    {
      Vec3<float> rd_ = m_lens_radius * random_in_unit_disk();
      Vec3<float> offset_ = m_u * rd_.x() + m_v * rd_.y();
      return Ray(m_origin + offset_, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin - offset_);
    }

  private:

    Vec3<float> m_lower_left_corner;
    Vec3<float> m_horizontal;
    Vec3<float> m_vertical;
    Vec3<float> m_origin;
    Vec3<float> m_u, m_v, m_w;

    float m_lens_radius;
};

#endif