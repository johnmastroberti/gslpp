#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "vector.hpp"
using namespace gsl;

TEST_CASE("initializer list construction", "[vector]") {
  Vector v{1,2,3};

  REQUIRE( v.size() == 3 );
}

TEST_CASE("arithmetic", "[vector]") {
  Vector v{1,2,3};

  REQUIRE( v * 3 == Vector{3,6,9} );
}
