#include <iostream>
#include <limits>

#include <random>

#include "camera.hpp"
#include "hitable_list.hpp"
#include "ppm_writer.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

std::random_device random_device_;
std::mt19937 generator_(random_device_());
std::uniform_real_distribution<float> distribution_(0, 1);


Vec3<float> random_in_unit_sphere()
{
  Vec3<float> p_;

  do
  {
    p_ = 2.0f * Vec3<float>(distribution_(generator_), distribution_(generator_), distribution_(generator_)) - Vec3<float>(1.0f, 1.0f, 1.0f);
  } while (p_.squared_length() >= 1.0f);

  return p_;
}

Vec3<float> color(const Ray & r, Hitable * world)
{
  HitRecord record_;

  if (world->hit(r, 0.0001f, std::numeric_limits<float>::max(), record_))
  {
    Vec3<float> target_ = record_.p + record_.normal + random_in_unit_sphere();
    return 0.5f * color(Ray(record_.p, target_ - record_.p), world);
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
  int nx_ = 200;
  int ny_ = 100;
  int ns_ = 256;

  PPMWriter ppm_writer_;

  std::vector<Vec3<float>> image_;

  Vec3<float> lower_left_corner_(-2.0f, -1.0f, -1.0f);
  Vec3<float> horizontal_(4.0f, 0.0f, 0.0f);
  Vec3<float> vertical_(0.0f, 2.0f, 0.0f);
  Vec3<float> origin_(0.0f, 0.0f, 0.0f);

  Hitable *list_[2];
  list_[0] = new Sphere(Vec3<float>(0.0f, 0.0f, -1.0f), 0.5f);
  list_[1] = new Sphere(Vec3<float>(0.0f, -100.5f, -1.0f), 100.0f);
  Hitable *world_ = new HitableList(list_, 2);

  Camera camera_;

  for (int j = ny_ - 1; j >= 0; --j)
  {
    for (int i = 0; i < nx_; ++i)
    {
      Vec3<float> pixel_(0.0f, 0.0f, 0.0f);

      for (int s = 0; s < ns_; ++s)
      {
        float u_ = float(i + distribution_(generator_)) / float(nx_);
        float v_ = float(j + distribution_(generator_)) / float(ny_);

        Ray ray_ = camera_.get_ray(u_, v_);
        Vec3<float> p_ = ray_.point_at_parameter(2.0f);
        pixel_ += color(ray_, world_);
      }

      pixel_ /= float(ns_);
      
      // Gamma squared
      pixel_ = Vec3<float>(sqrt(pixel_[0]), sqrt(pixel_[1]), sqrt(pixel_[2]));
      image_.push_back(pixel_);
    }
  }

  ppm_writer_.write(image_, ny_, nx_, "example.ppm");
}