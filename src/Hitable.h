// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_HITABLE_H_
#define SRC_HITABLE_H_

#include "Ray.h"
#include "AABB.h"

// Forward declaration
class Material;

struct HitRecord {
  float u;
  float v;
  float t;
  Vec3 p;
  Vec3 normal;
  Material *mat_ptr;
};

class Hitable {
 public:
  virtual ~Hitable() {}

  virtual bool hit(const Ray &r,
                   float t_min,
                   float t_max,
                   HitRecord &rec) const = 0;

  virtual bool bounding_box(AABB &box) const = 0;
};

#endif  // SRC_HITABLE_H_
