// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_HITABLELIST_H_
#define SRC_HITABLELIST_H_

#include "Hitable.h"

class HitableList: public Hitable {
 public:
  HitableList() = default;
  explicit HitableList(int capacity);
  HitableList(const HitableList &l) = delete;
  HitableList& operator=(const HitableList &l) = delete;
  ~HitableList();

  int size() const { return _size; }
  int capacity() const { return _capacity; }
  int is_empty() const {return _size == 0; }

  void append(Hitable *hitable);
  void clear(Hitable **array);

  bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const;

 private:
  int _size{0};
  int _capacity{8};
  Hitable **_data{nullptr};
};

// _____________________________________________________________________________
HitableList::HitableList(int capacity) {
    if (_capacity > 0) {
      _size = 0;
      _capacity = capacity;
      _data = new Hitable*[capacity];
    }
}

// _____________________________________________________________________________
HitableList::~HitableList() {
  clear(_data);
}

// _____________________________________________________________________________
void HitableList::append(Hitable *hitable) {
  // Check if the new element is not empty
  if (hitable == nullptr) return;

  // Array's capacity should be enlarged
  if (_size >= _capacity) {
    // Double the capacity
    _capacity *= 2;

    // Copy the content
    Hitable **new_data = new Hitable*[_capacity];
    for (int i = 0; i < _size; i++) {
      new_data[i] = _data[i];
    }

    // Delete just the array of pointers, not the actual elements
    // they're pointing to
    delete[] _data;

    // Transfer the ownership of the array to _data
    _data = new_data;
  }

  // Add the new element
  _data[_size] = hitable;
  _size++;
}

void HitableList::clear(Hitable **array) {
  // Go through all Hitable elements and free the memory occupied by them
  for (int i = 0; i < _size; i++) {
    delete array[i];
  }
  // Delete the array
  delete[] array;
  // Set the size to 0
  _size = 0;
}

// _____________________________________________________________________________
bool HitableList::hit(const Ray &r,
                      float t_min,
                      float t_max,
                      HitRecord &rec) const {
  HitRecord temp_rec;
  bool did_hit = false;
  double closest_hit = t_max;
  for (int i = 0; i < _size; i++) {
    if (_data[i]->hit(r, t_min, closest_hit, temp_rec)) {
      did_hit = true;
      closest_hit = temp_rec.t;
      rec = temp_rec;
    }
  }
  return did_hit;
}

#endif  // SRC_HITABLELIST_H_
