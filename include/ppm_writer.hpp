#ifndef PPM_WRITER_HPP
#define PPM_WRITER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <vec3.hpp>

class PPMWriter
{
  public:

    void write(const std::vector<Vec3<float>> & colors, int rows, int cols, std::string filename)
    {
      std::ofstream f_(filename);

      if (f_.is_open())
      {
        f_ << "P3\n" << cols << " " << rows << "\n255\n";
        
        for (int j = 0; j < rows; ++j)
        {
          for (int i = 0; i < cols; ++i)
          {
            int idx_ = j * cols + i;

            int ir_ = int(255.99 * colors[idx_][0]);
            int ig_ = int(255.99 * colors[idx_][1]);
            int ib_ = int(255.99 * colors[idx_][2]);

            f_ << ir_ << " " << ig_ << " " << ib_ << "\n";
          }
        }

        f_.close();
      }
      else
      {
        std::cerr << "ERROR: Unable to open file " << filename << "\n";
      }
    }
};

#endif