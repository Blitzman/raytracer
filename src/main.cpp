#include <iostream>

#include <ppm_writer.hpp>

#include <vec3f.hpp>

int main(void)
{
  int nx_ = 1920;
  int ny_ = 1080;

  PPMWriter ppm_writer_;

  std::vector<Vec3f> image_;

  for (int j = ny_ - 1; j >= 0; --j)
  {
    for (int i = 0; i < nx_; ++i)
    {
      float r_ = float(i) / float(nx_);
      float g_ = float(j) / float(ny_);
      float b_ = 0.2f;

      Vec3f pixel_(r_, g_, b_);
      image_.push_back(pixel_);
    }
  }

  ppm_writer_.write(image_, ny_, nx_, "example.ppm");
}