// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include <cmath>

#include "Ray.h"
#include "Vec3.h"
#include "Utils.h"

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
         float vertical_fov, float aspect_ratio,
         float lens_radius, float focus_distance);

  inline Ray get_ray(float u, float v) const;

 private:
  Vec3 _lower_left_corner;
  Vec3 _horizontal;
  Vec3 _vertical;
  Vec3 _origin;
  Vec3 _u, _v, _w;
  float _lens_radius;  // lens radius
  float _focus_distance;
};

// _____________________________________________________________________________
Camera::Camera(const Vec3 &lookfrom,
               const Vec3 &lookat,
               const Vec3 &up_vector,
               float vertical_fov, float aspect_ratio,
               float lens_radius, float focus_distance) {
  // Convert the field of view to radians
  float theta = vertical_fov * (M_PI / 180.f);

  // Compute the half height & half width
  float half_height = static_cast<float>(tan(theta / 2.f));
  float half_width = aspect_ratio * half_height;

  // Set lens radius and focus distance
  _lens_radius = lens_radius;
  _focus_distance = focus_distance;

  // Compute camera's orthonormal basis
  _w = make_unit_vector(lookfrom - lookat);
  _u = make_unit_vector(cross(up_vector, _w));
  _v = cross(_w, _u);

  // Image plane vectors
  _origin = lookfrom;
  _lower_left_corner = _origin
                       - half_width*_focus_distance*_u
                       - half_height*_focus_distance*_v
                       - _focus_distance*_w;
  _horizontal = 2.f * half_width*_focus_distance*_u;
  _vertical =  2.f * half_height*_focus_distance*_v;
}


// _____________________________________________________________________________
Ray Camera::get_ray(float s, float t) const {
  // Get point on the unit disc
  float lens_x, lens_y;
  random_in_unit_disc(lens_x, lens_y);

  // Compute offset vector
  Vec3 offset = lens_x*_lens_radius*_u + lens_y*_lens_radius*_v;

  return Ray(_origin + offset,
             _lower_left_corner + s*_horizontal + t*_vertical
             - _origin - offset);
}

#endif  // SRC_CAMERA_H_
