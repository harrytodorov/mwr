// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_AABB_H_
#define SRC_AABB_H_

#include <limits>  // min/max float

#include "Vec3.h"
#include "Ray.h"

// _____________________________________________________________________________
inline float maxf() {
  float max = static_cast<float>(std::numeric_limits<float>::max());
  return max;
}

// _____________________________________________________________________________
inline float minf() {
  float min = static_cast<float>(std::numeric_limits<float>::min());
  return min;
}

// _____________________________________________________________________________
inline float minf(float a, float b) {
  return a < b ? a : b;
}

// _____________________________________________________________________________
inline float maxf(float a, float b) {
  return a > b ? a : b;
}

class AABB {
 public:
  AABB() = default;
  AABB(const Vec3 &a, const Vec3 &b) : _min(a), _max(b) {}

  Vec3 min() const { return _min; }
  Vec3 max() const { return _max; }

  bool hit(const Ray &r, float &t_min, float &t_max) const;
 private:
  Vec3 _min{maxf(), maxf(), maxf()};
  Vec3 _max{minf(), minf(), minf()};
};

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

// _____________________________________________________________________________
inline AABB surrounding_box(AABB &a, AABB &b) {
  Vec3 small(minf(a.min().x(), b.min().x()),
             minf(a.min().y(), b.min().y()),
             minf(a.min().z(), b.min().z()));
  Vec3 big  (maxf(a.max().x(), b.max().x()),
             maxf(a.max().y(), b.max().y()),
             maxf(a.max().z(), b.max().z()));
  return AABB(small, big);
}

#endif  // SRC_AABB_H_
