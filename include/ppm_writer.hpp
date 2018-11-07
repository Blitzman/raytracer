#ifndef PPM_WRITER_HPP
#define PPM_WRITER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <vec3f.hpp>

class PPMWriter
{
  public:

    void write(const std::vector<Vec3f> & crColors, const int & crRows, const int & crCols, const std::string & crFilename)
    {
      std::ofstream f_(crFilename);

      if (f_.is_open())
      {
        f_ << "P3\n" << crCols << " " << crRows << "\n255\n";
        
        for (int j = crRows - 1; j >= 0; --j)
        {
          for (int i = 0; i < crCols; ++i)
          {
            int idx_ = j * crCols + i;

            int ir_ = int(255.99 * crColors[idx_][0]);
            int ig_ = int(255.99 * crColors[idx_][1]);
            int ib_ = int(255.99 * crColors[idx_][2]);

            f_ << ir_ << " " << ig_ << " " << ib_ << "\n";
          }
        }

        f_.close();
      }
      else
      {
        std::cerr << "ERROR: Unable to open file " << crFilename << "\n";
      }
    }
};

#endif