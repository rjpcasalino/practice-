{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    # Compilers & Toolchains
    gcc
    clang

    # Build Systems & Utilities
    gnumake
    cmake
    pkg-config
    bear            # Generates compile_commands.json for clangd/LSP support

    # Debugging & Profiling
    gdb
    valgrind
    strace

    # C & POSIX Documentation
    man-pages
    man-pages-posix
  ];

  shellHook = ''
    echo "========================================================"
    echo " 🌴 Tropical C & C++ Development Environment Loaded 🌴  "
    echo " 🎵 'Last night I dreamt of San Pedro...'               "
    echo "========================================================"
    echo " Compilers Available:                                   "
    echo "   - C:   gcc / clang   (C11, C17, C23)                 "
    echo "   - C++: g++ / clang++ (C++17, C++20, C++23)          "
    echo "                                                        "
    echo " Compilation Shortcuts:                                 "
    echo "   C:   gcc -std=c17 main.c -lm -o main                 "
    echo "   C++: g++ -std=c++20 main.cpp -o main                 "
    echo "                                                        "
    echo " Helpful Tooling:                                       "
    echo "   Use 'man 3 <func>' for C library docs.               "
    echo "   Run 'bear -- make' to build compile_commands.json.   "
    echo "--------------------------------------------------------"
  '';
}
