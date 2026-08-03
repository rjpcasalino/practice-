{
  description = "Nix Expression Development & Practice Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;
    in
    {
      devShells = forAllSystems (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};

          customVim = (pkgs.vim-full.override { guiSupport = false; }).customize {
            name = "vim";
            vimrcConfig.customRC = ''
              syntax on
              filetype plugin indent on
              set number
              set expandtab
              set shiftwidth=2
              set tabstop=2
              set clipboard=

              set completeopt=menu,menuone,noselect,noinsert
              set shortmess+=c
              let g:mucomplete#enable_auto_at_startup = 1

              let g:ale_completion_enabled = 1
              let g:ale_linters = {'nix': ['nil', 'statix']}
              let g:ale_fixers = {'nix': ['nixpkgs-fmt']}
              let g:ale_fix_on_save = 1

              set laststatus=2
              set noshowmode
            '';
            vimrcConfig.packages.myVimPackage = with pkgs.vimPlugins; {
              start = [ vim-nix ale vim-mucomplete lightline-vim ];
            };
          };

          # Create a custom executable command to display the practice examples
          practiceExamples = pkgs.writeShellScriptBin "nix-examples" ''
            cat << 'EOF'
            =========================================
                 NIX BUILTINS PRACTICE EXAMPLES
            =========================================
            Run 'nix repl' and try typing these in:

            --- LISTS ---
            1. map: Apply logic to every item
               builtins.map (x: x * 2) [ 1 2 3 ]

            2. filter: Keep items that match a rule
               builtins.filter (x: x > 2) [ 1 2 3 4 ]

            3. foldl': Keep a running total
               builtins.foldl' (total: x: total + x) 0 [ 1 2 3 ]

            --- ATTRIBUTE SETS ---
            1. attrNames: Get all the keys
               builtins.attrNames { name = "alice"; age = 30; }

            2. hasAttr: Check if a key exists safely
               builtins.hasAttr "role" { name = "bob"; }

            3. mapAttrs: Modify values in a set
               builtins.mapAttrs (k: v: "Port ''${toString v}") { http = 80; }
            =========================================
            EOF
          '';
        in
        {
          default = pkgs.mkShell {
            buildInputs = with pkgs; [
              nil
              nixpkgs-fmt
              statix
              customVim
              practiceExamples # Injects the 'nix-examples' command
            ];

            shellHook = ''
              echo "================================================================"
              echo " ❄️  Nix Expression Practice Environment Ready ❄️"
              echo "================================================================"
              echo ""
              echo " To view the builtins practice examples, run:"
              echo "    nix-examples"
              echo ""
              echo " To practice evaluating expressions interactively, run:"
              echo "    nix repl -f '<nixpkgs>'"
              echo "================================================================"
              echo ""
            '';
          };
        });
    };
}
