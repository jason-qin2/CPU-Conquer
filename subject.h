#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "info.h"

class Observer;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);  
  void notifyObservers();
  virtual Info getInfo() = 0;
};

#endif
