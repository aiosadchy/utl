#ifndef UTL_RANGE_HPP
#define UTL_RANGE_HPP

namespace utl {

template <typename TValue>
class Range {
public:
    using Value = TValue;

    class End {};

    class Iterator {
    public:
        Iterator(Value initial_value, Value end, Value step)
            : m_value{initial_value}
            , m_end{end}
            , m_step{step} {
        }

        Value operator*() const {
            return m_value;
        }

        Iterator &operator++() {
            m_value += m_step;
            return *this;
        }

        bool operator!=(const End) const {
            if (Value{0} < m_step) {
                return m_value < m_end;
            }
            if (m_step < Value{0}) {
                return m_end < m_value;
            }
            return false;
        }

    private:
        Value m_value;
        Value m_end;
        Value m_step;
    };

    explicit Range(Value length)
        : Range{Value{0}, length, Value{1}} {
    }

    Range(Value begin, Value end, Value step = Value{1})
        : m_begin{begin}
        , m_end{end}
        , m_step{step} {
    }

    Iterator begin() const {
        return Iterator{m_begin, m_end, m_step};
    }

    End end() const {
        return End{};
    }

private:
    Value m_begin;
    Value m_end;
    Value m_step;
};

template <typename TValue>
Range<TValue> range(TValue length) {
    return Range{length};
}

template <typename TValue>
Range<TValue> range(TValue begin, TValue end, TValue step = TValue{1}) {
    return Range{begin, end, step};
}

} // namespace utl

#endif // UTL_RANGE_HPP
