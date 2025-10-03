#include <experimental/meta>
#include <format>
#include <fstream>
#include <filesystem>
#include <print>
using namespace std;

struct EnumInfo {
  std::string enum_name;
  std::string variable_name;
};

consteval auto ToLower(const std::string &input) {
  std::string result;
  for (auto c : input) {
    if (c >= 'A' && c <= 'Z') {
      result += (c - 'A' + 'a');
    } else {
      result += c;
    }
  }
  return define_static_string(result);
}

template <typename T>
consteval auto GetEnumInfo() {
  constexpr auto info = ^^T;
  constexpr auto enum_name = define_static_string(display_string_of(info));
  constexpr auto variable_name = ToLower(enum_name);
  return EnumInfo{
    enum_name, variable_name
  };
}


template <typename T>
consteval auto get_includes() {
  constexpr auto enum_info = GetEnumInfo<T>();
  std::string result = "#include <string>\n" + std::string("#include \"../") + enum_info.variable_name + ".hpp\"\n";
  return result;
}

template <typename T>
consteval auto declare_function() {
  constexpr auto enum_info = GetEnumInfo<T>();
  return std::string("std::string ToString(" )+ enum_info.enum_name + " " + enum_info.variable_name + ")";
}

template<typename T>
consteval auto make_function_header() {
  std::string result = get_includes<T>() + declare_function<T>() + ";";
  return define_static_string(result);
}

template <typename T>
consteval auto make_function_source() {
  constexpr auto enum_info = GetEnumInfo<T>();
  std::string result = "#include \"to_string.hpp\"\n";
  result += declare_function<T>();
  result += std::string(" {\n  switch (") + enum_info.variable_name + "){\n";
  template for (auto constexpr m : define_static_array(enumerators_of(^^T))) { //***
    auto member_name = display_string_of(m);
    result += std::string("    case ") + enum_info.enum_name + "::" + member_name +
              ": return \"" + member_name + "\";\n";
  }
  result += std::string("  }\n}");
  return define_static_string(result);
}

template <typename T>
void GenerateEnumSerializer() {
  constexpr auto enum_info = GetEnumInfo<T>();
  constexpr auto directory = enum_info.variable_name;
  if (!filesystem::is_directory(directory)) {
    filesystem::create_directory(directory);
  }
  std::ofstream header_file(std::string(directory) + "/to_string.hpp");
  header_file << make_function_header<Colour>() << std::endl;
  std::ofstream source_file(std::string(directory) + "/to_string.cpp");
  source_file << make_function_source<Colour>() << std::endl;
}
