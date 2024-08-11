#pragma once

#include "enemy.hpp"
#include "inventory.hpp"

namespace Rpg {

class Player {
public:
  Player(Player &&) = delete;
  Player(const Player &) = delete;
  Player &operator=(Player &&) = delete;
  Player &operator=(const Player &) = delete;

  Player();
  ~Player() = default;

  int health = 255;
  std::string firstName;
  std::string secondName;

  inline void hit(int8_t damage) noexcept {
    output(firstName + " got hit! [" + std::to_string(damage) + "]",
           Colors::FgRedBgBlack, 10);
    health -= damage;
  }
  inline void hit(int8_t damage, EnemyBase &enemy) const noexcept {
    output(enemy.firstName + " got hit! [" + std::to_string(damage) + "]",
           Colors::FgRedBgBlack, 10);
    enemy.health -= damage;
  }
  void action(EnemyBase &enemy);

  Inventory inventory;
};

} // namespace Rpg
