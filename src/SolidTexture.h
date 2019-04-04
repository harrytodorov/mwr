// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_SOLIDTEXTURE_H_
#define SRC_SOLIDTEXTURE_H_

#include "Texture.h"
#include "Vec3.h"

class SolidTexture: public Texture {
 public:
  SolidTexture() {}
  explicit SolidTexture(const Vec3 &c) : _color(c) {}

  virtual Vec3 value(float u, float v, const Vec3 &p) const;
 private:
  Vec3 _color;
};

// _____________________________________________________________________________
Vec3 SolidTexture::value(float u, float v, const Vec3 &p) const {
  return _color;
}

#endif  // SRC_SOLIDTEXTURE_H_
