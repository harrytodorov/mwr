// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <stdlib.h>  // drand48
#include <cmath>  // sqrt, pow

#include "Vec3.h"

// -----------------------------------------------------------------------------
// Function definitions
// -----------------------------------------------------------------------------

/**
 * Pick a random point in the unit sphere using the rejection method.
 * Algorithm:
 * 1. Generate a random point inside the unit cube just with x,y,z having
 *    random values between [-1, 1).
 * 2. Generate new points while the squred length of the point is larger than 1
 */
Vec3 random_in_unit_sphere();

/**
 * Pick a random point in the unit dist using the rejection method.
 * Algorithm:
 * 1. Generate a random point inside the unit square just with x,y having
 *    random values between [-1, 1).
 * 2. Generate new points while the squred length of the point is larger than 1
 */
void random_in_unit_disc(float &x, float &y);

/**
 * Generate a random number in the range [min, max)
 */
float get_random_in_range(float min, float max);

/**
 * Reflect an incoming ray i, which is not normalized. n is the normal at
 * the hitpoint.
 */
Vec3 reflect(const Vec3 &i, const Vec3 &n);

/**
 * Refract an incoming ray i, which is not normalized. 
 * n is the normal at the hitpoint.
 * n_it is the ration between the refraction index of the first and the second
 * medium.
 * t is the transmitted/refracted vector.
 */
bool refract(const Vec3 &i, const Vec3 &n, float n_it, Vec3 &t);

/**
 * Compute the reflection coefficient according to the approximation of the
 * Fresnel equations by Christophe Schlick.
 * i is the incoming ray.
 * n is the normal at the hitpoint.
 * ri is the larger refraction index
 * n1 is the refraction index of the medium from which the incoming ray is
 * coming.
 * n2 is the refraction index of the medium into which the incoming ray going
 * to.
 * in gives hints to the function how to compute the cosine
 */
float schlick(const Vec3 &i, const Vec3 &n, float n1, float n2, bool in);

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

void random_in_unit_disc(float &x, float &y) {
  do {
    x = get_random_in_range(-1.f, 1.f);
    y = get_random_in_range(-1.f, 1.f);
  } while (x*x + y*y >= 1.f);
}

// _____________________________________________________________________________
float get_random_in_range(float min, float max) {
  float diff = max - min;
  return static_cast<float>(drand48()*diff + min);
}

// _____________________________________________________________________________
Vec3 reflect(const Vec3 &i, const Vec3 &n) {
  return i - 2*dot(i, n)*n;
}

// _____________________________________________________________________________
bool refract(const Vec3 &i, const Vec3 &n, float n_it, Vec3 &t) {
  Vec3 ui = make_unit_vector(i);
  float cos_i = dot(ui, n);
  float discriminant = 1.f - n_it*n_it * (1.f - cos_i*cos_i);
  // Discriminant <= 0: there is refraction, otherwise total internal refraction
  if (discriminant <= 0.f) return false;
  t = n_it*(ui - cos_i*n) - sqrt(discriminant)*n;
  return true;
}

// _____________________________________________________________________________
float schlick(const Vec3 &i, const Vec3 &n, float ri, bool in) {
  // Compute supplementary
  float r0 = (1.0003f - ri) / (1.0003f + ri);
  r0 = r0 * r0;

  // Compute the cosine
  float cosine = dot(i, n) / i.length();
  if (in) {
    cosine = sqrt(1.f - ri*ri * (1.f - cosine*cosine));
  } else {
    cosine = -cosine;
  }

  // Compute reflection coefficient
  return r0 + (1.f - r0)*pow((1.f - cosine), 5);
}

#endif  // SRC_UTILS_H_
