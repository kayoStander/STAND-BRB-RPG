#pragma once

#include <atomic>
#include <functional>

namespace Rpg {

struct Key {
public:
  Key(int key, std::function<void()> function)
      : key{key}, function{function} {};

  int key; // ch
  std::atomic<bool> working = true;
  std::function<void()> function;

  /*Key(Key &&) = default;
  Key(const Key &) = default;
  Key &operator=(Key &&) = default;
  Key &operator=(const Key &) = default;
  ~Key() = default;
*/

private:
};

void startKeyboardInput(Key &key);
[[gnu::leaf]] inline void toggleKeyboardInput(Key &key) {
  key.working = !key.working;
};
} // namespace Rpg
