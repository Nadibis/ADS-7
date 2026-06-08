// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}
Train::~Train() {
  if (first == nullptr) return;
  Car* current = first;
  Car* next;
  do {
    next = current->next;
    delete current;
    current = next;
  } while (current != first);
}
void Train::addCar(bool light) {
  Car* newCar = new Car;
  newCar->light = light;
  newCar->next = nullptr;
  newCar->prev = nullptr;

  if (first == nullptr) {
    first = newCar;
    newCar->next = newCar;
    newCar->prev = newCar;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}
int Train::getLength() {
  if (first == nullptr) return 0;
  countOp = 0;
  first->light = true;
  int totalSteps = 0;      // общее число переходов
  int memorizedLen = 0;    // сколько вагонов прошли не меняя направление
  Car* current = first;
  while (true) {
    current = current->next;
    countOp++;
    totalSteps++;
    memorizedLen++;
    if (current->light == false) {
      continue;
    } else {
      current->light = false;
      for (int i = 0; i < memorizedLen; i++) { // назад на memorizedLen шагов
        current = current->prev;
        countOp++;
      }
    if (first->light == true) {
        memorizedLen = 0;
    } else {
        return memorizedLen + 1;
      }
    }
  }
}

int Train::getOpCount() const {
  return countOp;
}
