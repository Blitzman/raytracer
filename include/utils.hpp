#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <random>

#include "vec3.hpp"

std::random_device random_device_;
std::mt19937 generator_(random_device_());
std::uniform_real_distribution<float> distribution_(0, 1);

float random_in_0_1()
{
  return distribution_(generator_);  
}

Vec3<float> random_in_unit_sphere()
{
  Vec3<float> p_;

  do
  {
    p_ = 2.0f * Vec3<float>(distribution_(generator_), distribution_(generator_), distribution_(generator_)) - Vec3<float>(1.0f, 1.0f, 1.0f);
  } while (p_.squared_length() >= 1.0f);

  return p_;
}

#endif