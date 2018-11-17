#include <iostream>
#include <limits>


#include "camera.hpp"
#include "hitable_list.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "ppm_writer.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "vec3.hpp"

Vec3<float> color(const Ray & r, Hitable * world, int depth)
{
  HitRecord record_;

  if (world->hit(r, 0.0001f, std::numeric_limits<float>::max(), record_))
  {
    Ray scattered_;
    Vec3<float> attenuation_;

    if (depth < 50 && record_.material->scatter(r, record_, attenuation_, scattered_))
    {
      return attenuation_ * color(scattered_, world, depth + 1);
    }
    else
    {
      return Vec3<float>(0.0f, 0.0f, 0.0f);
    }
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
  int nx_ = 800;
  int ny_ = 400;
  int ns_ = 128;

  PPMWriter ppm_writer_;

  std::vector<Vec3<float>> image_;

  Vec3<float> lower_left_corner_(-2.0f, -1.0f, -1.0f);
  Vec3<float> horizontal_(4.0f, 0.0f, 0.0f);
  Vec3<float> vertical_(0.0f, 2.0f, 0.0f);
  Vec3<float> origin_(0.0f, 0.0f, 0.0f);

  Hitable *list_[4];
  list_[0] = new Sphere(Vec3<float>(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(Vec3<float>(0.8f, 0.3f, 0.3f)));
  list_[1] = new Sphere(Vec3<float>(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(Vec3<float>(0.8f, 0.8f, 0.0f)));
  list_[2] = new Sphere(Vec3<float>(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3<float>(0.8f, 0.6f, 0.2f), 0.3f));
  list_[3] = new Sphere(Vec3<float>(-1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3<float>(0.8f, 0.8f, 0.8f), 1.0f));
  Hitable *world_ = new HitableList(list_, 4);

  Camera camera_;

  for (int j = ny_ - 1; j >= 0; --j)
  {
    for (int i = 0; i < nx_; ++i)
    {
      Vec3<float> pixel_(0.0f, 0.0f, 0.0f);

      for (int s = 0; s < ns_; ++s)
      {
        float u_ = float(i + random_in_0_1()) / float(nx_);
        float v_ = float(j + random_in_0_1()) / float(ny_);

        Ray ray_ = camera_.get_ray(u_, v_);
        Vec3<float> p_ = ray_.point_at_parameter(2.0f);
        pixel_ += color(ray_, world_, 0);
      }

      pixel_ /= float(ns_);
      
      // Gamma squared
      pixel_ = Vec3<float>(sqrt(pixel_[0]), sqrt(pixel_[1]), sqrt(pixel_[2]));
      image_.push_back(pixel_);
    }
  }

  ppm_writer_.write(image_, ny_, nx_, "example.ppm");
}