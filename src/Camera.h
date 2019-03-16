// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include "Ray.h"

class Camera {
 public:
  Camera() = default;
  inline Ray get_ray(float u, float v) const;
 private:
  Vec3 lower_left_corner{-2.f, -1.f, -1.f};
  Vec3 horizontal{4.f, 0.f, 0.f};
  Vec3 vertical{0.f, 2.f, 0.f};
  Vec3 camera_origin{0.f, 0.f, 0.f};
};

Ray Camera::get_ray(float u, float v) const {
  return Ray(camera_origin, lower_left_corner + u*horizontal + v*vertical);
}

#endif  // SRC_CAMERA_H_
