#pragma once

#include "HandlersExceptions.h"
#include <queue>
#include <mutex>

template <typename T> class Handler {
public:
  virtual ~Handler();
  bool objectInQueue() const;
  void objectToQueue(const T obj);
  T processFirst();

private:
  mutable std::mutex m_queueMutex;
  std::queue<T> m_queue;
};
