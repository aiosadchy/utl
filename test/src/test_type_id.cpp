#include <utl/type_id.hpp>

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


TEST_MAIN
