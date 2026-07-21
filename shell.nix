{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    # Java Toolchain
    jdk21            # Modern OpenJDK 21 LTS
    maven            # Java build tool
    gradle           # Alternative Java build tool

    # C & C++ Compilers & Toolchains
    gcc
    clang

    # Build Systems & Utilities
    gnumake
    cmake
    pkg-config
    bear            # Generates compile_commands.json for clangd/LSP

    # Debugging & Profiling
    gdb
    valgrind
    strace

    # Documentation
    man-pages
    man-pages-posix
  ];

  shellHook = ''
    echo "========================================================"
    echo " 🌴 Tropical Polyglot Dev Environment Loaded 🌴          "
    echo " 🎵 'Last night I dreamt of San Pedro...'               "
    echo "========================================================"
    echo " Environment Specs:                                     "
    echo "   - Java: $(java -version 2>&1 | head -n 1)            "
    echo "   - C/C++: gcc / clang                                 "
    echo "                                                        "
    echo " Quick Commands:                                        "
    echo "   Java: javac Quicksort.java && java Quicksort          "
    echo "   C:    gcc -std=c17 main.c -lm -o main                "
    echo "   C++:  g++ -std=c++20 main.cpp -o main                "
    echo "--------------------------------------------------------"
  '';
}
