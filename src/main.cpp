#include <iostream>
#include <limits>

#include <ppm_writer.hpp>

#include "vec3.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "ray.hpp"

Vec3<float> color(const Ray & r, Hitable * world)
{
  HitRecord record_;

  if (world->hit(r, 0.0, std::numeric_limits<float>::max(), record_))
  {
    return 0.5f * Vec3<float>(record_.normal.x() + 1.0f, record_.normal.y() + 1.0f, record_.normal.z() + 1.0f);
  }
  else
  {
    Vec3<float> unit_direction_ = r.direction().unit_vector();
    float t_ = 0.5f * (unit_direction_.y() + 1.0f);
    return (1.0f - t_) * Vec3<float>(1.0f, 1.0f, 1.0f) + t_ * Vec3<float>(0.5f, 0.7f, 1.0f);
  }
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

  Hitable *list_[4];
  list_[0] = new Sphere(Vec3<float>(0.0f, 0.0f, -1.0f), 0.5f);
  list_[1] = new Sphere(Vec3<float>(0.0f, -100.5f, -1.0f), 100.0f);
  list_[2] = new Sphere(Vec3<float>(1.75f, 0.5f, -1.5f), 0.4f);
  list_[3] = new Sphere(Vec3<float>(-1.75f, 0.5f, -1.5f), 0.4f);
  Hitable *world_ = new HitableList(list_, 4);

  for (int j = ny_ - 1; j >= 0; --j)
  {
    for (int i = 0; i < nx_; ++i)
    {
      float u_ = float(i) / float(nx_);
      float v_ = float(j) / float(ny_);

      Ray ray_(origin_, lower_left_corner_ + u_ * horizontal_ + v_ * vertical_);
      Vec3<float> p_ = ray_.point_at_parameter(2.0f);

      Vec3<float> pixel_ = color(ray_, world_);
      image_.push_back(pixel_);
    }
  }

  ppm_writer_.write(image_, ny_, nx_, "example.ppm");
}