#include "utils.hpp"
#include "keyboard.hpp"

#include <atomic>
#include <cstdio>
#include <ncurses.h>
#include <thread>

const char symbol = '-';

typedef std::string::size_type sizeType;

[[gnu::returns_nonnull]] [[gnu::malloc]] sizeType *Max() noexcept {
  initscr();
  int maxx, maxy;
  getmaxyx(stdscr, maxy, maxx);
  endwin();

  sizeType *max = new std::string::size_type[2];
  max[0] = static_cast<sizeType>(maxx);
  max[1] = static_cast<sizeType>(maxy);

  return max;
}

[[gnu::returns_nonnull]] [[gnu::malloc]] [[gnu::nonnull(3)]] sizeType *
Padding(const std::string content, const int sizeY,
        const sizeType *max) noexcept {
  sizeType *padding = new std::string::size_type[2];
  padding[0] = (max[0] - content.length()) / 2;
  padding[1] = (max[1] - content.length()) / static_cast<sizeType>(sizeY);

  return padding;
}

[[gnu::leaf]] void inline handleMaxPaddingErrors(sizeType *max,
                                                 sizeType *padding) {
  if (!max || !padding) {
    assert("no max or padding");
  }
}

void clearOutput() {
  std::atomic<bool> dontContinue = true;
  Rpg::Key key{KEY_ENTER, [&]() {
                 clear();
                 dontContinue = false;
               }};
  Rpg::startKeyboardInput(key);
  while (dontContinue) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  Rpg::toggleKeyboardInput(key);
}

void Rpg::initColorPairs() noexcept {
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
}

void Rpg::output(const std::string content, const int Color,
                 const int sizeY) noexcept {

  clearOutput();

  sizeType *max = Max();
  sizeType *padding = Padding(content, sizeY, max);

  handleMaxPaddingErrors(max, padding);

  std::string line = std::string(max[0], symbol);
  std::string newLine = std::string(padding[1] / 2, '\n');
  std::string whitespace = std::string(padding[0], ' ');

  clear();
  attron(COLOR_PAIR(Color));
  printw("%s\n", line.c_str());

  printw("%s", newLine.c_str());
  printw("%s %s\n", whitespace.c_str(), content.c_str());
  printw("%s", newLine.c_str());

  printw("%s\n", line.c_str());
  attroff(COLOR_PAIR(Color));
  refresh();

  delete[] max;
  delete[] padding;
}

/*[[gnu::nonnull(1)]] void outputTable(const std::string *table,
                                     const int tableSize, const int Color,
                                     const int sizeY) {

  sizeType *max = Max();
  sizeType *padding = Padding(table[0], sizeY, max);

  std::cout << "\x1B[" << Color << std::string(max[0], symbol) << "\033[0m"
            << std::endl;
  std::cout << std::string(padding[1] / 2, '\n');

  for (int i = 0; i >= tableSize; i++) {
    std::cout << std::string(padding[0], ' ') << table[i] << " I ";
  }
  std::cout << std::endl;

  std::cout << std::string(padding[1] / 2, '\n');
  std::cout << "\x1B[" << Color << std::string(max[0], symbol) << "\033[0m"
            << std::endl;

  delete[] max;
}*/

[[nodiscard]] std::string Rpg::input(const std::string text, const int Color,
                                     const int sizeY) noexcept {
  // clearOutput();

  std::string content;

  sizeType *max = Max();
  sizeType *padding = Padding(text, sizeY, max);

  handleMaxPaddingErrors(max, padding);

  std::string line = std::string(max[0], symbol);
  std::string newLine = std::string(padding[1] / 2, '\n');
  std::string whitespace = std::string(padding[0], ' ');

  attron(COLOR_PAIR(Color));
  printw("%s\n", line.c_str());

  printw("%s", newLine.c_str());
  printw("%s %s = ", whitespace.c_str(), text.c_str());

  int promptLength = static_cast<int>(whitespace.length() + text.length()) + 3;
  move(static_cast<int>(padding[1]) + 1, promptLength);

  char buffer[256];
  echo();
  mvgetnstr(static_cast<int>(padding[1]), promptLength, buffer,
            sizeof(buffer) - 1);
  noecho();
  printw("%s", newLine.c_str());

  printw("%s\n", line.c_str());
  attroff(COLOR_PAIR(Color));
  refresh();

  content = std::string(buffer);

  delete[] max;
  delete[] padding;

  clear();
  refresh();

  return content;
}

[[nodiscard]] std::string Rpg::input(const int Color,
                                     const int sizeY) noexcept {
  std::string content;

  sizeType *max = Max();
  sizeType *padding = Padding("", sizeY, max);

  handleMaxPaddingErrors(max, padding);

  std::string line = std::string(max[0], symbol);
  std::string newLine = std::string(padding[1] / 2, '\n');
  std::string whitespace = std::string(padding[0], ' ');

  attron(COLOR_PAIR(Color));
  printw("%s\n", line.c_str());

  printw("%s", newLine.c_str());
  printw("%s = ", whitespace.c_str());

  [[maybe_unused]] char buffer[256];
  echo();
  // mvgetnstr(static_cast<int>(padding[1]) / 2 + 1, promptLength, buffer,
  //         sizeof(buffer) - 1);
  noecho();
  printw("%s", newLine.c_str());

  printw("%s\n", line.c_str());

  delete[] max;
  delete[] padding;

  return content;
}

void Rpg::input(std::string &content, const int Color,
                const int sizeY) noexcept {
  sizeType *max = Max();
  sizeType *padding = Padding(content, sizeY, max);

  std::cout << "\x1B[" << Color << std::string(max[0], symbol) << "\033[0m"
            << std::endl;
  std::cout << std::string(padding[1] / 2, '\n');

  std::cout << std::string(padding[0], ' ');
  std::getline(std::cin, content);

  std::cout << std::string(padding[1] / 2, '\n');
  std::cout << "\x1B[" << Color << std::string(max[0], symbol) << "\033[0m"
            << std::endl;

  delete[] max;
}

void Rpg::input(std::string &content, const std::string text, const int Color,
                const int sizeY) noexcept {
  sizeType *max = Max();
  sizeType *padding = Padding(text, sizeY, max);

  std::cout << "\x1B[" << Color << std::string(max[0], symbol) << "\033[0m"
            << std::endl;
  std::cout << std::string(padding[1] / 2, '\n');

  std::cout << "\x1B[" << Color << std::string(padding[0], ' ') << text << " = "
            << "\033[0m";
  std::getline(std::cin, content);

  std::cout << std::string(padding[1] / 2, '\n');
  std::cout << "\x1B[" << Color << std::string(max[0], symbol) << "\033[0m"
            << std::endl;

  delete[] max;

  if (content == "") {
    input(content, text, Color, sizeY);
  }
}

[[gnu::unused]] void outputASCII([[maybe_unused]] std::string content) {};

[[nodiscard]] bool Rpg::inputBool(const std::string text, const int Color,
                                  const int sizeY) noexcept {
  sizeType *max = Max();
  sizeType *padding = Padding(text, sizeY, max);

  std::string content;

  std::cout << "\x1B[" << Color << std::string(max[0], symbol) << "\033[0m"
            << std::endl;
  std::cout << std::string(padding[1] / 2, '\n');

  std::cout << "\x1B[" << Color << std::string(padding[0], ' ') << text
            << " (Y/N) = " << "\033[0m";
  std::getline(std::cin, content);

  std::cout << std::string(padding[1] / 2, '\n');
  std::cout << "\x1B[" << Color << std::string(max[0], symbol) << "\033[0m"
            << std::endl;

  // content = tolower(static_cast<char>(content[0]));
  return content == "y" || content == "" ? true : false;

  delete[] max;

  if (content == "") {
    input(content, text, Color, sizeY);
  }
}

// TODO simplify functions
