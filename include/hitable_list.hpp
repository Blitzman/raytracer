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

    virtual bool bounding_box(float t0, float t1, AABB & box) const
    {
      if (m_list.size() < 1)
        return false;

      AABB temp_box_;

      bool first_true_ = m_list[0]->bounding_box(t0, t1, temp_box_);

      if (!first_true_)
        return false;

      box = temp_box_;

      for (int i = 1; i < m_list.size(); ++i)
      {
        if (m_list[0]->bounding_box(t0, t1, temp_box_))
          box = surrounding_box(box, temp_box_);
        else
          return false;
      }

      return true;
    }

  private:

    std::vector<Hitable*> m_list;
};

#endif