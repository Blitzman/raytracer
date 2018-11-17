#ifndef HITABLE_LIST_HPP_
#define HITABLE_LIST_HPP_

#include <vector>

#include "hitable.hpp"

class HitableList : public Hitable
{
  public:

    HitableList()
    {

    }

    void add(Hitable* h)
    {
      m_list.push_back(h);
    }

    virtual bool hit(const Ray & r, float tMin, float tMax, HitRecord & record) const
    {
      HitRecord temp_record_;
      bool hit_anything_ = false;
      double closest_so_far_ = tMax;

      for (int i = 0; i < m_list.size(); ++i)
      {
        if (m_list[i]->hit(r, tMin, closest_so_far_, temp_record_))
        {
          hit_anything_ = true;
          closest_so_far_ = temp_record_.t;
          record = temp_record_;
        }
      }

      return hit_anything_;
    }

  private:

    std::vector<Hitable*> m_list;
};

#endif