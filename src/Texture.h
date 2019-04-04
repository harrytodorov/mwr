// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_TEXTURE_H_
#define SRC_TEXTURE_H_

#include "Vec3.h"

class Texture {
 public:
  Texture() {}
  virtual ~Texture() {}
  virtual Vec3 value(float u, float v, const Vec3 &p) const = 0;
};

#endif  // SRC_TEXTURE_H_
