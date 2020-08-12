#include "CountDownLatch.h"

CountDownLatch::CountDownLatch(int count)
  : mutex_(),
    condition_(mutex_),
    count_(count) {
};

void CountDownLatch::wait() {
  MutexLockGuard lock(mutex_);
  // wait in a loop, in order to avoid spurious weak
  while(count_ > 0) {
    condition_.wait();
  }
}

void CountDownLatch::countDown() {
  MutexLockGuard lock(mutex_);
  --count_;
  if(count_ == 0) {
    condition_.notifyAll();
  }
}

int CountDownLatch::getCount() {
  MutexLockGuard lock(mutex_);
  return count_;
}
