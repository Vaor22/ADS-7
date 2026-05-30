// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (!first) return;
  Car *cur = first->next;
  while (cur != first) {
    Car *tmp = cur->next;
    delete cur;
    cur = tmp;
  }
  delete first;
  first = nullptr;
}

void Train::addCar(bool light) {
  Car *newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    newCar->next = newCar;
    newCar->prev = newCar;
    first = newCar;
  } else {
    Car *last = first->prev;
    newCar->next  = first;
    newCar->prev  = last;
    last->next    = newCar;
    first->prev   = newCar;
  }
}

int Train::getLength() {
  countOp = 0;
  if (!first) return 0;

  Car *cur = first;
  bool wasOn = cur->light;
  cur->light = true;

  int count = 1;
  cur = cur->next;
  countOp++;

  while (cur != first) {
    if (cur->light) {
      cur->light = false;
      countOp++;
    } else {
      cur->light = true;
    }
    cur = cur->next;
    countOp++;
    count++;
  }

  first->light = wasOn;

  return count;
}

int Train::getOpCount() {
  return countOp;
}
