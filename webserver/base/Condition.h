#ifndef BASE_CONDITION_H
#define BASE_CONDITION_H

#include <errno.h>
#include <pthread.h>
#include <time.h>

#include "noncopyable.h"
#include "MutexLock.h"

namespace mosfet {

class Condition : noncopyable {
 public:
  explicit Condition(MutexLock& mutex) : mutex_(mutex) {
    pthread_cond_init(&cond_, NULL);
  }

  ~Condition() {
    pthread_cond_destroy(&cond_);
  }

  void wait() {
    pthread_cond_wait(&cond_, mutex_.getPthreadMutex());
  }

  void notify() {
    pthread_cond_signal(&cond);
  }

  void notifyAll() {
    pthread_cond_broadcast(&cond_);
  }

  bool waitForSeconds(int seconds) {
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    abstime.tv_sec += static_cast<time_t>(seconds);
    return ETIMEOUT == pthread_cond_timewait(&cond_, mutex_.getPthreadMutex(), &abstime);
  }

 private:
  MutexLock& mutex_;
  pthread_cond_t cond_;
};

} // namespace mosfet

#endif // BASE_CONDITION_H
