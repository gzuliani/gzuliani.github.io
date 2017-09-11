#include <algorithm>
#include <cassert>
#include <stdexcept>

enum State {
    HAPPY,
    HUNGRY,
    DEAD,
};

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

static State state;

struct Entry {
    State source_;
    Input input_;
    State destination_;
    Output output_;
    bool matches(State source, Input input) const {
        return source_ == source && input_ == input;
    }
};

const Entry table[] = {
    { HAPPY,  PET,         HAPPY,  PURRS     },
    { HAPPY,  FEED,        HAPPY,  THROWS_UP },
    { HAPPY,  TIME_PASSES, HUNGRY, RUBS      },
    { HUNGRY, FEED,        HAPPY,  PURRS     },
    { HUNGRY, PET,         HUNGRY, BITES     },
    { HUNGRY, TIME_PASSES, DEAD,   UNDEFINED },
};

const int entries = sizeof(table) / sizeof(table[0]);

Output cat(Input input) {
    const auto entry = std::find_if(
        std::begin(table), std::end(table),
        [&](const Entry& entry) { return entry.matches(state, input); });

    if (entry == std::end(table))
        throw std::runtime_error("unexpected state/input pair");

    state = entry->destination_;
    return entry->output_;
}

int main() {
    state = HAPPY;

    assert(cat(PET) == PURRS);
    assert(state == HAPPY);

    assert(cat(FEED) == THROWS_UP);
    assert(state == HAPPY);

    assert(cat(TIME_PASSES) == RUBS);
    assert(state == HUNGRY);

    assert(cat(PET) == BITES);
    assert(state == HUNGRY);

    assert(cat(FEED) == PURRS);
    assert(state == HAPPY);

    assert(cat(TIME_PASSES) == RUBS);
    assert(state == HUNGRY);

    assert(cat(TIME_PASSES) == UNDEFINED);
    assert(state == DEAD);
}
