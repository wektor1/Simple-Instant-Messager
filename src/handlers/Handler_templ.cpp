#include "Handler_templ.h"
#include "HandlersExceptions.h"

template <typename T> Handler<T>::~Handler() {}

template <typename T> bool Handler<T>::objectInQueue() const {
  std::lock_guard<std::mutex> lockQueue(m_queueMutex);
  return !m_queue.empty();
}

template <typename T> void Handler<T>::objectToQueue(const T obj) {
  std::lock_guard<std::mutex> lockQueue(m_queueMutex);
  m_queue.push(obj);
}

template <typename T> T Handler<T>::processFirst() {
  if (!objectInQueue()) {
    throw EmptyQueueException("Empty queue");
  }
  std::lock_guard<std::mutex> lockQueue(m_queueMutex);
  T obj = m_queue.front();
  m_queue.pop();
  return obj;
}
