#ifndef BVH_NODE_HPP_
#define BVH_NODE_HPP_

#include "hitable.hpp"
#include "utils.hpp"

class BVHNode : public Hitable
{
  public:

    BVHNode()
    {

    }

    BVHNode(Hitable **l, int n, float t0, float t1)
    {
      int axis_ = int(3 * random_in_0_1());

      if (axis_ == 0)
        qsort(l, n, sizeof(Hitable *), box_x_compare);
      else if (axis_ == 1)
        qsort(l, n, sizeof(Hitable *), box_y_compare);
      else
        qsort(l, n, sizeof(Hitable *), box_z_compare);

      if (n == 1)
      {
        m_left = m_right = l[0];
      }
      else if (n == 2)
      {
        m_left = l[0];
        m_right = l[1];
      }
      else
      {
        m_left = new BVHNode(l, n/2, t0, t1);
        m_right = new BVHNode(l + n/2, n - n/2, t0, t1);
      }

      AABB box_left_;
      AABB box_right_;

      if (m_left->bounding_box(t0, t1, box_left_) && m_right->bounding_box(t0, t1, box_right_))
        m_box = surrounding_box(box_left_, box_right_);
    }

    virtual bool hit(const Ray & ray, float tMin, float tMax, HitRecord & record) const
    {
      if (m_box.hit(ray, tMin, tMax))
      {
        HitRecord left_record_;
        HitRecord right_record_;

        bool hit_left_ = m_left->hit(ray, tMin, tMax, left_record_);
        bool hit_right_ = m_right->hit(ray, tMin, tMax, right_record_);

        if (hit_left_ && hit_right_)
        {
          if (left_record_.t < right_record_.t)
            record = left_record_;
          else
            record = right_record_;

          return true;
        }
        else if (hit_left_)
        {
          record = left_record_;
          return true;
        }
        else if (hit_right_)
        {
          record = right_record_;
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }

    virtual bool bounding_box(float t0, float t1, AABB & box) const
    {
      box = m_box;
      return true;
    }

  private:

    int box_x_compare(const void * a, const void * b)
    {
      AABB box_left_;
      AABB box_right_;

      Hitable *ah_ = *(Hitable**)a;
      Hitable *bh_ = *(Hitable**)b;

      if (!ah_->bounding_box(0.0f, 0.0f, box_left_) || ! bh_->bounding_box(0.0f, 0.0f, box_right_))
        std::cerr << "No bounding box in BVH node constructor...\n";
      
      if (box_left_.min().x() - box_right_.min().x() < 0.0f)
        return -1;
      else
        return 1;
    }

    int box_y_compare(const void * a, const void * b)
    {
      AABB box_left_;
      AABB box_right_;

      Hitable *ah_ = *(Hitable**)a;
      Hitable *bh_ = *(Hitable**)b;

      if (!ah_->bounding_box(0.0f, 0.0f, box_left_) || ! bh_->bounding_box(0.0f, 0.0f, box_right_))
        std::cerr << "No bounding box in BVH node constructor...\n";
      
      if (box_left_.min().y() - box_right_.min().y() < 0.0f)
        return -1;
      else
        return 1;
    }

    int box_z_compare(const void * a, const void * b)
    {
      AABB box_left_;
      AABB box_right_;

      Hitable *ah_ = *(Hitable**)a;
      Hitable *bh_ = *(Hitable**)b;

      if (!ah_->bounding_box(0.0f, 0.0f, box_left_) || ! bh_->bounding_box(0.0f, 0.0f, box_right_))
        std::cerr << "No bounding box in BVH node constructor...\n";
      
      if (box_left_.min().z() - box_right_.min().z() < 0.0f)
        return -1;
      else
        return 1;
    }

    Hitable *m_left;
    Hitable *m_right;
    AABB m_box;
};

#endif