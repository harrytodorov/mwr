// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_MATERIAL_H_
#define SRC_MATERIAL_H_

#include "Ray.h"
#include "Hitable.h"
#include "Vec3.h"

class Material {
 public:
  virtual ~Material() {}

  virtual bool scatter(const Ray &r,
                       const HitRecord &rec,
                       Vec3 &attenuation,
                       Ray &scattered) const = 0;

  virtual Vec3 emit(float u, float v, const Vec3 &p) const {
    return Vec3(0.f, 0.f, 0.f);
  }
};

#endif  // SRC_MATERIAL_H_
