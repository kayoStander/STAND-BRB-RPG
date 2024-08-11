#include "inventory.hpp"

[[gnu::leaf]] Rpg::Item::Item(bool tradeable, std::uint8_t maxQuantity,
                              std::uint8_t quantity, std::uint16_t value,
                              std::string_view name)
    : tradeable(tradeable), maxQuantity(maxQuantity), quantity(quantity),
      value(value), name(name) {}

////////////////////////////////////////////////////////////////////////////////

[[gnu::pure]] [[nodiscard]] Rpg::Item
Rpg::Inventory::get(const std::string_view index) {
  return Rpg::Inventory::items.at(index);
};
void Rpg::Inventory::set(Item item, const std::string_view name) {
  Inventory::items.insert({name == "" ? item.name : name, item});
};
