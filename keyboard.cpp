#include "keyboard.hpp"

#include <coroutine>
#include <exception>
#include <ncurses.h>

struct KeyboardInputPromise;

struct KeyboardInput {
  struct promise_type {
    int current_value;
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    std::suspend_always yield_value(int value) {
      current_value = value;
      return {};
    }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
    KeyboardInput get_return_object() {
      return KeyboardInput{handle_type::from_promise(*this)};
    }
  };

  using handle_type = std::coroutine_handle<promise_type>;

  handle_type handle;
  KeyboardInput(handle_type handle) : handle{handle} {};
  ~KeyboardInput() {
    if (handle) {
      handle.destroy();
    }
  }

  int get() { return handle.promise().current_value; }
  int next() {
    handle.resume();
    return !handle.done();
  }
};

KeyboardInput keyboardInput() {
  while (true) {
    int ch = getch();
    co_yield ch;
  }
}

void Rpg::startKeyboardInput(Key &key) {
  initscr();            // start ncurses
  cbreak();             // no line buffering
  noecho();             // dont echo while do getch
  keypad(stdscr, TRUE); // enable special keys detection
  curs_set(0);          // hide cursor

  auto inputGen = keyboardInput();

  // int ch = 0;
  while (key.working) {
    if (inputGen.next()) {
      int ch = inputGen.get();
      if (ch) {
        key.function();
        refresh();
      }
    }
    /*switch (ch) {
      case KEY_UP: {
      }
    }*/
  }

  endwin();
} // TODO
