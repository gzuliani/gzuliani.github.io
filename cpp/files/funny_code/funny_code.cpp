#include <iostream>

const auto wrap = [](auto x) { return [x](auto) { return x; }; };
const auto delay = [](auto x) { return x; };

const auto first = wrap;
const auto rest = wrap(delay);

const auto pair = [](auto x) {
  return [x](auto y) {
    return [x, y](auto sel) {
      return sel(x)(y);
    };
  };
};

const auto empty_list = [](auto when_empty, auto) { return when_empty(); };
const auto node = [](auto x) {
  return [x](auto y) {
    return [x, y](auto, auto unless_empty) {
      return unless_empty(pair(x)(y));
    };
  };
};

const auto one_item_list = node(1)(empty_list);
const auto many_items_list = node(1)(node(2)(node(3)(empty_list)));

template <class T>
int length(T list, int acc) {
  return list(
    [acc]() { return acc; },
    [acc](auto pair) { return length(pair(rest), 1 + acc); });
}

template <class T>
int length(T list) {
  return length(list, 0);
}

int main() {
  std::cout
    << length(empty_list) << " "
    << length(one_item_list) << " "
    << length(many_items_list) << "\n";
}
