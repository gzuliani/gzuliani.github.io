#include <cassert>
#include <stdexcept>

void f(int i) {
    if (i < 0)
        throw std::out_of_range("negative value");
    else if (i % 2 == 1)
        throw std::invalid_argument("odd value");
    // do something with i...
}

void g(double a, double b) {
    if (a > b)
        throw std::invalid_argument("a greater than b");
    else if (a == 0)
        throw std::domain_error("a is zero");
    // do something with a and b...
}

// step 1: explicit capture

enum RESPONSE {
    OK,
    INVALID_ARGUMENT,
    OUT_OF_RANGE,
    DOMAIN_ERROR,
    UNKNOWN_ERROR,
};

extern "C" RESPONSE f_(int i) {
    try {
        f(i);
        return OK;
    } catch (const std::invalid_argument&) {
        return INVALID_ARGUMENT;
    } catch (const std::out_of_range&) {
        return OUT_OF_RANGE;
    } catch (...) {
        return UNKNOWN_ERROR;
    }
}

extern "C" RESPONSE g_(double a, double b) {
    try {
        g(a, b);
        return OK;
    } catch (const std::invalid_argument&) {
        return INVALID_ARGUMENT;
    } catch (const std::domain_error&) {
        return DOMAIN_ERROR;
    } catch (...) {
        return UNKNOWN_ERROR;
    }
}

// step 2: macro-based capture

#define BEGIN_C_BOUNDARY \
    try {

#define END_C_BOUNDARY \
        return OK; \
    } \
    catch (const std::invalid_argument&) { \
        return INVALID_ARGUMENT; \
    } catch (const std::out_of_range&) { \
        return OUT_OF_RANGE; \
    } catch (const std::domain_error&) { \
        return DOMAIN_ERROR; \
    } catch (...) { \
        return UNKNOWN_ERROR; \
    }

extern "C" RESPONSE f_macro(int i) {
BEGIN_C_BOUNDARY
    f(i);
END_C_BOUNDARY
}

extern "C" RESPONSE g_macro(double a, double b) {
BEGIN_C_BOUNDARY
    g(a, b);
END_C_BOUNDARY
}

// step 3. function-based capture

RESPONSE error_code_from_exception() noexcept {
    try {
        if (std::current_exception())
            throw; // re-throw the current exception
        else
            return OK;
    } catch (const std::invalid_argument&) {
        return INVALID_ARGUMENT;
    } catch (const std::out_of_range&) {
        return OUT_OF_RANGE;
    } catch (const std::domain_error&) {
        return DOMAIN_ERROR;
    } catch (...) {
        return UNKNOWN_ERROR;
    }
}

extern "C" RESPONSE f_lippincott(int i) {
    try {
        f(i);
        return OK;
    }
    catch (...) {
        return error_code_from_exception();
    }
}

extern "C" RESPONSE g_lippincott(double a, double b) {
    try {
        g(a, b);
        return OK;
    }
    catch (...) {
        return error_code_from_exception();
    }
}

// step 4. wrapping the code in lambda functions

template <typename F>
RESPONSE lippincott(F&& f) noexcept {
    try {
        f();
        return OK;
    } catch (...) {
        return error_code_from_exception();
    }
}

extern "C" RESPONSE f_lippincott_lambda(int i) {
    return lippincott([&]{
        f(i);
    });
}

extern "C" RESPONSE g_lippincott_lambda(double a, double b) {
    return lippincott([&]{
        g(a, b);
    });
}

// step 5. syntactic sugar

struct ErrorCodeFromException {
    template <typename F>
    RESPONSE operator+(F&& f) {
        return lippincott(f);
    }
};

#define ERROR_CODE_FROM_EXCEPTION \
    ErrorCodeFromException() + [&]

extern "C" RESPONSE f_lippincott_final(int i) {
    return ERROR_CODE_FROM_EXCEPTION { f(i); };
}

extern "C" RESPONSE g_lippincott_final(double a, double b) {
    return ERROR_CODE_FROM_EXCEPTION { g(a, b); };
}

int main() {
    assert(f_(42) == OK);
    assert(f_(-1) == OUT_OF_RANGE);
    assert(f_(11) == INVALID_ARGUMENT);

    assert(g_(1, 1) == OK);
    assert(g_(2, 1) == INVALID_ARGUMENT);
    assert(g_(0, 1) == DOMAIN_ERROR);

    assert(f_macro(42) == OK);
    assert(f_macro(-1) == OUT_OF_RANGE);
    assert(f_macro(11) == INVALID_ARGUMENT);

    assert(g_macro(1, 1) == OK);
    assert(g_macro(2, 1) == INVALID_ARGUMENT);
    assert(g_macro(0, 1) == DOMAIN_ERROR);

    assert(f_lippincott(42) == OK);
    assert(f_lippincott(-1) == OUT_OF_RANGE);
    assert(f_lippincott(11) == INVALID_ARGUMENT);

    assert(g_lippincott(1, 1) == OK);
    assert(g_lippincott(2, 1) == INVALID_ARGUMENT);
    assert(g_lippincott(0, 1) == DOMAIN_ERROR);

    assert(f_lippincott_lambda(42) == OK);
    assert(f_lippincott_lambda(-1) == OUT_OF_RANGE);
    assert(f_lippincott_lambda(11) == INVALID_ARGUMENT);

    assert(g_lippincott_lambda(1, 1) == OK);
    assert(g_lippincott_lambda(2, 1) == INVALID_ARGUMENT);
    assert(g_lippincott_lambda(0, 1) == DOMAIN_ERROR);

    assert(f_lippincott_final(42) == OK);
    assert(f_lippincott_final(-1) == OUT_OF_RANGE);
    assert(f_lippincott_final(11) == INVALID_ARGUMENT);

    assert(g_lippincott_final(1, 1) == OK);
    assert(g_lippincott_final(2, 1) == INVALID_ARGUMENT);
    assert(g_lippincott_final(0, 1) == DOMAIN_ERROR);

    return 0;
}
