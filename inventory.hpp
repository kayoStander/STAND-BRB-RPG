#pragma once

#include <cstdint>
#include <string_view>
#include <unordered_map>

namespace Rpg {
struct Item {
public:
  [[gnu::leaf]] Item(bool tradeable, std::uint8_t maxQuantity,
                     std::uint8_t quantity, std::uint16_t value,
                     std::string_view name);
  ~Item() = default;

  bool tradeable = true;
  std::uint8_t maxQuantity = 255;
  std::uint8_t quantity = 1;
  std::uint16_t value;
  std::string_view name;
};

class Inventory {
public:
  Inventory(Inventory &&) = delete;
  Inventory(const Inventory &) = delete;
  Inventory &operator=(Inventory &&) = delete;
  Inventory &operator=(const Inventory &) = delete;

  Inventory() = default;
  ~Inventory() = default;

  [[gnu::pure]] [[nodiscard]] Item get(const std::string_view index);
  void add(const std::string_view index, std::uint8_t amount); // not added
  void set(Item item, const std::string_view name = "");

private:
  std::unordered_map<std::string_view, Item> items;
};
} // namespace Rpg
