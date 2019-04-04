// Copyright (c) 2019, University of Freiburg.
// Author: Haralambi Todorov <harrytodorov@gmail.com>

#ifndef SRC_HITABLELIST_H_
#define SRC_HITABLELIST_H_

#include <iostream>

#include "Hitable.h"
#include "AABB.h"

class HitableList: public Hitable {
 public:
  HitableList();
  explicit HitableList(int capacity);
  HitableList(const HitableList &l) = delete;
  HitableList& operator=(const HitableList &l) = delete;
  ~HitableList();

  inline int size() const { return _size; }
  inline int capacity() const { return _capacity; }
  inline int is_empty() const {return _size == 0; }

  Hitable* operator[](int i);

  void append(Hitable *hitable);
  void clear(Hitable **array);
  void sort_in_range(int axis, int min, int max);

  bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const;
  bool bounding_box(AABB &box) const;

 private:
  int _size{0};
  int _capacity{8};
  Hitable **_data{nullptr};
};

// _____________________________________________________________________________
HitableList::HitableList() {
  _data = new Hitable*[_capacity];
}

// _____________________________________________________________________________
HitableList::HitableList(int capacity) {
    if (_capacity > 0) {
      _size = 0;
      _capacity = capacity;
      _data = new Hitable*[_capacity];
    }
}

// _____________________________________________________________________________
HitableList::~HitableList() {
  clear(_data);
}

// _____________________________________________________________________________
Hitable* HitableList::operator[](int i) {
  if (i >= 0 && i < _size) {
    return _data[i];
  }
  return nullptr;
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

// _____________________________________________________________________________
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
int aabb_x_cmp(const void *a, const void *b) {
  // Get pointers to the Hitable element
  Hitable *ha = *(Hitable**)a;
  Hitable *hb = *(Hitable**)b;
  AABB a_box, b_box;

  // Check, if the elements have bounding boxes
  if (!ha->bounding_box(a_box) ||
      !hb->bounding_box(b_box)) {
    std::cout << "No Bounding box; cannot compare elements" << std::endl;
    return 0;
  }

  // Sort by x ascending
  if (a_box.min().x() - b_box.min().x() < 0.f) return -1;
  else if (a_box.min().x() - b_box.min().x() > 0.f) return 1;
  else return 0;
}

// _____________________________________________________________________________
int aabb_y_cmp(const void *a, const void *b) {
  // Get pointers to the Hitable element
  Hitable *ha = *(Hitable**)a;
  Hitable *hb = *(Hitable**)b;
  AABB a_box, b_box;

  // Check, if the elements have bounding boxes
  if (!ha->bounding_box(a_box) ||
      !hb->bounding_box(b_box)) {
    std::cout << "No Bounding box; cannot compare elements" << std::endl;
    return 0;
  }

  // Sort by x ascending
  if (a_box.min().y() - b_box.min().y() < 0.f) return -1;
  else if (a_box.min().y() - b_box.min().y() > 0.f) return 1;
  else return 0;
}

// _____________________________________________________________________________
int aabb_z_cmp(const void *a, const void *b) {
  // Get pointers to the Hitable element
  Hitable *ha = *(Hitable**)a;
  Hitable *hb = *(Hitable**)b;
  AABB a_box, b_box;

  // Check, if the elements have bounding boxes
  if (!ha->bounding_box(a_box) ||
      !hb->bounding_box(b_box)) {
    std::cout << "No Bounding box; cannot compare elements" << std::endl;
    return 0;
  }

  // Sort by x ascending
  if (a_box.min().z() - b_box.min().z() < 0.f) return -1;
  else if (a_box.min().z() - b_box.min().z() > 0.f) return 1;
  else return 0;
}

// _____________________________________________________________________________
void HitableList::sort_in_range(int axis, int min, int max) {
  int number_elements = max - min;
  // x axis
  if (axis == 0) {
    qsort(_data + min, number_elements, sizeof(Hitable*), aabb_x_cmp);
  // y axis
  } else if (axis == 1) {
    qsort(_data + min, number_elements, sizeof(Hitable*), aabb_y_cmp);
  // z axis
  } else {
    qsort(_data + min, number_elements, sizeof(Hitable*), aabb_z_cmp);
  }
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

// _____________________________________________________________________________
bool HitableList::bounding_box(AABB &box) const {
  if (_size < 1) return false;

  // Get the bounding box of the first element
  AABB temp_box;

  for (int i = 0; i < _size; i++) {
    if (_data[i]->bounding_box(temp_box)) {
      box = surrounding_box(temp_box, box);
    } else {
      return false;
    }
  }
  return true;
}

#endif  // SRC_HITABLELIST_H_
