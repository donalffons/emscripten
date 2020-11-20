#include <time.h>
#include <errno.h>
#include <emscripten/threading.h>

int nanosleep(const struct timespec* req, struct timespec* rem) {
  if (!req || req->tv_nsec < 0 || req->tv_nsec > 999999999L || req->tv_sec < 0) {
    errno = EINVAL;
    return -1;
  }
  emscripten_thread_sleep(req->tv_sec * 1000.0 + req->tv_nsec / 1e6);
  return 0;
}

int usleep(unsigned usec) {
  emscripten_thread_sleep(usec / 1e3);
  return 0;
}
