#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "model.hpp"

TEST_CASE("Testing the tests", "[A]") {
    
    REQUIRE(model() == 1);
    REQUIRE(model() == 2);
    REQUIRE(model() == 3);
}