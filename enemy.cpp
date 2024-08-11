#include "enemy.hpp"
#include "player.hpp"
#include "utils.hpp"

void Rpg::EnemyBase::action(Rpg::Player &player) {
  int ACT = Rpg::RNG(0, 1);
  switch (ACT) {
  case 0: {
    int8_t Damage = Rpg::RNG<int8_t>(static_cast<int8_t>(10 * level),
                                     static_cast<int8_t>(20 * level));
    player.hit(Damage);
    break;
  }
  case 1: {
    output(firstName + " missed!", Colors::FgGreenBgBlack, 10);
    break;
  }
  }
}
