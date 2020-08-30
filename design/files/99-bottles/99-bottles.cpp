#include <iostream>
#include <memory>
#include <sstream>

class Verse {
protected:
  std::ostream& stream_;
public:
  Verse(std::ostream& stream) : stream_{stream} {}
  virtual void sing() {
    sing_verse();
    stream_ << "\n";
    next_verse()->sing();
  }
  static std::unique_ptr<Verse> verse(int i, std::ostream& stream);
  void sing_verse() {
    bottles_of_beer_on_the_wall();
    bottles_of_beer();
    take_one_down();
    next_verse_bottles_of_beer_on_the_wall();
  }
  void bottles_of_beer_on_the_wall() {
   count_bottles();
   stream_ << " of beer on the wall\n";
  }
  void count_bottles() {
    stream_ << bottle_count_string(); // virtual call!
    stream_ << " ";
    stream_ << bottle_string(); // virtual call!
  }
  virtual int count() = 0;
  virtual std::string bottle_count_string() {
    return std::to_string(count()); // virtual call!
  }
  virtual std::string bottle_string() { return "bottles"; }
  virtual void bottles_of_beer() {
    count_bottles();
    stream_ << " of beer\n";
  }
  virtual void take_one_down() = 0;
  virtual void next_verse_bottles_of_beer_on_the_wall() {
    next_verse()->bottles_of_beer_on_the_wall();
  }
  std::unique_ptr<Verse> next_verse() {
    return verse(count() - 1, stream_);
  }
  static std::string sing(int n) {
    std::ostringstream oss;
    verse(n, oss)->sing();
    return oss.str();
  }
};

class NegativeVerse : public Verse {
public:
  NegativeVerse(std::ostream& stream) : Verse{stream} {}
  void sing() override {};
  int count() override { return -1; }
  void take_one_down() override {}
};

class PrecedingVerse : public Verse {
  int count_;
public:
  PrecedingVerse(int count, std::ostream& stream) : Verse{stream}, count_{count} {}
  int count() override { return count_; }
  void take_one_down() override {
    stream_ << "Take one down and pass it around\n";
  }
};

class PenultimateVerse : public Verse {
public:
  PenultimateVerse(std::ostream& stream) : Verse{stream} {}
  int count() override { return 1; }
  std::string bottle_string() override { return "bottle"; }
  void take_one_down() override {
    stream_ << "Take it down and pass it around\n";
  }
};

class UltimateVerse : public Verse {
public:
  UltimateVerse(std::ostream& stream) : Verse{stream} {}
  int count() override { return 0; }
  std::string bottle_count_string() override { return "No"; }
  void take_one_down() override {
    stream_ << "There are no more to pass around\n";
  }
  virtual void next_verse_bottles_of_beer_on_the_wall() {
    bottles_of_beer_on_the_wall();
  }
};

std::unique_ptr<Verse> Verse::verse(int i, std::ostream& stream)
{
  if (i <  0) return std::make_unique<NegativeVerse>(stream);
  if (i == 0) return std::make_unique<UltimateVerse>(stream);
  if (i == 1) return std::make_unique<PenultimateVerse>(stream);
  return std::make_unique<PrecedingVerse>(i, stream);
}

int main() {
  std::cout << Verse::sing(99);
}
