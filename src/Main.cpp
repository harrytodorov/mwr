// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#include <iostream>
#include <fstream>  // output to a file
#include <sstream>  // ostringstream
#include <cmath>    // sqrt
#include <limits>   // maxfloat
#include <chrono>   // clock

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

/**
 * Render with the provided camera/objects and save it to a file with
 * the provided out_file name.
 * nx specifies the number of pixels along the width,
 * ny specifies the number of pixels along the height, and
 * ns provide the number of randomly shot samples per pixel (for antialiasing).
 * Box filter is applied.
 * Gamma correction is applied to the output image.
 */
void render_scene(Camera c,
                  Hitable* world,
                  const char *out_file,
                  int nx, int ny, int ns) {
  // Create file handler
  std::ofstream image_file;
  image_file.open(out_file);

  // PPM header
  image_file << "P3" << std::endl
            << nx << " " << ny << std::endl
            << "255" << std::endl;

  // Iterate over the pixels
  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      Vec3 col{0.f, 0.f, 0.f};

      // Iterate over the samples
      for (int s = 0; s < ns; s++) {
        // Get the sample parameters
        float u = static_cast<float>((i + get_random_in_range(0.f, 1.f)) / nx);
        float v = static_cast<float>((j + get_random_in_range(0.f, 1.f)) / ny);

        // Create the ray
        Ray r = c.get_ray(u, v);

        // Accumulate color
        col += color(r, world, 0);
      }

      // Apply antialiasing using box filter
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

  // Close file handler
  image_file.close();
}

Hitable* cover_scene() {
  // Number of objects
  int n = 500;

  HitableList *world = new HitableList(n+1);

  Sphere *sFloor = new Sphere(Vec3(0.f, -1000.f, 0.f),
                              1000.f,
                              new Lambertian(Vec3(0.5f, 0.5f, 0.5f)));
  world->append(sFloor);

  // Add small spheres
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      float choose_material = get_random_in_range(0.f, 1.f);
      float center_x = a+0.9f*get_random_in_range(0.f, 1.f);
      float center_z = b+0.9f*get_random_in_range(0.f, 1.f);
      Vec3 center(center_x, 0.2f, center_z);
      if ((center - Vec3(4.f, 0.2f, 0.f)).length() > 0.9f) {
        if (choose_material < 0.8f) {          // diffuse
          float rand_r = get_random_in_range(0.f, 1.f)
                         * get_random_in_range(0.f, 1.f);
          float rand_g = get_random_in_range(0.f, 1.f)
                         * get_random_in_range(0.f, 1.f);
          float rand_b = get_random_in_range(0.f, 1.f)
                         * get_random_in_range(0.f, 1.f);
          Sphere *sDiffuse = new Sphere(center, 0.2f,
                                        new Lambertian(Vec3(rand_r,
                                                            rand_g,
                                                            rand_b)));
          world->append(sDiffuse);
        } else if (choose_material < 0.95f) {  // metal
          float rand_r = get_random_in_range(0.5f, 1.f);
          float rand_g = get_random_in_range(0.5f, 1.f);
          float rand_b = get_random_in_range(0.5f, 1.f);
          float rand_fuzz = get_random_in_range(0.f, 1.f);
          Sphere *sMetal = new Sphere(center, 0.2f,
                                      new Metal(Vec3(rand_r, rand_g, rand_b),
                                                rand_fuzz));
          world->append(sMetal);
        } else {                               // glass
          Sphere *sGlass = new Sphere(center, 0.2, new Dialectic(1.52f));
          world->append(sGlass);
        }
      }
    }
  }

  // Add 3 big spheres
  Sphere *sBigGlass = new Sphere(Vec3(0.f, 1.f, 0.f),
                                 1.f,
                                 new Dialectic(1.52f));
  Sphere *sBigDiffuse = new Sphere(Vec3(-4.f, 1.f, 0.f),
                                   1.f,
                                   new Lambertian(Vec3(0.4f, 0.2f, 0.1f)));
  Sphere *sBigMetal = new Sphere(Vec3(4.f, 1.f, 0.f),
                                 1.f,
                                 new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.f));
  world->append(sBigGlass);
  world->append(sBigDiffuse);
  world->append(sBigMetal);

  return world;
}

// // Construct sample scene
// // cos(PI/4) ~ 0.70..
// float radius = static_cast<float>(cos(M_PI_4));
// Sphere *blue_sphere = new Sphere(Vec3(-radius, 0.f, -1.f),
//                                 radius,
//                                 new Lambertian(Vec3(0.f, 0.f, 1.f)));
// Sphere *red_sphere = new Sphere(Vec3(radius, 0.f, -1.f),
//                                 radius,
//                                 new Lambertian(Vec3(1.f, 0.f, 0.f)));
// world->append(blue_sphere);
// world->append(red_sphere);

// Sphere *sFloor = new Sphere(Vec3(0.f, -100.5f, -1.f),
//                         100.f,
//                         new Lambertian(Vec3(0.5f, 0.5f, 0.5f)));
// Sphere *sPinkish = new Sphere(Vec3(0.f, 0.f, 1.f),
//                         0.5f,
//                         new Lambertian(Vec3(0.8f, 0.3f, 0.3f)));
// Sphere *sGoldish = new Sphere(Vec3(1.f, 0.f, 1.f),
//                              0.5f,
//                              new Metal(Vec3(1.f, 0.71f, 0.29f), 0.8f));
// Sphere *sSilverish = new Sphere(Vec3(-1.f, 0.f, 1.f),
//                         0.5f,
//                         new Metal(Vec3(0.95f, 0.93f, 0.88f), 0.9f));
// Sphere *sWaterish = new Sphere(Vec3(-2.f, 0.f, 1.f),
//                                0.5f,
//                                new Dialectic(1.52f));

// HitableList *world = new HitableList;
// world->append(sPinkish);
// world->append(sFloor);
// world->append(sGoldish);
// world->append(sSilverish);
// world->append(sWaterish);

int main() {
  int nx = 1280;
  int ny = 720;
  int ns = 100;  // Number of samples

  Vec3 lookfrom(13.f, 2.f, 3.f);
  Vec3 lookat(0.f, 0.f, 0.f);
  Vec3 up(0.f, 1.f, 0.f);
  float ar = static_cast<float>(nx) / static_cast<float>(ny);
  float lens_radius = 0.05f;
  float distance_to_focus = 10.f;

  // Camera
  Camera cam(lookfrom, lookat, up, 20.f, ar, lens_radius, distance_to_focus);

  // File naming
  std::ostringstream fileName;
  fileName << "cover_floor+bigS+smallS.ppm";
  std::string fileNameStr = fileName.str();

  // Measure the rendering time
  auto start = std::chrono::steady_clock::now();

  // Render scene and output image
  render_scene(cam, cover_scene(), fileNameStr.c_str(), nx, ny, ns);

  auto end = std::chrono::steady_clock::now();
  auto duration =
       std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << "Rendered in " << duration << " seconds." << std::endl;
}
