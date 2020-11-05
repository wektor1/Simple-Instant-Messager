#include "Handler_templ.h"
#include "HandlersExceptions.h"

template <typename T> Handler<T>::~Handler() {}

template <typename T> bool Handler<T>::objectInQueue() const {
  return !m_queue.empty();
}

template <typename T> void Handler<T>::objectToSend(const T obj) {
  m_queue.push(obj);
}

template <typename T> T Handler<T>::processFirst() {
  if (!objectInQueue()) {
    throw EmptyQueueException("Empty queue");
  }
  T obj = m_queue.front();
  m_queue.pop();
  return obj;
}
