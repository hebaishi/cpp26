# C++26

Simply a cosy home for C++26 experimentation

Requires [this fork of clang](https://github.com/bloomberg/clang-p2996)
with C++26 reflection support.

Currently has a single target, `generate_enum_code` takes an enum as a parameter and 
generates the source file and header for a function to serialize it.

Needs deserialization, and more experiments!
