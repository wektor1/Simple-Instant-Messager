#pragma once

#include "HandlersExceptions.h"
#include <queue>

template <typename T> class Handler {
public:
  bool objectInQueue() const;
  void objectToSend(const T obj);
  T processFirst();

private:
  std::queue<T> m_queue;
};
