#include <utl/type_info.hpp>

#include <set>

#include "test.hpp"


#define TYPE_INFO_CLASS(name, ...)                  \
class name : public utl::TypeInfo<__VA_ARGS__> {    \
public:                                             \
    template <typename T>                           \
    explicit name(Initializer<T>)                   \
        : m_index(s_count++) {                      \
    }                                               \
                                                    \
    unsigned int get_index() const {                \
        return m_index;                             \
    }                                               \
                                                    \
    static unsigned int get_count() {               \
        return s_count;                             \
    }                                               \
                                                    \
private:                                            \
    unsigned int m_index;                           \
                                                    \
    inline static unsigned int s_count{0};          \
                                                    \
};

namespace {

TYPE_INFO_CLASS(
    TIRegular,
    TIRegular
)

TYPE_INFO_CLASS(
    TILazy,
    TILazy,
    utl::type_traits::Identity,
    utl::init::TypeInfo::LAZY
)

TYPE_INFO_CLASS(
    TIStatic,
    TIStatic,
    utl::type_traits::Identity,
    utl::init::TypeInfo::STATIC
)

TYPE_INFO_CLASS(
    TIDecay,
    TIDecay,
    std::decay_t
)

} // namespace

TEST(regular) {
    std::set<unsigned int> types = {
        TIRegular::get<bool>().get_index(),
        TIRegular::get<char>().get_index(),
        TIRegular::get<const char>().get_index(),
        TIRegular::get<bool>().get_index(),
        TIRegular::get<char>().get_index(),
        TIRegular::get<const char>().get_index()
    };
    ASSERT(types.size() == 3)

    ASSERT(TIRegular::get_count() == 3)
}

TEST(lazy_initialization) {
    ASSERT(TILazy::get_count() == 0)

    std::set<unsigned int> types = {
        TILazy::get<short>().get_index(),
        TILazy::get<short>().get_index(),
        TILazy::get<unsigned>().get_index(),
        TILazy::get<long>().get_index()
    };
    ASSERT(types.size() == 3)

    ASSERT(TILazy::get_count() == 3)
}

TEST(static_initialization) {
    ASSERT(TIStatic::get_count() == 4)

    std::set<unsigned int> types = {
        TIStatic::get<void>().get_index(),
        TIStatic::get<void>().get_index(),
        TIStatic::get<bool>().get_index(),
        TIStatic::get<char>().get_index(),
        TIStatic::get<int>().get_index()
    };
    ASSERT(types.size() == 4)

    ASSERT(TIStatic::get_count() == 4)
}

TEST(decay) {
    std::set<unsigned int> indices {
        TIDecay::get<long>().get_index(),
        TIDecay::get<long>().get_index(),
        TIDecay::get<const long>().get_index(),
        TIDecay::get<bool>().get_index(),
        TIDecay::get<bool>().get_index(),
        TIDecay::get<const bool>().get_index(),
        TIDecay::get<volatile bool &>().get_index(),
        TIDecay::get<volatile long &>().get_index()
    };
    ASSERT(indices.size() == 2)

    ASSERT(TIDecay::get_count() == 2)
}

TEST_MAIN
