# C++26

Simply a cosy home for C++26 experimentation

Requires [this fork of clang](https://github.com/bloomberg/clang-p2996)
with C++26 reflection support.

The following command was used to build it:
```
cmake -S llvm -B build -DCMAKE_INSTALL_PREFIX=$(pwd)/clang-custom
-DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS="clang;lld"
-DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind"
-DCMAKE_INSTALL_PREFIX=$(pwd)/clang-custom -G Ninja
```

Currently has a single target, `generate_enum_code` takes an enum as a parameter and 
generates the source file and header for a function to serialize it.

Needs deserialization, and more experiments!
