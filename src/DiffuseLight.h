// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_DIFFUSELIGHT_H_
#define SRC_DIFFUSELIGHT_H_

#include "Material.h"
#include "Texture.h"

class DiffuseLight: public Material {
 public:
  DiffuseLight() = default;
  explicit DiffuseLight(Texture *t) : _emit(t) {}
  ~DiffuseLight() { delete _emit; }

  virtual bool scatter(const Ray &r,
                       const HitRecord &rec,
                       Vec3 &attenuation,
                       Ray &scattered) const;

  virtual Vec3 emit(float u, float v, const Vec3 &p) const;
 private:
  Texture *_emit{nullptr};
};

// _____________________________________________________________________________
bool DiffuseLight::scatter(const Ray &r,
             const HitRecord &rec,
             Vec3 &attenuation,
             Ray &scattered) const {
  return false;
}

// _____________________________________________________________________________
Vec3 DiffuseLight::emit(float u, float v, const Vec3 &p) const {
  return _emit->value(u, v, p);
}
#endif  // SRC_DIFFUSELIGHT_H_