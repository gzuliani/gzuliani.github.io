#include "gut.h"
#include "gut-num.h"

const double pi = 3.141592653;

TEST("return true if in-range") {
	CHECK( gut::num::areAlmostEqual(pi, 3.141));
}

TEST("return false if out-of-tolerance") {
	CHECK(!gut::num::areAlmostEqual(pi, 3.14));
}
