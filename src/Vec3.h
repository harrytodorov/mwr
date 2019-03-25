// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_VEC3_H_
#define SRC_VEC3_H_

#include <math.h>

// Vector3 class is used to represent colors, locations, directions, etc
class Vec3 {
 public:
  Vec3() = default;
  Vec3(float e0, float e1, float e2) { _e[0] = e0; _e[1] = e1; _e[2] = e2; }
  Vec3(const Vec3 &v2) { _e[0] = v2.x(); _e[1] = v2.y(); _e[2] = v2.z(); }

  // Location / Direction
  inline float x() const { return _e[0]; }
  inline float y() const { return _e[1]; }
  inline float z() const { return _e[2]; }

  // Color
  inline float r() const { return _e[0]; }
  inline float g() const { return _e[1]; }
  inline float b() const { return _e[2]; }

  inline const Vec3& operator+() const { return *this; }
  inline Vec3 operator-() const { return Vec3(-_e[0], -_e[2], -_e[2]); }
  inline float operator[](int i) const { return _e[i]; }
  inline float& operator[](int i) { return _e[i]; }

  inline Vec3& operator+=(const Vec3 &v2);
  inline Vec3& operator-=(const Vec3 &v2);
  inline Vec3& operator*=(const Vec3 &v2);
  inline Vec3& operator/=(const Vec3 &v2);
  inline Vec3& operator*=(const float t);
  inline Vec3& operator/=(const float t);

  inline float length() const;
  inline float squared_length() const;
  inline void make_unit_vector();

 private:
  // Default initialization set vector's elements to 0
  float _e[3]{};
};

// _____________________________________________________________________________
Vec3& Vec3::operator+=(const Vec3 &v2) {
  _e[0] += v2._e[0];
  _e[1] += v2._e[1];
  _e[2] += v2._e[2];
  return *this;
}

// _____________________________________________________________________________
Vec3& Vec3::operator-=(const Vec3 &v2) {
  _e[0] -= v2._e[0];
  _e[1] -= v2._e[1];
  _e[2] -= v2._e[2];
  return *this;
}

// _____________________________________________________________________________
Vec3& Vec3::operator*=(const Vec3 &v2) {
  _e[0] *= v2._e[0];
  _e[1] *= v2._e[1];
  _e[2] *= v2._e[2];
  return *this;
}

// _____________________________________________________________________________
Vec3& Vec3::operator/=(const Vec3 &v2) {
  _e[0] /= v2._e[0];
  _e[1] /= v2._e[1];
  _e[2] /= v2._e[2];
  return *this;
}

// _____________________________________________________________________________
Vec3& Vec3::operator*=(float t) {
  _e[0] *= t;
  _e[1] *= t;
  _e[2] *= t;
  return *this;
}

// _____________________________________________________________________________
Vec3& Vec3::operator/=(float t) {
  float k = 1.f/t;

  _e[0] *= k;
  _e[1] *= k;
  _e[2] *= k;
  return *this;
}

// _____________________________________________________________________________
float Vec3::length() const {
  return sqrt(_e[0]*_e[0] + _e[1]*_e[1] + _e[2]*_e[2]);
}

// _____________________________________________________________________________
float Vec3::squared_length() const {
  return _e[0]*_e[0] + _e[1]*_e[1] + _e[2]*_e[2];
}

// _____________________________________________________________________________
void Vec3::make_unit_vector() {
  float il = 1.f / sqrt(_e[0]*_e[0] + _e[1]*_e[1] + _e[2]*_e[2]);
  _e[0] *= il;
  _e[1] *= il;
  _e[2] *= il;
}

// _____________________________________________________________________________
// Non-member functions
// _____________________________________________________________________________

// _____________________________________________________________________________
inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.x()+v2.x(), v1.y()+v2.y(), v1.z()+v2.z());
}

// _____________________________________________________________________________
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.x()-v2.x(), v1.y()-v2.y(), v1.z()-v2.z());
}

// _____________________________________________________________________________
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.x()*v2.x(), v1.y()*v2.y(), v1.z()*v2.z());
}

// _____________________________________________________________________________
inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.x()/v2.x(), v1.y()/v2.y(), v1.z()/v2.z());
}

// _____________________________________________________________________________
inline Vec3 operator*(const Vec3 &v, float t) {
  return Vec3(t*v.x(), t*v.y(), t*v.z());
}

// _____________________________________________________________________________
inline Vec3 operator*(float t, const Vec3 &v) {
  return Vec3(t*v.x(), t*v.y(), t*v.z());
}

// _____________________________________________________________________________
inline Vec3 operator/(const Vec3 &v, float t) {
  return Vec3(v.x()/t, v.y()/t, v.z()/t);
}

// _____________________________________________________________________________
inline std::ostream& operator<<(std::ostream &os, const Vec3 &v) {
  os << "[" << v.x() << ", " << v.y() << ", " << v.z() << "]";
  return os;
}

// _____________________________________________________________________________
inline float dot(const Vec3 &v1, const Vec3 &v2) {
  return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
}

// _____________________________________________________________________________
inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.y()*v2.z() - v1.z()*v2.y(),
              v1.z()*v2.x() - v1.x()*v2.z(),
              v1.x()*v2.y() - v1.y()*v2.x());
}

// _____________________________________________________________________________
inline Vec3 make_unit_vector(const Vec3 v) {
  return v / v.length();
}


#endif  // SRC_VEC3_H_
