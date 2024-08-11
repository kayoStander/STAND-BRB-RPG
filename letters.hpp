#pragma once

struct [[gnu::packed]] Letter {

  Letter(char letter);
  ~Letter() = default;

  char letter;
};

namespace Rpg {
struct [[gnu::packed]] Font {
  char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                       'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                       'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  Font(Font &&) = delete;
  Font(const Font &) = delete;
  Font &operator=(Font &&) = delete;
  Font &operator=(const Font &) = delete;

  Font();
  ~Font() = default;
};
} // namespace Rpg
