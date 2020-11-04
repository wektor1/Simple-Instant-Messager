#include <queue>
#include "HandlersExceptions.h"

template <typename T>
class Handler {
public:
  bool objectInQueue() const { return !m_queue.empty(); }
  void objectToSend(const T obj){
      m_queue.push(obj);
    }
  T processFirst(){
    if (!objectInQueue()) {
      throw EmptyQueueException("Empty queue");
    }
    T obj = m_queue.front();
    m_queue.pop();
    return obj;
  }

private:
  std::queue<T> m_queue;
};
