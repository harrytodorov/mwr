// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_LAMBERTIAN_H_
#define SRC_LAMBERTIAN_H_

#include "Material.h"
#include "Vec3.h"
#include "Utils.h"
#include "Texture.h"

class Lambertian: public Material {
 public:
  Lambertian() = default;
  explicit Lambertian(Texture *albedo) : _albedo(albedo) {}

  virtual bool scatter(const Ray &r,
                       const HitRecord &rec,
                       Vec3 &attenuation,
                       Ray &scattered) const;
 private:
  Texture *_albedo{nullptr};
};

// _____________________________________________________________________________
bool Lambertian::scatter(const Ray &r,
                         const HitRecord &rec,
                         Vec3 &attenuation,
                         Ray &scattered) const {
  Vec3 target_direction = rec.normal + random_in_unit_sphere();
  scattered.origin(rec.p);
  scattered.direction(target_direction);
  attenuation = _albedo->value(0.f, 0.f, rec.p);
  return true;
}

#endif  // SRC_LAMBERTIAN_H_
