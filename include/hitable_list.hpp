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

    Hitable* operator[] (const int & crIdx) const { return m_list[crIdx]; }
    Hitable*& operator[] (const int & crIdx) { return m_list[crIdx]; }

    void add(Hitable* h)
    {
      m_list.push_back(h);
    }

    HitableList slice_list(int begin, int end)
    {
      HitableList sliced_list_;

      for (int i = begin; i < end; ++i)
        sliced_list_.add(m_list[i]);

      return sliced_list_;
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

    void sort_x()
    {
      std::sort(m_list.begin(), m_list.end(), [ ]( const Hitable *a, const Hitable *b )
      {
        AABB box_left_;
        AABB box_right_;

        //std::cout << "Sorting\n";

        if (!a->bounding_box(0.0f, 0.0f, box_left_) || ! b->bounding_box(0.0f, 0.0f, box_right_))
          std::cerr << "No bounding box in BVH node constructor...\n";
      
        //std::cout << "BB\n";

        if (box_left_.min().x() - box_right_.min().x() < 0.0f)
          return -1;
        else
          return 1;
      });
    }

    void sort_y()
    {
      sort(m_list.begin( ), m_list.end( ), [ ]( const Hitable *a, const Hitable *b )
      {
        AABB box_left_;
        AABB box_right_;

        if (!a->bounding_box(0.0f, 0.0f, box_left_) || ! b->bounding_box(0.0f, 0.0f, box_right_))
          std::cerr << "No bounding box in BVH node constructor...\n";
      
        if (box_left_.min().y() - box_right_.min().y() < 0.0f)
          return -1;
        else
          return 1;
      });
    }

    void sort_z()
    {
      sort(m_list.begin( ), m_list.end( ), [ ]( const Hitable *a, const Hitable *b )
      {
        AABB box_left_;
        AABB box_right_;

        if (!a->bounding_box(0.0f, 0.0f, box_left_) || ! b->bounding_box(0.0f, 0.0f, box_right_))
          std::cerr << "No bounding box in BVH node constructor...\n";
      
        if (box_left_.min().z() - box_right_.min().z() < 0.0f)
          return -1;
        else
          return 1;
      });
    }

  private:

    std::vector<Hitable*> m_list;
};

#endif