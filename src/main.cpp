#include <iostream>
#include <limits>


#include "bvh_node.hpp"
#include "camera.hpp"
#include "dielectric.hpp"
#include "hitable_list.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "ppm_writer.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "utils.hpp"
#include "vec3.hpp"

/* Hitable * random_world(int n)
{
  Hitable ** list_ = new Hitable*[n+1];

  list_[0] = new Sphere(Vec3<float>(0.0f, -1000.0f, 0.0f), 1000.0f, new Lambertian(Vec3<float>(0.5f, 0.5f, 0.5f)));

  int i = 1;

  for (int a = -11; a < 11; ++a)
  {
    for (int b = -11; b < 11; ++b)
    {
      float choose_mat_ = random_in_0_1();

      Vec3<float> center_(a + 0.9f * random_in_0_1(), 0.2f, b + 0.9 * random_in_0_1());

      if ((center_ - Vec3<float>(4.0f, 0.2f, 0.0f)).length() > 0.9f)
      {
        if (choose_mat_ < 0.8f)
        {
          list_[i++] = new Sphere(center_, 0.2f, new Lambertian(Vec3<float>(random_in_0_1() * random_in_0_1(),
                                                                            random_in_0_1() * random_in_0_1(),
                                                                            random_in_0_1() * random_in_0_1())));
        }
        else if (choose_mat_ < 0.95f)
        {
          list_[i++] = new Sphere(center_, 0.2f, new Metal(Vec3<float>(0.5f * (1.0f + random_in_0_1()),
                                                                      0.5f * (1.0f + random_in_0_1()),
                                                                      0.5f * (1.0f + random_in_0_1())),
                                                            0.5f * random_in_0_1()));
        }
        else
        {
          list_[i++] = new Sphere(center_, 0.2f, new Dielectric(1.5f));
        }
      }
    }
  }

  list_[i++] = new Sphere(Vec3<float>(0.0f, 1.0f, 0.0f), 1.0f, new Dielectric(1.5f));
  list_[i++] = new Sphere(Vec3<float>(-4.0f, 1.0f, 0.0f), 1.0f, new Lambertian(Vec3<float>(0.4f, 0.2f, 0.1f)));
  list_[i++] = new Sphere(Vec3<float>(4.0f, 1.0f, 0.0f), 1.0f, new Metal(Vec3<float>(0.7f, 0.6f, 0.5f), 0.0f));

  return new HitableList(list_, i);
} */

Vec3<float> color(const Ray & r, HitableList world, int depth)
{
  HitRecord record_;

  if (world.hit(r, 0.0001f, std::numeric_limits<float>::max(), record_))
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
  int ny_ = 800;
  int ns_ = 50;

  PPMWriter ppm_writer_;

  std::vector<Vec3<float>> image_;

  Hitable* sphere1_ = new Sphere(Vec3<float>(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(Vec3<float>(0.9f, 0.9f, 0.9f)));
  Hitable* sphere2_ = new Sphere(Vec3<float>(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(Vec3<float>(0.8f, 0.8f, 0.0f)));
  Hitable* sphere3_ = new Sphere(Vec3<float>(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vec3<float>(0.8f, 0.6f, 0.2f), 0.3f));
  Hitable* sphere4_ = new Sphere(Vec3<float>(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5f));
  Hitable* sphere5_ = new Sphere(Vec3<float>(-1.0f, 0.0f, -1.0f), -0.48f, new Dielectric(1.5f));

  HitableList spheres_;
  for (int i = 0; i < 10; ++i)
  {
    Hitable* sphere_x_ = new Sphere(Vec3<float>((random_in_0_1() - 0.5f) * 10.0f, 0.0f, (random_in_0_1() - 0.5f)* 10.0f), 0.5f, new Lambertian(Vec3<float>(0.9f, 0.9f, 0.9f)));
    spheres_.add(sphere_x_);
  }

  std::cout << "Added 100 spheres...\n";

  spheres_.add(sphere1_);
  spheres_.add(sphere2_);
  spheres_.add(sphere3_);
  spheres_.add(sphere4_);
  spheres_.add(sphere5_);
  //BVHNode* bvh_node_ = new BVHNode(spheres_, 105, 0.0f, 1.0f);
  //HitableList world_;
  //world_.add((Hitable *)bvh_node_);

  Vec3<float> look_from_(-0.5f, 0.5f, 2.5f);
  Vec3<float> look_at_(-0.1f, 0.0f, 0.0f);
  float fov_ = 60.0f;
  float aspect_ = float(nx_) / float(ny_);
  float dist_to_focus_ = 4.0f;
  float aperture_ = 0.1f;
  Camera camera_(look_from_, look_at_, Vec3<float>(0.0f, 1.0f, 0.0f), fov_, aspect_, aperture_, dist_to_focus_, 0.0f, 1.0f);

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
        pixel_ += color(ray_, spheres_, 0);
      }

      pixel_ /= float(ns_);
      
      // Gamma squared
      pixel_ = Vec3<float>(sqrt(pixel_[0]), sqrt(pixel_[1]), sqrt(pixel_[2]));
      image_.push_back(pixel_);
    }
  }

  ppm_writer_.write(image_, ny_, nx_, "example.ppm");
}