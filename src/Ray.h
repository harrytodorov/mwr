// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include "Vec3.h"

class Ray {
 public:
  Ray() {}
  Ray(const Vec3 &o, const Vec3 &d) { _origin = o; _direction = d; }

  inline Vec3 origin() const { return _origin; }
  inline Vec3 direction() const { return _direction; }
  inline Vec3 point_at_t(float t) const { return _origin + t*_direction; }

  inline void origin(const Vec3 &origin) { _origin = origin; }
  inline void direction(const Vec3 &direction) { _direction = direction; }

 private:
  Vec3 _origin;
  Vec3 _direction;
};

#endif  // SRC_RAY_H_
