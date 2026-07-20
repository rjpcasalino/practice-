{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    gcc
    clang     # Added as an alternative compiler
    gnumake
    gdb
    valgrind
  ];

  shellHook = ''
    echo "C development environment loaded."
    echo "Compilers available: gcc, clang"
    echo "Run 'gcc main.c -o main && ./main' to test the binary search."
  '';
}
