#define CATCH_CONFIG_MAIN

#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"
#include "catch.hpp"

TEST_CASE ("Testing a number of components")
{
  MBRSHI002::PGMimageProcessor pgm = MBRSHI002::PGMimageProcessor("./images/chess.pgm");
  
  REQUIRE(pgm.extractComponents(200, 50) == 6);
// REQUIRE(factorial(1) == 1);
// REQUIRE(factorial(2) == 2);
// REQUIRE(factorial(3) == 6);
// REQUIRE(factorial(10) == 3628800);
}

