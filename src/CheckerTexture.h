// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_CHECKERTEXTURE_H_
#define SRC_CHECKERTEXTURE_H_

#include <math.h>  // sin

#include "Texture.h"
#include "Vec3.h"

class CheckerTexture: public Texture {
 public:
  CheckerTexture() {}
  CheckerTexture(Texture *t0, Texture *t1, float i) : _even(t0),
                                                      _odd(t1),
                                                      _interval(i) {}
  ~CheckerTexture();

  virtual Vec3 value(float u, float v, const Vec3 &p) const;
 private:
  Texture *_even;
  Texture *_odd;
  float _interval;
};

CheckerTexture::~CheckerTexture() {
  delete _even;
  delete _odd;
}

// _____________________________________________________________________________
Vec3 CheckerTexture::value(float u, float v, const Vec3 &p) const {
  // Not quite sure how this functions, but let's see
  auto sinesD = sin(_interval*p.x())*sin(_interval*p.y())*sin(_interval*p.z());
  float sines = static_cast<float>(sinesD);

  if (sines < 0.f) return _odd->value(u, v, p);
  else
    return _even->value(u, v, p);
}

#endif  // SRC_CHECKERTEXTURE_H_
