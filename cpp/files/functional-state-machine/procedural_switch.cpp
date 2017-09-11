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

Output cat(Input input) {
    switch (state) {
        case HAPPY:
            switch (input) {
                case PET:
                    state = HAPPY;
                    return PURRS;
                    break;
                case FEED:
                    state = HAPPY;
                    return THROWS_UP;
                    break;
                case TIME_PASSES:
                    state = HUNGRY;
                    return RUBS;
                    break;
            }
            break;
        case HUNGRY:
            switch (input) {
                case PET:
                    state = HUNGRY;
                    return BITES;
                    break;
                case FEED:
                    state = HAPPY;
                    return PURRS;
                    break;
                case TIME_PASSES:
                    state = DEAD;
                    return UNDEFINED;
                    break;
            }
            break;
        case DEAD:
            throw std::runtime_error("cat is dead");
    }
    throw std::runtime_error("invalid cat state");
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
