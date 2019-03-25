// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_DIALECTIC_H_
#define SRC_DIALECTIC_H_

#include "Material.h"
#include "Utils.h"

class Dialectic: public Material {
 public:
  Dialectic() = delete;
  explicit Dialectic(float ri) : _refraction_index(ri) {}

  inline float reflective_index() const { return _refraction_index; }
  virtual bool scatter(const Ray &r,
                       const HitRecord &rec,
                       Vec3 &attenuation,
                       Ray &scattered) const;
 private:
  float _refraction_index;
};

// _____________________________________________________________________________
bool Dialectic::scatter(const Ray &r,
                        const HitRecord &rec,
                        Vec3 &attenuation,
                        Ray &scattered) const {
  attenuation = Vec3(1.f, 1.f, 1.f);
  Vec3 refracted_direction;
  Vec3 normal = rec.normal;
  // One assumes there is always air between two surfaces
  bool inside_medium = (dot(r.direction(), rec.normal) >= 0.f);
  float n1;
  float n2;
  float reflection_coefficient;
  if (inside_medium) {
    n1 = _refraction_index;
    n2 = 1.0003f;
    normal *= -1.f;
  } else {
    n1 = 1.0003f;
    n2 = _refraction_index;
  }

  // Handle reflection/refraction contribution
  if (refract(r.direction(), normal, n1, n2, refracted_direction)) {
    // Compute the reflection contribution according to Schlick's approx.
    reflection_coefficient = schlick(r.direction(), normal, n1, n2);
  } else {
    // In case of total internal reflection, there is only reflection
    reflection_coefficient = 1.f;
  }

  // "Randomly" choose to either shoot a reflection ray or a transmission ray
  if (get_random_in_range(0.f, 1.f) < reflection_coefficient) {
    scattered.origin(rec.p);
    scattered.direction(reflect(r.direction(), normal));
  } else {
    scattered.origin(rec.p);
    scattered.direction(refracted_direction);

  }
  return true;
}

#endif  // SRC_DIALECTIC_H_
