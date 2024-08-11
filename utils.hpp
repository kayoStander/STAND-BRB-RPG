#pragma once

#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <random>

#ifdef RPGHASASSERT
#ifdef _WIN32
#define RPGASSERT() __debugbreak() // MSVC
#elif defined(__APPLE__)
#define RPGASSERT() __builtin_trap()
#elif defined(__linux__)
#define RPGASSERT() std::abort()
#else
#define RPGASSERT()                                                            \
  [[gnu::always_inline]] __volate__ __asm__("int $3" ::                        \
                                                : "memory") std::cout          \
      << FILE__ << __LINE__
#endif
#else
#define RPGASSERT() std::cout << "no assertion, but reached one";
#endif

template <typename T>
concept Number = std::is_arithmetic_v<T>;
template <typename T>
concept Integral = std::is_integral_v<T>;

namespace Rpg {

const int BIGGESTYSIZE = 2;
const int SMALLESTYSIZE = 20;

enum Size { Biggest = 2, Medium = 12, Smallest = 20 }; // NOT USED YET

enum class Colors : uint32_t {
  FgWhiteBgBlack = 1,
  FgBlackBgBlack = 2,
  FgRedBgBlack = 3,
  FgGreenBgBlack = 4,
  FgBlueBgBlack = 5
};

void initColorPairs() noexcept;

void output(const std::string content,
            const Colors Color = Colors::FgWhiteBgBlack,
            const int sizeY = SMALLESTYSIZE
            /*const int textSize = 1, Rpg::Font textFont*/) noexcept;

[[nodiscard]] std::string input(const std::string text,
                                const Colors Color = Colors::FgWhiteBgBlack,
                                const int sizeY = 12) noexcept;

[[nodiscard]] std::string input(const Colors Color = Colors::FgWhiteBgBlack,
                                const int sizeY = 12) noexcept;

void input(std::string &content, const Colors Color = Colors::FgWhiteBgBlack,
           const int sizeY = 12) noexcept;

void input(std::string &content, const std::string text,
           const Colors Color = Colors::FgWhiteBgBlack,
           const int sizeY = 12) noexcept;

void outputASCII(std::string content, const int sizeY = 12);

[[nodiscard]] bool inputBool(const std::string text,
                             const Colors Color = Colors::FgWhiteBgBlack,
                             const int sizeY = 12) noexcept;

template <Number T> T RNG(T min, T max) noexcept {
  static std::random_device random;
  static std::mt19937 gen(random());

  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> dis(min, max);
    return static_cast<T>(dis(gen));
  } else if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dis(min, max);
    return static_cast<T>(dis(gen));
  }
  return T();
}

} // namespace Rpg
