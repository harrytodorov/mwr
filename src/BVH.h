// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_BVH_H_
#define SRC_BVH_H_

#include "Hitable.h"
#include "HitableList.h"
#include "Utils.h"
#include "Sphere.h"

class BVH: public Hitable {
 public:
  BVH() = default;
  BVH(HitableList *l, int min_idx, int max_idx);
  ~BVH();

  virtual bool hit(const Ray &r,
                   float t_min,
                   float t_max,
                   HitRecord &rec) const;

  virtual bool bounding_box(AABB &box) const;

 private:
  Hitable *_left{nullptr};
  Hitable *_right{nullptr};
  AABB _box;
  int _range_min{0};
  int _range_max{0};
};

// _____________________________________________________________________________
BVH::BVH(HitableList *l, int min_idx, int max_idx) {
  _range_min = min_idx;
  _range_max = max_idx;

  // Choose axis for split
  int axis = static_cast<int>(get_random_in_range(0.f, 3.f));
  // std::cout << "axis: " << axis << std::endl;
  // std::cout << "sorting: [" << min_idx << ", " << max_idx << ")" << std::endl;

  // Sort by the axis
  l->sort_in_range(axis, _range_min, _range_max);

  // // Print sorted elements
  // for (int i = min_idx; i < max_idx; i++) {
  //   std::cout << (*static_cast<Sphere*>((*l)[i])) << std::endl;
  // }

  // Recustion base cases
  // 1 Hitable: it gets copied to both children
  int num_elements = max_idx - min_idx;
  if (num_elements == 1) {
    // std::cout << "1 Hitable, copying it to both children" << std::endl;
    _left = _right = (*l)[min_idx];
  // 2 Hitables: each leaf is a Hitable
  } else if (num_elements == 2) {
    // std::cout << "2 Hitables, splitting them between children" << std::endl;
    _left = (*l)[min_idx];
    _right = (*l)[min_idx + 1];
  // Recuriseve case
  // Create two BVH nodes as children
  } else {
    int half_els = num_elements / 2;
    // std::cout << "Splitting into two new BVH nodes" << std::endl;
    // std::cout << "Left node" << std::endl;
    _left = new BVH(l, min_idx, min_idx + half_els);
    // std::cout << "Right node" << std::endl;
    _right = new BVH(l, min_idx + half_els, max_idx);
  }

  // Create bounding boxes for the nodes
  AABB left_box, right_box;
  if (!_left->bounding_box(left_box) || !_right->bounding_box(right_box)) {
    std::cout << "No bounding box" << std::endl;
  }
  _box = surrounding_box(left_box, right_box);
  // std::cout << std::endl;
}

// _____________________________________________________________________________
BVH::~BVH() {
  // Delete children nodes, if they exist
  if (_left != nullptr) delete _left;
  if (_right != nullptr) delete _right;
}

// _____________________________________________________________________________
bool BVH::hit(const Ray &r,
              float t_min,
              float t_max,
              HitRecord &rec) const {
  // Check if the surrounding box is hit
  if (!_box.hit(r, t_min, t_max)) return false;

  // Get possible hits from children nodes recursively
  HitRecord left_rec, right_rec;
  bool is_left_hit = _left->hit(r, t_min, t_max, left_rec);
  bool is_right_hit = _right->hit(r, t_min, t_max, right_rec);

  // Hit logic
  if (!is_left_hit && !is_right_hit) return false;

  // Left child hit
  if (is_left_hit && !is_right_hit) {
    rec = left_rec;
    return true;
  }

  // Right child hit
  if (!is_left_hit && is_right_hit) {
    rec = right_rec;
    return true;
  }

  // Both children were hit, get the smaller one
  if (left_rec.t < right_rec.t) {
    rec = left_rec;
  } else {
    rec = right_rec;
  }
  return true;
}

// _____________________________________________________________________________
bool BVH::bounding_box(AABB &box) const {
  box = _box;
  return true;
}

#endif  // SRC_BVH_H_
