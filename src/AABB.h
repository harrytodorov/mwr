// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_AABB_H_
#define SRC_AABB_H_

#include "Vec3.h"
#include "Ray.h"

class AABB {
 public:
  AABB() = delete;
  AABB(const Vec3 &a, const Vec3 &b) : _min(a), _max(b) {}

  Vec3 min() const { return _min; }
  Vec3 max() const { return _max; }

  bool hit(const Ray &r, float &t_min, float &t_max) const;
 private:
  Vec3 _min;
  Vec3 _max;
};

// _____________________________________________________________________________
inline float minf(float a, float b) {
  return a < b ? a : b;
}

// _____________________________________________________________________________
inline float maxf(float a, float b) {
  return a > b ? a : b;
}

// _____________________________________________________________________________
bool AABB::hit(const Ray &r, float &t_min, float &t_max) const {
  float t0, t1;
  // Iterate over the 3 axis of the AABB
  for (int a = 0; a < 3; a++) {
    // Compute t0 and t1
    t0 = minf((min()[a] - r.origin()[a]) / r.direction()[a],
              (max()[a] - r.origin()[a]) / r.direction()[a]);
    t1 = maxf((min()[a] - r.origin()[a]) / r.direction()[a],
              (max()[a] - r.origin()[a]) / r.direction()[a]);

    // Update the ray's min/max intervals
    t_min = maxf(t0, t_min);
    t_max = minf(t1, t_max);

    // Check if the intervals got swapped
    if (t_max <= t_min) return false;
  }
  return true;
}

#endif  // SRC_AABB_H_
