#include "player.hpp"
#include "utils.hpp"

Rpg::Player::Player() {
  do {
    input(firstName, "first name", Colors::FgGreenBgBlack, SMALLESTYSIZE);
    input(secondName, "second name", Colors::FgGreenBgBlack, SMALLESTYSIZE);
  } while (!Rpg::inputBool("Are you sure?"));
  output("Your name is " + firstName + " " + secondName + "!",
         Colors::FgGreenBgBlack, BIGGESTYSIZE);
}

void Rpg::Player::action(EnemyBase &enemy) {
  [[maybe_unused]] std::string content =
      Rpg::input("What will be your action? (WIP) ", Colors::FgWhiteBgBlack);
  int8_t damage =
      Rpg::RNG<int8_t>(static_cast<int8_t>(10), static_cast<int8_t>(25));
  hit(damage, enemy); // temp
}

// void Rpg::Player::interact() {}
