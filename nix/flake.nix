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

          # Safely access the Nix HTML manual without overriding system Nix executables
          nixManualScript = pkgs.writeShellScriptBin "nix-manual" ''
            DOC_PATH="${pkgs.nix.doc}/share/doc/nix/manual/index.html"
            echo "Opening local Nix Manual in your browser..."
            
            if command -v open >/dev/null 2>&1; then
              open "$DOC_PATH"
            elif command -v xdg-open >/dev/null 2>&1; then
              xdg-open "$DOC_PATH"
            else
              echo "Could not detect a web browser opener. You can view the manual here:"
              echo "file://$DOC_PATH"
            fi
          '';

          ghosttyManualScript = pkgs.writeShellScriptBin "man-ghost" ''
            echo "Opening Ghostty man page..."
            man ghostty
          '';

          # A lightweight launcher that loads the curriculum into the REPL
          playTutor = pkgs.writeShellScriptBin "nix-tutor" ''
            clear
            # Calculate the local path to the Nix manual
            DOC_BASE="file://${pkgs.nix.doc}/share/doc/nix/manual"

            # Launch REPL and dynamically pass the DOC_BASE argument into the file
            nix repl --expr "import ./tutor.nix { docBase = \"$DOC_BASE\"; }"
          '';
          

        in
        {
          default = pkgs.mkShell {
            # Adding 'man' ensures the environment's MANPATH is generated correctly
            buildInputs = with pkgs; [
              nil
              nixpkgs-fmt
              statix
              customVim
              man
              practiceExamples
              nixManualScript
              ghosttyManualScript
              playTutor
            ] ++ (if pkgs.stdenv.isLinux then [ pkgs.ghostty ]
            else if pkgs.stdenv.isDarwin then [ pkgs.ghostty-bin ]
            else [ ]);

            shellHook = ''
              # --- GHOSTTY AUTO-INSTALLER & HIJACK ---
              if [[ "$TERM" != *"ghostty"* ]]; then
                if ! command -v ghostty >/dev/null 2>&1; then
                  echo "⚠️ Ghostty not detected. Attempting automated installation..."
                  if [[ "$OSTYPE" == "darwin"* ]]; then
                    if command -v brew >/dev/null 2>&1; then
                      echo "📦 Installing Ghostty via Homebrew cask..."
                      brew install --cask ghostty
                    else
                      echo "❌ Homebrew not found. Please install Ghostty manually from https://ghostty.org"
                    fi
                  else
                    echo "ℹ️ Nix is provisioning Ghostty for your Linux environment..."
                  fi
                fi

                if command -v ghostty >/dev/null 2>&1; then
                  echo "🚀 Relaunching Nix development environment inside Ghostty..."
                  exec ghostty -e nix develop
                fi
              fi

              echo "================================================================"
              echo " ❄️  Nix Expression Practice Environment Ready ❄️"
              echo "================================================================"
              echo ""
              echo " Quick commands available:"
              echo "    nix-examples    - View builtins cheat sheet"
              echo "    nix-manual      - Open local offline Nix HTML manual"
              echo "    man-ghost       - Open local Ghostty man page"
              echo "    nix-tutor       - Open tutor.nix"
              echo "    nix repl        - Open interactive evaluation REPL"
              echo "================================================================"
              echo ""
            '';
          };
        });
    };
}
