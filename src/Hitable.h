// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_HITABLE_H_
#define SRC_HITABLE_H_

#include <iostream>

#include "Ray.h"

struct HitableRecord {
  float t;
  Vec3 p;
  Vec3 normal;
};

class Hitable {
 public:
  virtual ~Hitable() {}
  virtual bool hit(const Ray &r,
                   float t_min,
                   float t_max,
                   HitableRecord &rec) const = 0;
};

#endif  // SRC_HITABLE_H_
