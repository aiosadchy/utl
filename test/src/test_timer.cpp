#include <utl/timer.hpp>

#include <chrono>
#include <thread>

#include "test.hpp"


TEST(timer) {
    using Timer = utl::Timer<std::chrono::high_resolution_clock>;

    Timer t;

    Timer::Duration d0;

    ASSERT(d0.to_nanoseconds() == 0)

    std::this_thread::sleep_for(std::chrono::milliseconds{10});

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
