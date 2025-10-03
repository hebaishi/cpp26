#include "colour.hpp"
#include "generate_enum_serializer.hpp"

auto main() -> int {
  GenerateEnumSerializer<Colour>();
}
