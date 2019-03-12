// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#include <iostream>
#include <fstream>  // Output to a file

#include "Vec3.h"
#include "Ray.h"

bool hit_sphere(const Vec3 &center, float radius, const Ray &r) {
  // Solve discriminant:
  // D = b^2 - 4ac
  // a = dot(ray.dir, ray.dir)
  // b = 2*dot(ray.dir, ray.orig-center)
  // c = dot(ray.orig-center, ray.orig-center)
  // u = ray.orig-center
  Vec3 u = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2*dot(r.direction(), u);
  float c = dot(u, u) - radius*radius;

  float discriminant = b*b - 4.f*a*c;
  // When D >= 0, there is an intersection
  return (discriminant >= 0.f);
}

Vec3 color(const Ray &r) {
  // Color a sphere in the center of the screen in green
  if (hit_sphere(Vec3(0.f, 0.f, -1.f), 0.5f, r))
    return Vec3(0.60f, 0.78f, 0.25f);

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

int main() {
  int nx = 200;
  int ny = 100;

  std::ofstream image_file;
  image_file.open("rendered_image.ppm");

  // PPM header
  image_file << "P3" << std::endl
             << nx << " " << ny << std::endl
             << "255" << std::endl;

  // Help vectors to traverse the image plane
  Vec3 lower_left_corner(-2.f, -1.f, -1.f);
  Vec3 horizontal(4.f, 0.f, 0.f);
  Vec3 vertical(0.f, 2.f, 0.f);
  Vec3 camera_origin(0.f, 0.f, 0.f);

  // The actual image pixel
  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      // Get camera screen parameters
      float u = static_cast<float>(i) / static_cast<float>(nx);
      float v = static_cast<float>(j) / static_cast<float>(ny);

      // Create the ray
      Ray r(camera_origin, lower_left_corner + u*horizontal + v*vertical);

      // Get the color
      Vec3 col = color(r);

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
