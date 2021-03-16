#ifndef UTL_RANGE_HPP
#define UTL_RANGE_HPP

namespace utl {

template <typename TValue>
class Range {
public:
    using Value = TValue;

    class Iterator;

    class End {
    public:
        explicit End(Value value)
            : m_value{value} {
        }

    private:
        Value m_value;

        friend class Iterator;

    };

    class Iterator {
    public:
        Iterator(Value initial_value, Value step)
            : m_value{initial_value}
            , m_step{step} {
        }

        Value operator*() const {
            return m_value;
        }

        Iterator &operator++() {
            m_value += m_step;
            return *this;
        }

        bool operator!=(const End &end) const {
            if (m_step > Value{0}) {
                return m_value < end.m_value;
            }
            return m_value > end.m_value;
        }

    private:
        Value m_value;
        Value m_step;

    };

    explicit Range(Value length)
        : Range(Value{0}, length, Value{1}) {
    }

    Range(Value begin, Value end, Value step = Value{1})
        : m_begin{begin}
        , m_end{end}
        , m_step{step} {
    }

    Iterator begin() const {
        return Iterator{m_begin, m_step};
    }

    End end() const {
        return End{m_end};
    }

private:
    Value m_begin;
    Value m_end;
    Value m_step;

};

} // namespace utl

#endif // UTL_RANGE_HPP
