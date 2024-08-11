#include "interaction.hpp"
#include "utils.hpp"

void Rpg::Actions::Battle(EnemyBase &enemy, Player &player) {
  output(enemy.firstName + " " + enemy.secondName + " started fighting " +
             player.firstName + "!",
         Colors::FgRedBgBlack, BIGGESTYSIZE);
  output /*Table*/ (enemy.firstName + " " + enemy.secondName + " LV." +
                        std::to_string(enemy.level),
                    Colors::FgRedBgBlack, 10);
  while (enemy.health >= 0 || player.health >= 0) {
    output("Next one to act is " + enemy.firstName, Colors::FgGreenBgBlack, 10);
    enemy.action(player);
    output("Next one to act is " + player.firstName, Colors::FgGreenBgBlack,
           10);
    player.action(enemy);
  };

  output(player.health > enemy.health ? player.firstName + " won! "
                                      : enemy.firstName + " won! ",
         Colors::FgRedBgBlack, BIGGESTYSIZE);
}
