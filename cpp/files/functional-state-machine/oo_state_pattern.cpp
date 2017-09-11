#include <cassert>
#include <memory>
#include <stdexcept>

enum Output {
    PURRS,
    THROWS_UP,
    RUBS,
    BITES,
    UNDEFINED
};

class Cat;

class State {
public:
    virtual bool is_happy() const { return false; }
    virtual bool is_hungry() const { return false; }
    virtual bool is_dead() const { return false; }
    virtual Output pet(Cat& cat) = 0;
    virtual Output feed(Cat& cat) = 0;
    virtual Output time_passes(Cat& cat) = 0;
};

class Happy : public State {
public:
    bool is_happy() const override { return true; }
    Output pet(Cat& cat) override;
    Output feed(Cat& cat) override;
    Output time_passes(Cat& cat) override;
};

class Hungry : public State {
public:
    bool is_hungry() const override { return true; }
    Output pet(Cat& cat) override;
    Output feed(Cat& cat) override;
    Output time_passes(Cat& cat) override;
};

class Dead : public State {
public:
    bool is_dead() const override { return true; }
    Output pet(Cat&) override { throw std::runtime_error("cat is dead"); }
    Output feed(Cat&) override { throw std::runtime_error("cat is dead"); }
    Output time_passes(Cat&) override { throw std::runtime_error("cat is dead"); }
};

class Cat {
    std::unique_ptr<State> state_;
public:
    Cat() : state_(std::make_unique<Happy>()) {}
    bool is_happy() const { return state_->is_happy(); }
    bool is_hungry() const { return state_->is_hungry(); }
    bool is_dead() const { return state_->is_dead(); }
    Output pet() { return state_->pet(*this); }
    Output feed() { return state_->feed(*this); }
    Output time_passes() { return state_->time_passes(*this); }
    template <class T>
    void setState() { state_ = std::make_unique<T>(); }
};

Output Happy::pet(Cat& cat) {
    cat.setState<Happy>();
    return PURRS;
}

Output Happy::feed(Cat& cat) {
    cat.setState<Happy>();
    return THROWS_UP;
}

Output Happy::time_passes(Cat& cat) {
    cat.setState<Hungry>();
    return RUBS;
}

Output Hungry::pet(Cat& cat) {
    cat.setState<Hungry>();
    return BITES;
}

Output Hungry::feed(Cat& cat) {
    cat.setState<Happy>();
    return PURRS;
}

Output Hungry::time_passes(Cat& cat) {
    cat.setState<Dead>();
    return UNDEFINED;
}

int main() {
    Cat cat;
    assert(cat.is_happy());

    assert(cat.pet() == PURRS);
    assert(cat.is_happy());

    assert(cat.feed() == THROWS_UP);
    assert(cat.is_happy());

    assert(cat.time_passes() == RUBS);
    assert(cat.is_hungry());

    assert(cat.pet() == BITES);
    assert(cat.is_hungry());

    assert(cat.feed() == PURRS);
    assert(cat.is_happy());

    assert(cat.time_passes() == RUBS);
    assert(cat.is_hungry());

    assert(cat.time_passes() == UNDEFINED);
    assert(cat.is_dead());
}
