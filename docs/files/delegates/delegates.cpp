#include "delegates.h"

#include <cassert>

int add(int a, int b) {
    return a + b;
}

struct Math {
    static int add(int a, int b) {
        return a + b;
    }
    int diff(int a, int b) {
        return a - b;
    }
    int cdiff(int a, int b) const {
        return a - b;
    }
};

struct AddOp {
    int operator()(int a, int b) {
        return a + b;
    }
};

struct ConstAddOp {
    int operator()(int a, int b) const {
        return a + b;
    }
};

int overloaded(double /*x*/) {
    return 0;
}

int overloaded(const std::string& /*s*/) {
    return 1;
}

int main() {

    /* compiler error!
     * auto override1 = make_delegate(&override, &Override::f);
     */

    auto addFn = make_delegate(add);
    assert(addFn(1, 2) == 3);

    // wrapping a static function member
    auto staticAddFnMem = make_delegate(Math::add);
    assert(staticAddFnMem(1, 2) == 3);

    // wrapping a non-static function member
    Math math;
    auto diffFnMem = make_delegate(&math, &Math::diff);
    assert(diffFnMem(3, 2) == 1);

    // wrapping a function object /2
    AddOp addOp;
    auto addOpAsFnObj = make_delegate(addOp);
    assert(addOpAsFnObj(1, 2) == 3);

    // wrapping a lambda
    auto add_ = [](int a, int b) { return a + b; };
    auto lambda = make_delegate(add_);
    assert(lambda(1, 2) == 3);

    // wrapping a temporary lambda
    auto lambda2 = make_delegate([](int a, int b) { return a + b; });
    assert(lambda2(1, 2) == 3);

    // wrapping a const function object
    ConstAddOp constAddOp;
    auto constAddOpAsFnObj = make_delegate(constAddOp);
    assert(constAddOpAsFnObj(1, 2) == 3);

    // wrapping a const non-static function member
    auto cdiffFnMem = make_delegate(&math, &Math::cdiff);
    assert(cdiffFnMem(3, 2) == 1);

    /* won't compile
     * auto overloaded1 = make_delegate(overloaded);
     */
  
    auto overloaded2 =
		make_delegate(static_cast<int (*)(double)>(overloaded));
    assert(overloaded2(3.14) == 0);
  
    auto overloaded3 =
		make_delegate(static_cast<int (*)(const std::string&)>(overloaded));
    assert(overloaded3("acme") == 1);

    return 0;
}
