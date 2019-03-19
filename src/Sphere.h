// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_SPHERE_H_
#define SRC_SPHERE_H_

#include <iostream>

#include "Hitable.h"

class Sphere: public Hitable {
 public:
  Sphere() {}
  Sphere(const Vec3 &center, float radius) {
    _center = center;
    _radius = radius;
  }

  inline Vec3 center() const { return _center; }
  inline float radius() const { return _radius; }

  virtual bool hit(const Ray &r,
                   float t_min,
                   float t_max,
                   HitRecord &rec) const;

  inline void set_hit_record(const float t,
                             const Ray &r,
                             HitRecord &rec) const {
    rec.t = t;
    rec.p = r.point_at_t(t);
    rec.normal = (rec.p - _center) / _radius;
  }

 private:
  Vec3 _center;
  float _radius;
};

// _____________________________________________________________________________
bool Sphere::hit(const Ray &r,
                 float t_min,
                 float t_max,
                 HitRecord &rec) const {
  // Solve discriminant:
  // D = b^2 - 4ac
  // a = dot(ray.dir, ray.dir)
  // b = 2*dot(ray.dir, ray.orig-center)
  // c = dot(ray.orig-center, ray.orig-center)
  // u = ray.orig-center
  Vec3 u = r.origin() - _center;
  float a = dot(r.direction(), r.direction());
  float b = 2*dot(r.direction(), u);
  float c = dot(u, u) - _radius*_radius;

  float discriminant = b*b - 4.f*a*c;
  // When D < 0, there is no intersection
  if (discriminant < 0.f) return false;

  // D == 0, 1 intesection; but sqrt(0) = 0,
  // so the case is naturally included
  // D > 0, 2 possible intersections
  float dis_sqrt = sqrt(discriminant);

  float t = (-b - dis_sqrt) / (2.f*a);
  if (t > t_min && t < t_max) {
    set_hit_record(t, r, rec);
    return true;
  }

  t = (-b + dis_sqrt) / (2.f*a);
  if (t > t_min && t < t_max) {
    set_hit_record(t, r, rec);
    return true;
  }

  return false;
}

// _____________________________________________________________________________
inline std::ostream& operator<<(std::ostream &os, const Sphere &s) {
  os << "[" << "sphere, center: " << s.center()
     << ", radius: " << s.radius() << "]";
  return os;
}

#endif  // SRC_SPHERE_H_
