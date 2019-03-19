// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <stdlib.h>  // drand48

#include "Vec3.h"

// -----------------------------------------------------------------------------
// Function definitions
// -----------------------------------------------------------------------------

/**
 * Pick a random point in the unit sphere using the rejection method.
 * Algoritmh:
 * 1. Generate a random point inside the unit cube just with x,y,z having
 *    random values between [-1, 1).
 * 2. Generate new points while the squred length of the point is larger than 1
 */
Vec3 random_in_unit_sphere();

/**
 * Generate a random number in the range [min, max)
 */
float get_random_in_range(float min, float max);

/**
 * Reflect an incoming ray i, which is not normalized. n is the normal at
 * the hitpoint.
 */
Vec3 reflect(const Vec3 &i, const Vec3 &n) {
  return i - 2*dot(i, n)*n;
}

// -----------------------------------------------------------------------------
// Function declaration
// -----------------------------------------------------------------------------

// _____________________________________________________________________________
Vec3 random_in_unit_sphere() {
  Vec3 point;
  do {
    point[0] = get_random_in_range(-1.f, 1.f);
    point[1] = get_random_in_range(-1.f, 1.f);
    point[2] = get_random_in_range(-1.f, 1.f);
  } while (point.squared_length() >= 1.f);
  return point;
}

// _____________________________________________________________________________
float get_random_in_range(float min, float max) {
  float diff = max - min;
  return static_cast<float>(drand48()*diff + min);
}

#endif  // SRC_UTILS_H_
