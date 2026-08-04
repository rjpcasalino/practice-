# Nix Expression Practice Environment

A lightweight, reproducible development shell designed specifically for writing, testing, and learning Nix expressions. This environment comes pre-configured with a modern terminal editor setup and all the necessary language tools—so you can focus on writing Nix without configuring your environment.

## What's Inside

When you launch this shell, you get a zero-setup, IDE-like Vim environment powered by ALE:

* **nil:** The Nix Language Server (provides autocomplete, documentation, and go-to-definition).
* **statix:** A static analysis linter that catches Nix anti-patterns and bad habits as you type.
* **nixpkgs-fmt:** The standard formatter to keep your code clean (auto-runs on save in Vim).
* **Vim:** Configured with `vim-nix`, `vim-mucomplete` for as-you-type autocomplete, and a clean status bar.
