#include <set>
#include <type_traits>

#include <utl/type_id.hpp>

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
    utl::init::TypeID::LAZY>;

class FamilyStatic {};

using TypeIDStatic = utl::TypeID<
    FamilyStatic,
    int,
    utl::init::TypeID::STATIC>;

} // namespace

TEST(different_families) {
    ASSERT(std::is_same_v<TypeIDA::Index, TypeIDB::Index>)

    std::set<TypeIDA::Index> a{
        TypeIDA::get<bool>().get_index(),
        TypeIDA::get<char>().get_index(),
        TypeIDA::get<const bool>().get_index(),
        TypeIDA::get<bool>().get_index(),
        TypeIDA::get<char>().get_index(),
        TypeIDA::get<const bool>().get_index()
    };
    ASSERT(a == std::set<TypeIDA::Index>{0, 1, 2})

    std::set<TypeIDB::Index> b{
        TypeIDB::get<void>().get_index(),
        TypeIDB::get<double>().get_index(),
        TypeIDB::get<const double>().get_index(),
        TypeIDB::get<void>().get_index(),
        TypeIDB::get<double>().get_index(),
        TypeIDB::get<const double>().get_index()
    };
    ASSERT(a == std::set<TypeIDB::Index>{0, 1, 2})

    ASSERT(a == b)
}

TEST(lazy_initialization) {
    ASSERT(TypeIDLazy::get_types_count() == 0)

    std::set<TypeIDLazy::Index> indices{
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

    std::set<TypeIDStatic::Index> indices{
        TypeIDStatic::get<void>().get_index(),
        TypeIDStatic::get<void>().get_index(),
        TypeIDStatic::get<bool>().get_index(),
        TypeIDStatic::get<char>().get_index(),
        TypeIDStatic::get<int>().get_index()
    };
    ASSERT(indices == std::set<TypeIDStatic::Index>{0, 1, 2, 3})

    ASSERT(TypeIDStatic::get_types_count() == 4)
}
