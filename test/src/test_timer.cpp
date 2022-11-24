#include <utl/timer.hpp>

#include "test.hpp"


TEST(timer) {
    using Timer = utl::Timer<std::chrono::high_resolution_clock>;

    constexpr int ITERATIONS = 100000;

    Timer t;

    Timer::Duration d0;

    ASSERT(d0.to_nanoseconds() == 0)

    volatile int i;

    for (i = 0; i < ITERATIONS; ++i) {
        d0 = t.get_time();
    }

    Timer::Duration d1 = t.get_time();

    ASSERT(d1.to_nanoseconds() > 0)
    ASSERT(d1.to_nanoseconds()  / 1000 == d1.to_microseconds())
    ASSERT(d1.to_microseconds() / 1000 == d1.to_milliseconds())
    ASSERT(d1.to_milliseconds() / 1000 == d1.to_seconds()     )

    Timer::Duration d2 = t.restart();

    ASSERT(d2.to_nanoseconds() >= d1.to_nanoseconds())

    Timer::Duration d3 = t.get_time();

    ASSERT(d2.to_nanoseconds() > d3.to_nanoseconds())
}
