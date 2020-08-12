#ifndef BASE_COUNTDOWNLATCH_H
#define BASE_COUNTDOWNLATCH_H

#include "Condition.h"
#include "MutexLock.h"
#include "noncopyable.h"

namespace mosfet {

// Use CountDownLatch to ensure:
//
class CountDownLatch : noncopyable {
 public:
  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  void getCount();

 private:
  mutable MutexLock mutex_;
  Condition condition_;
  int count_;
};

} // namespace mosfet

#endif // BASE_COUNTDOWNLATCH_H
