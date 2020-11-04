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
