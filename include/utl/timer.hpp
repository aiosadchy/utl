#ifndef UTL_TIMER_HPP
#define UTL_TIMER_HPP

#include <chrono>

namespace utl {

template <typename TClock>
class Timer {
public:
    using Clock = TClock;

    class Duration {
    public:
        Duration()
            : m_duration{Clock::duration::zero()} {
        }

        template <typename TDuration>
        explicit Duration(const TDuration &duration)
            : m_duration{
                std::chrono::duration_cast<typename Clock::duration>(duration)
            } {
        }

        template <typename TDuration>
        [[nodiscard]] typename TDuration::rep to() const {
            return std::chrono::duration_cast<TDuration>(m_duration).count();
        }

        [[nodiscard]] std::chrono::seconds::rep to_seconds() const {
            return to<std::chrono::seconds>();
        }

        [[nodiscard]] std::chrono::milliseconds::rep to_milliseconds() const {
            return to<std::chrono::milliseconds>();
        }

        [[nodiscard]] std::chrono::microseconds::rep to_microseconds() const {
            return to<std::chrono::microseconds>();
        }

        [[nodiscard]] std::chrono::nanoseconds::rep to_nanoseconds() const {
            return to<std::chrono::nanoseconds>();
        }

    private:
        typename Clock::duration m_duration;
    };

    Timer()
        : m_time_point{Clock::now()} {
    }

    [[nodiscard]] Duration get_time() const {
        return Duration{Clock::now() - m_time_point};
    }

    Duration restart() {
        typename Clock::time_point past = m_time_point;
        m_time_point = Clock::now();
        return Duration{m_time_point - past};
    }

private:
    typename Clock::time_point m_time_point;
};

} // namespace utl

#endif // UTL_TIMER_HPP
