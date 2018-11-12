#ifndef HITABLE_LIST_HPP_
#define HITABLE_LIST_HPP_

#include "hitable.hpp"

class HitableList : public Hitable
{
  public:

    HitableList()
    {

    }

    HitableList(Hitable **l, int n)
    {
      m_list = l;
      m_list_size = n;
    }

    virtual bool hit(const Ray & r, float tMin, float tMax, HitRecord & record) const
    {
      HitRecord temp_record_;
      bool hit_anything_ = false;
      double closest_so_far_ = tMax;

      for (int i = 0; i < m_list_size; ++i)
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

    Hitable ** m_list;
    int m_list_size;
};

#endif