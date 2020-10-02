#ifndef UTL_RANGE_HPP
#define UTL_RANGE_HPP

template <typename T>
class Range {
public:
    class Iterator;

    class End {
    public:
        explicit End(T value)
            : m_value(value) {
        }

    private:
        T m_value;

        friend class Iterator;

    };

    class Iterator {
    public:
        Iterator(T initial_value, T step)
            : m_value(initial_value)
            , m_step(step) {
        }

        T operator*() const {
            return m_value;
        }

        Iterator &operator++() {
            m_value += m_step;
            return *this;
        }

        bool operator!=(const End &end) const {
            if (m_step > T(0)) {
                return m_value < end.m_value;
            }
            return m_value > end.m_value;
        }

    private:
        T m_value;
        T m_step;

    };

    explicit Range(T length)
        : Range(T(0), length, T(1)) {
    }

    Range(T begin, T end, T step = T(1))
        : m_begin(begin)
        , m_end(end)
        , m_step(step) {
    }

    Iterator begin() const {
        return Iterator(m_begin, m_step);
    }

    End end() const {
        return End(m_end);
    }

private:
    T m_begin;
    T m_end;
    T m_step;

};

#endif // UTL_RANGE_HPP
