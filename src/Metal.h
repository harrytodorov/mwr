// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_METAL_H_
#define SRC_METAL_H_

#include "Material.h"
#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Utils.h"


class Metal: public Material {
 public:
  Metal() = default;
  Metal(const Vec3 &albedo, float fuzz);

  virtual bool scatter(const Ray &r,
                       const HitRecord &rec,
                       Vec3 &attenuation,
                       Ray &scattered) const;
 private:
  Vec3 _albedo{0.f, 0.f, 0.f};
  float _fuzz{0.f};
};

// _____________________________________________________________________________
Metal::Metal(const Vec3 &albedo, float fuzz) {
  _albedo = albedo;
  _fuzz = fuzz < 1.f ? fuzz : 1.f;
}

// _____________________________________________________________________________
bool Metal::scatter(const Ray &r,
                    const HitRecord &rec,
                    Vec3 &attenuation,
                    Ray &scattered) const {
  Vec3 reflected = reflect(make_unit_vector(r.direction()), rec.normal);
  scattered.origin(rec.p);
  scattered.direction(reflected + _fuzz*random_in_unit_sphere());
  attenuation = _albedo;
  bool same_direction = (dot(reflected, rec.normal) > 0.f);
  return same_direction;
}

#endif  // SRC_METAL_H_
