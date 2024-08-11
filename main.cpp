#include "enemy.hpp"
#include "interaction.hpp"
#include "keyboard.hpp"
#include "player.hpp"
#include "utils.hpp"

constexpr /*eval*/ bool firstTime() { return true; }
constinit const static bool isFirstTime = firstTime();

#define RPGHASASSERT

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  initscr();
  if (!stdscr) {
    assert("error initializing ncurses");
    return 1;
  }
  if (!has_colors()) {
    endwin();
    assert("your terminal doenst support colors");
    return 1;
  }
  start_color();

  Rpg::initColorPairs();

  // printf("\033[38;5;0m");

  Rpg::Item Banana = Rpg::Item(false, 255, 1, 1, "Banana");

  // Rpg::Player player{};
  // player.inventory.set(Banana);

  // Rpg::Key key{KEY_ENTER, []() { assert() }};

  // Rpg::startKeyboardInput(key);
  //  std::cout << player.inventory.get("Banana").name;
  Rpg::output("welcome to TypePG!", Rpg::Colors::FgWhiteBgBlack, 7);
  Rpg::output("type M or menu for more info", Rpg::Colors::FgWhiteBgBlack, 12);

  Rpg::EnemyBase enemy{3, "robert", "downey jr"};

  // Rpg::output(std::to_string(enemy.health) + " " +
  //             std::to_string(player.health));

  const std::string a = Rpg::input("lol");

  while (true) {
    refresh();
  }

  // Rpg::Actions::Battle(enemy, player);

  /*do {
    refresh();
    Rpg::output("... Waiting next input ...", Rpg::FgWhiteBgBlack);
  } while (Rpg::input(Rpg::FgWhiteBgBlack) != "/Quit");
*/
  endwin();

  return 0;
}
