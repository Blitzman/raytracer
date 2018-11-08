#include <iostream>

#include <ppm_writer.hpp>

#include "vec3.hpp"
#include "ray.hpp"

Vec3<float> color(const Ray & r)
{
  Vec3<float> unit_direction_ = r.direction().unit_vector();
  float t_ = 0.5f * (unit_direction_.y() + 1.0f);
  return (1.0f - t_) * Vec3<float>(1.0f, 1.0f, 1.0f) + t_ * Vec3<float>(0.5f, 0.7f, 1.0f);
}

int main(void)
{
  int nx_ = 1920;
  int ny_ = 1080;

  PPMWriter ppm_writer_;

  std::vector<Vec3<float>> image_;

  Vec3<float> lower_left_corner_(-2.0f, -1.0f, -1.0f);
  Vec3<float> horizontal_(4.0f, 0.0f, 0.0f);
  Vec3<float> vertical_(0.0f, 2.0f, 0.0f);
  Vec3<float> origin_(0.0f, 0.0f, 0.0f);

  for (int j = ny_ - 1; j >= 0; --j)
  {
    for (int i = 0; i < nx_; ++i)
    {
      float u_ = float(i) / float(nx_);
      float v_ = float(j) / float(ny_);

      Ray ray_(origin_, lower_left_corner_ + u_ * horizontal_ + v_ * vertical_);

      Vec3<float> pixel_ = color(ray_);
      image_.push_back(pixel_);
    }
  }

  ppm_writer_.write(image_, ny_, nx_, "example.ppm");
}