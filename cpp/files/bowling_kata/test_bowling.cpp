// file: test_bowling.cpp

#include "../gut/current/gut.h"
#include <cassert>
#include <numeric> // accumulate

class Roll {
  int number_;
  int pins_;
public:
  Roll(int number, int pins) : number_(number), pins_(pins) {}
  int number() const { return number_; }
  int pins() const { return pins_; }
  int score() const { return pins_; }
};

using Rolls = std::vector<Roll>;

class Frame {
protected:
  static const int PINS = 10;
  Roll first_roll_;
  enum State {
    e_empty,
    e_incomplete,
    e_complete,
    e_spare,
    e_strike,
  };
  State state_;
public:
  Frame() : first_roll_(-1, 0), state_(e_empty) {}
  virtual void add(const Roll& roll) {
    if (state_ == e_empty) {
      first_roll_ = roll;
      if (first_roll_.pins() == PINS)
        state_ = e_strike;
      else
        state_ = e_incomplete;
    } else if (state_ == e_incomplete) {
      if (roll.pins() + first_roll_.pins() == PINS)
        state_ = e_spare;
      else
        state_ = e_complete;
    }
  }
  virtual bool is_completed() const {
    return state_ == e_complete || state_ == e_spare || state_ == e_strike;
  }
  int score(const Rolls& rolls) const {
    if (state_ == e_incomplete)
      return 0;
    else if (state_ == e_complete)
      return sum_scores(rolls, 2);
    else if ((state_ == e_spare || state_ == e_strike)
        && available_rolls(rolls) > 2)
      return sum_scores(rolls, 3);
    return 0;
  }
private:
  int available_rolls(const Rolls& rolls) const {
    return static_cast<int>(rolls.size()) - first_roll_.number();
  }
  int sum_scores(const Rolls& rolls, int rolls_to_add) const {
    assert(available_rolls(rolls) >= rolls_to_add);
    auto start_pos = rolls.begin() + first_roll_.number();
    return std::accumulate(
      start_pos, start_pos + rolls_to_add, 0,
        [](int a, const Roll& roll) { return a + roll.score(); });
  }
};

class TenthFrame : public Frame {
  int bonus_rolls_;
public:
  TenthFrame() : bonus_rolls_(0) {}
  void add(const Roll& roll) override {
    if (!Frame::is_completed())
      Frame::add(roll);
    else
      ++bonus_rolls_;
  }
  bool is_completed() const override {
    return state_ == e_complete
      || (state_ == e_spare && bonus_rolls_ == 1)
      || (state_ == e_strike && bonus_rolls_ == 2);
  }
};

class Game {
  static const int FRAMES = 10;
  Rolls rolls_;
  using FramePtr = std::shared_ptr<Frame>;
  std::vector<FramePtr> frames_;
  int current_frame_;
public:
  Game() : current_frame_(0) {
    for (int i = 0; i < FRAMES - 1; ++i)
      frames_.push_back(std::make_shared<Frame>());
    frames_.push_back(std::make_shared<TenthFrame>());
    assert(frames_.size() == FRAMES);
  }
  void add(int pins) {
    rolls_.push_back(Roll(rolls_.size(), pins));
    if (frames_[current_frame_]->is_completed())
      ++current_frame_;
    assert(current_frame_ < FRAMES);
    frames_[current_frame_]->add(rolls_.back());
  }
  int score() const {
    return score_for_frame(current_frame_ + 1);
  }
  int score_for_frame(int i) const {
    return std::accumulate(
      frames_.begin(), frames_.begin() + i, 0,
        [this](int a, const FramePtr& f) { return a + f->score(rolls_); });
  }
};

TEST("two throws no mark") {
  Game game;
  game.add(5);
  game.add(4);
  CHECK(9 == game.score());
}

TEST("four throws no mark") {
  Game game;
  game.add(5);
  game.add(4);
  game.add(7);
  game.add(2);
  CHECK(18 == game.score());
  CHECK( 9 == game.score_for_frame(1));
  CHECK(18 == game.score_for_frame(2));
}

TEST("simple spare") {
  Game game;
  game.add(3);
  game.add(7);
  game.add(3);
  CHECK(13 == game.score_for_frame(1));
}

TEST("simple frame after spare") {
  Game game;
  game.add(3);
  game.add(7);
  game.add(3);
  game.add(2);
  CHECK(13 == game.score_for_frame(1));
  CHECK(18 == game.score_for_frame(2));
  CHECK(18 == game.score());
}

TEST("simple strike") {
  Game game;
  game.add(10);
  game.add(3);
  game.add(6);
  CHECK(19 == game.score_for_frame(1));
  CHECK(28 == game.score());
}

TEST("perfect game") {
  Game game;
  for (int i = 0; i < 12; ++i)
    game.add(10);
  CHECK(300 == game.score());
}

TEST("end of array") {
  Game game;
  for (int i = 0; i < 9; ++i) {
    game.add(0);
    game.add(0);
  }
  game.add( 2);
  game.add( 8); // 10th frame spare
  game.add(10); // strike in last position of array
  CHECK(20 == game.score());
}

TEST("sample game") {
  Game game;
  game.add( 1);
  game.add( 4);
  game.add( 4);
  game.add( 5);
  game.add( 6);
  game.add( 4);
  game.add( 5);
  game.add( 5);
  game.add(10);
  game.add( 0);
  game.add( 1);
  game.add( 7);
  game.add( 3);
  game.add( 6);
  game.add( 4);
  game.add(10);
  game.add( 2);
  game.add( 8);
  game.add( 6);
  CHECK(133 == game.score());
}

TEST("heart break") {
  Game game;
  for (int i = 0; i < 11; ++i)
    game.add(10);
  game.add(9);
  CHECK(299 == game.score());
}

TEST("tenth frame spare") {
  Game game;
  for (int i = 0; i < 9; ++i)
    game.add(10);
  game.add(9);
  game.add(1);
  game.add(1);
  CHECK(270 == game.score());
}
