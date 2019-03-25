// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#include <iostream>
#include <fstream>  // Output to a file
#include <cmath>  // sqrt()
#include <limits>  // Maxfloat

#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Utils.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dialectic.h"

// Definitions
#define SHADOW_BIAS 0.001f
#define RECURSION_DEPTH 50

Vec3 color(const Ray &r, Hitable *world, int depth) {
  HitRecord rec;
  if (world->hit(r, SHADOW_BIAS, MAXFLOAT, rec)) {
    Ray scattered_ray;
    Vec3 attenuation;

    // Bounce the scattered ray, until maximum recursion depth is reached,
    // or the material on the hitpoint has decided not to scatter the ray
    if (depth < RECURSION_DEPTH &&
        rec.mat_ptr->scatter(r, rec, attenuation, scattered_ray)) {
      return attenuation * color(scattered_ray, world, depth+1);
    } else {
      return Vec3(0.f, 0.f, 0.f);
    }
  // Nothing is hit
  } else {
    Vec3 unit_direction = make_unit_vector(r.direction());
    // After making the ray's direction a unit vector, y-axis is in the range
    // [-1, 1]. Following transformation first adds 1 to the y-axis
    // and it now has the range [0, 2]. Multiplying it by 0.5 scales down the
    // range to [0, 1]
    float t = 0.5f * (unit_direction.y() + 1.f);
    // Linear interpolation interpolation between white (t = 0) and blue
    // (t = 1).
    return
    // white color
    (1.f - t)*Vec3(1.f, 1.f, 1.f) +
    // blue color
    t*Vec3(0.5f, 0.7f, 1.f);
  }
}

int main() {
  int nx = 200;
  int ny = 100;
  int ns = 100;  // Number of samples

  std::ofstream image_file;
  image_file.open("balls_different_materials_fuzzymetal_dialectic.ppm");

  // PPM header
  image_file << "P3" << std::endl
             << nx << " " << ny << std::endl
             << "255" << std::endl;

  // World and Objects
  Sphere *s0 = new Sphere(Vec3(0.f, 0.f, -1.f),
                          0.5f,
                          new Lambertian(Vec3(0.1f, 0.2f, 0.5f)));
  Sphere *s1 = new Sphere(Vec3(0.f, -100.5f, -1.f),
                          100.f,
                          new Lambertian(Vec3(0.8f, 0.8f, 0.f)));
  Sphere *s2 = new Sphere(Vec3(1.f, 0.f, -1.f),
                          0.5f,
                          new Metal(Vec3(0.8f, 0.6f, 0.2f), 0.3f));
  Sphere *s3 = new Sphere(Vec3(-1.f, 0.f, -1.f),
                          0.5f,
                          new Dialectic(1.5f));
  HitableList *world = new HitableList;
  world->append(s0);
  world->append(s1);
  world->append(s2);
  world->append(s3);

  // Camera
  Camera cam;

  // The actual image pixel
  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      Vec3 col{0.f, 0.f, 0.f};

      // Antialiasing
      for (int s = 0; s < ns; s++) {
        // Get the sample parameters
        float u = static_cast<float>((i + get_random_in_range(0.f, 1.f)) / nx);
        float v = static_cast<float>((j + get_random_in_range(0.f, 1.f)) / ny);

        // Create the ray
        Ray r = cam.get_ray(u, v);

        // Accumulate color
        col += color(r, world, 0);
      }

      // Box sampling
      col /= static_cast<float>(ns);

      // Gamma correction
      col[0] = sqrt(col[0]);
      col[1] = sqrt(col[1]);
      col[2] = sqrt(col[2]);

      // Convert floats to ints
      int ir = static_cast<int>(255.99f * col.r());
      int ig = static_cast<int>(255.99f * col.g());
      int ib = static_cast<int>(255.99f * col.b());

      // Print pixel
      image_file << ir << " " << ig << " " << ib << std::endl;
    }
  }

  // Close file
  image_file.close();
}
