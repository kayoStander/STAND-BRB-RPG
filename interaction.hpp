#pragma once

#include "enemy.hpp"
#include "player.hpp"

namespace Rpg {

namespace Actions {
void Battle(EnemyBase &enemy, Player &player);
/*
  {"Shopping",
   [](Inventory inventory, Player &player) {

   }},
  {"Afk", [](Player &player) {

   }}};*/

} // namespace Actions
} // namespace Rpg
