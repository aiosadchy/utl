#include <utl/type_id.hpp>

#include <set>
#include <type_traits>

#include "test.hpp"


namespace {

class FamilyA {};

class FamilyB {};

using TypeIDA = utl::TypeID<FamilyA>;
using TypeIDB = utl::TypeID<FamilyB>;

class FamilyLazy {};

using TypeIDLazy = utl::TypeID<
    FamilyLazy,
    int,
    utl::type_traits::Identity,
    utl::init::TypeID::LAZY
>;

class FamilyStatic {};

using TypeIDStatic = utl::TypeID<
    FamilyStatic,
    int,
    utl::type_traits::Identity,
    utl::init::TypeID::STATIC
>;

class FamilyDecay {};

using TypeIDDecay = utl::TypeID<
    FamilyDecay,
    int,
    std::remove_const_t
>;

} // namespace

TEST(different_families) {
    ASSERT(std::is_same_v<TypeIDA::Index, TypeIDB::Index>)

    std::set<TypeIDA::Index> a {
        TypeIDA::get<bool>().get_index(),
        TypeIDA::get<char>().get_index(),
        TypeIDA::get<int>().get_index(),
        TypeIDA::get<bool>().get_index(),
        TypeIDA::get<char>().get_index(),
        TypeIDA::get<int>().get_index()
    };
    ASSERT(a == std::set<TypeIDA::Index>{0, 1, 2})

    std::set<TypeIDB::Index> b {
        TypeIDB::get<void>().get_index(),
        TypeIDB::get<char>().get_index(),
        TypeIDB::get<double>().get_index(),
        TypeIDB::get<void>().get_index(),
        TypeIDB::get<char>().get_index(),
        TypeIDB::get<double>().get_index()
    };
    ASSERT(a == std::set<TypeIDB::Index>{0, 1, 2})

    ASSERT(a == b)
}

TEST(lazy_initialization) {
    ASSERT(TypeIDLazy::get_types_count() == 0)

    std::set<TypeIDLazy::Index> indices {
        TypeIDLazy::get<short>().get_index(),
        TypeIDLazy::get<short>().get_index(),
        TypeIDLazy::get<unsigned>().get_index(),
        TypeIDLazy::get<long>().get_index()
    };
    ASSERT(indices == std::set<TypeIDLazy::Index>{0, 1, 2})

    ASSERT(TypeIDLazy::get_types_count() == 3)
}

TEST(static_initialization) {
    ASSERT(TypeIDStatic::get_types_count() == 4)

    std::set<TypeIDStatic::Index> indices {
        TypeIDStatic::get<void>().get_index(),
        TypeIDStatic::get<void>().get_index(),
        TypeIDStatic::get<bool>().get_index(),
        TypeIDStatic::get<char>().get_index(),
        TypeIDStatic::get<int>().get_index()
    };
    ASSERT(indices == std::set<TypeIDStatic::Index>{0, 1, 2, 3})

    ASSERT(TypeIDStatic::get_types_count() == 4)
}

TEST(decay) {
    std::set<TypeIDDecay::Index> indices {
        TypeIDDecay::get<long>().get_index(),
        TypeIDDecay::get<long>().get_index(),
        TypeIDDecay::get<const long>().get_index(),
        TypeIDDecay::get<bool>().get_index(),
        TypeIDDecay::get<bool>().get_index(),
        TypeIDDecay::get<const bool>().get_index(),
        TypeIDDecay::get<volatile bool>().get_index(),
        TypeIDDecay::get<volatile long>().get_index()
    };
    ASSERT(indices == std::set<TypeIDDecay::Index>{0, 1, 2, 3})

    ASSERT(TypeIDDecay::get_types_count() == 4)
}

TEST_MAIN
