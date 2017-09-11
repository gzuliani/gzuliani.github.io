#include <cassert>
#include <tuple>

enum Input {
    PET,
    FEED,
    TIME_PASSES,
};

enum Output {
    PURRS,
    THROWS_UP,
    RUBS,
    BITES,
    UNDEFINED
};

struct State {
    using Result = std::pair<State, Output>;
    using Fn = Result(*)(Input);
    Fn fn_;
    State(Fn fn) : fn_(fn) {}
    Result operator()(Input input) { return fn_(input); }
    bool operator==(Fn fn) const { return fn_ == fn; }
};

State::Result HAPPY(Input);
State::Result HUNGRY(Input);
State::Result DEAD(Input);

State::Result HAPPY(Input input) {
    if (input == PET)
        return State::Result(HAPPY, PURRS);
    else if (input == FEED)
        return State::Result(HAPPY, THROWS_UP);
    else if (input == TIME_PASSES)
        return State::Result(HUNGRY, RUBS);
    else
        throw std::runtime_error("invalid cat state");
}

State::Result HUNGRY(Input input) {
    if (input == PET)
        return State::Result(HUNGRY, BITES);
    else if (input == FEED)
        return State::Result(HAPPY, PURRS);
    else if (input == TIME_PASSES)
        return State::Result(DEAD, UNDEFINED);
    else
        throw std::runtime_error("invalid cat state");
}

State::Result DEAD(Input) {
    throw std::runtime_error("cat is dead");
}

int main() {
    State cat = HAPPY;
    Output output = UNDEFINED;

    std::tie(cat, output) = cat(PET);
    assert(cat == HAPPY);
    assert(output == PURRS);

    std::tie(cat, output) = cat(FEED);
    assert(cat == HAPPY);
    assert(output == THROWS_UP);

    std::tie(cat, output) = cat(TIME_PASSES);
    assert(cat == HUNGRY);
    assert(output == RUBS);

    std::tie(cat, output) = cat(PET);
    assert(cat == HUNGRY);
    assert(output == BITES);

    std::tie(cat, output) = cat(FEED);
    assert(cat == HAPPY);
    assert(output == PURRS);

    std::tie(cat, output) = cat(TIME_PASSES);
    assert(cat == HUNGRY);
    assert(output == RUBS);

    std::tie(cat, output) = cat(TIME_PASSES);
    assert(cat == DEAD);
    assert(output == UNDEFINED);
}
