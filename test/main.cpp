#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "vector.hpp"
using namespace gsl;

TEST_CASE("basic", "[vector]") {
  Vector v{5};

  REQUIRE( v.size() == 5 );
}
