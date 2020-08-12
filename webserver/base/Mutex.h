#ifndef BASE_MUTEX_H
#define BASE_MUETX_H

#include <assert.h>
#include <pthread.h>

#include "noncopyable.h"

namespace mosfet {

class MutexLock : noncopyable {
 public:
  MutexLock() {
    pthread_mutex_init(&mutex_, NULL);
  }
  
  ~MutexLock() {
    pthread_mutex_destroy(&mutex_);
  }
  
  void lock() {
    pthread_mutex_lock(&mutex_);
  }
  
  void unlock() {
    pthread_mutex_unlock(&mutex_);
  }
  
  pthread_mutex_t* getPthreadMutex() {
    return &mutex_;
  }
 private:
  // friend class can use private member in this class
  friend class Condition;
    
  pthread_mutex_t mutex_;
  // pid_t holder_;
};

// Use as a stack variable, eg.
// int Foo::size() const {
//   MutexLockGuard lock(mutex_);
//   return data.size();
// }
class MutexLockGuard : noncopyable {
 public:
  explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex) {
    mutex_.lock();
  }

  ~MutexLockGuard() {
    mutex_.unlock();
  }

 private:
  MutexLock& mutex_;
};


} // namespace mosfet


#endif // BASE_MUTEX_H
