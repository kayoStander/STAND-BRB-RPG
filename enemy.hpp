#pragma once

#include "utils.hpp"

#include <cstdint>
#include <string>

namespace Rpg {
class Player;
} // namespace Rpg

namespace Rpg {

class EnemyBase {
public:
  EnemyBase(EnemyBase &&) = default;
  EnemyBase(const EnemyBase &) = default;
  EnemyBase &operator=(EnemyBase &&) = default;
  EnemyBase &operator=(const EnemyBase &) = default;
  ~EnemyBase() = default;

  EnemyBase(int8_t level, std::string firstName, std::string secondName)
      : level{level}, health{RNG(static_cast<int>(10 * level * 2),
                                 static_cast<int>(10 * level * 2 * 4))},
        firstName{firstName}, secondName{secondName} {};

  int level = 1;

  int health = 255;
  std::string firstName = "NO";
  std::string secondName = "NAME";

  void action(Player &player);

private:
};
} // namespace Rpg
