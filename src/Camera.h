// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include <cmath>

#include "Ray.h"
#include "Vec3.h"

class Camera {
 public:
  Camera() = delete;
  /**
   * lookfrom is the camera's origin position.
   * lookat is the point onto witch the camera is pointing.
   * up_vector is the vector which defines the camera's orientation.
   * vertical_fov is the vertical field of view in degrees.
   * aspect_ratio is just the aspect ratio between the image plane's
   * width and height.
   */
  Camera(const Vec3 &lookfrom,
         const Vec3 &lookat,
         const Vec3 &up_vector,
         float vertical_fov, float aspect_ratio);

  inline Ray get_ray(float u, float v) const;
 private:
  Vec3 _lower_left_corner;
  Vec3 _horizontal;
  Vec3 _vertical;
  Vec3 _origin;
};

// _____________________________________________________________________________
Camera::Camera(const Vec3 &lookfrom,
               const Vec3 &lookat,
               const Vec3 &up_vector,
               float vertical_fov, float aspect_ratio) {
  // Convert the field of view to radians
  float theta = vertical_fov * (M_PI / 180.f);
 
  // Compute the half height & half width
  float half_height = static_cast<float>(tan(theta / 2.f));
  float half_width = aspect_ratio * half_height;

  // Compute camera's orthonormal basis
  Vec3 u, v, w;
  w = make_unit_vector(lookfrom - lookat);
  u = make_unit_vector(cross(up_vector, w));
  v = cross(w, u);

  // Image plane vectors
  _origin = lookfrom;
  _lower_left_corner = _origin - half_width*u - half_height*v - w;
  _horizontal = 2.f * half_width*u;
  _vertical =  2.f * half_height*v;
}

// _____________________________________________________________________________
Ray Camera::get_ray(float s, float t) const {
  return Ray(_origin,
             _lower_left_corner + s*_horizontal + t*_vertical - _origin);
}

#endif  // SRC_CAMERA_H_
