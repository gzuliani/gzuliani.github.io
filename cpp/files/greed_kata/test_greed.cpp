#include "gut.h"
#include <algorithm>
#include <cassert>

using Die = int;
using Roll = std::vector<Die>;

Roll drop(const Roll& roll, int count) {
  return Roll(roll.begin() + count, roll.end());
}

class Match {
public:
  virtual ~Match() = default;
  virtual bool matches(const Roll& roll) const = 0;
  virtual int length() const = 0;
};

class Sequence : public Match {
  const Roll roll_;
public:
  Sequence(const Roll& roll) : roll_(roll) {}
  bool matches(const Roll& roll) const override {
    return std::equal(roll_.begin(), roll_.end(), roll.begin());
  }
  int length() const override { return roll_.size(); }
};

class Fallback : public Match {
public:
  bool matches(const Roll& /*roll*/) const override { return true; }
  int length() const override { return 1; }
};

class Rule {
  const std::shared_ptr<const Match> match_;
  const int score_;
public:
  Rule(const Match* match, int score) : match_(match), score_(score) {}
  bool matches(const Roll& roll) const { return match_->matches(roll); }
  int score() const { return score_; }
  int length() const { return match_->length(); }
};

static Rule greed_rules[] = {
  Rule(new Sequence({1, 1, 1}), 1000),
  Rule(new Sequence({2, 2, 2}),  200),
  Rule(new Sequence({3, 3, 3}),  300),
  Rule(new Sequence({4, 4, 4}),  400),
  Rule(new Sequence({5, 5, 5}),  500),
  Rule(new Sequence({6, 6, 6}),  600),
  Rule(new Sequence({1,     }),  100),
  Rule(new Sequence({5,     }),   50),
  Rule(new Fallback(),             0),
};

int sorted_roll_score(const Roll& roll) {
  if (roll.empty()) // avoid infinite recursion
    return 0;
  auto target_rule = std::find_if(
    std::begin(greed_rules), std::end(greed_rules),
    [&roll](const Rule& rule) { return rule.matches(roll); });
  assert(target_rule != std::end(greed_rules));
  return target_rule->score()
    + sorted_roll_score(drop(roll, target_rule->length()));
}

int score(const Roll& roll) {
  Roll sorted_roll = roll;
  std::sort(sorted_roll.begin (), sorted_roll.end());
  return sorted_roll_score(sorted_roll);
}

TEST("a set of three 1's is worth 1000 points") {
  CHECK(score({1, 1, 1}) == 1000);
}

TEST("a set of 3 of any other number is worth 100 * that number") {
  CHECK(score({2, 2, 2}) == 200);
  CHECK(score({3, 3, 3}) == 300);
  CHECK(score({4, 4, 4}) == 400);
  CHECK(score({5, 5, 5}) == 500);
  CHECK(score({6, 6, 6}) == 600);
}

TEST("a single 1 is worth 100 points") {
  CHECK(score({1}) == 100);
}

TEST("a single 5 is worth 50 points") {
  CHECK(score({5}) == 50);
}

TEST("any other die or combination is worth 0 points") {
  CHECK(score({2         }) == 0);
  CHECK(score({3         }) == 0);
  CHECK(score({4         }) == 0);
  CHECK(score({6         }) == 0);
  CHECK(score({2, 2      }) == 0);
  CHECK(score({2, 3      }) == 0);
  CHECK(score({2, 2, 3   }) == 0);
  CHECK(score({2, 3, 4, 6}) == 0);
}

TEST("after applying a rule, dice involved in it are removed from the roll") {
  CHECK(score({5, 5, 5, 5, 3}) == 550);
  CHECK(score({2, 3, 4, 6, 2}) ==   0);
  CHECK(score({1, 5, 1, 2, 4}) == 250);
  CHECK(score({5, 5, 5, 5, 5}) == 600);
}

TEST("rules are applied until all dice are evaluated") {
  CHECK(score({1, 2, 3, 4, 5}) == 150);
  CHECK(score({2, 3, 3, 3, 4}) == 300);
  CHECK(score({2, 2, 2, 3, 5}) == 250);
}

TEST("dice order does not matter") {
  CHECK(score({1, 1, 5, 1, 1}) == 1150);
  CHECK(score({3, 4, 5, 3, 3}) ==  350);
  CHECK(score({5, 5, 3, 5, 5}) ==  550);
  CHECK(score({3, 4, 3, 5, 3}) ==  350);
}


