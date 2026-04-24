{
  description = "Stars SDL2 animation";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs";

  outputs = { self, nixpkgs }:
    let
      system = "aarch64-darwin";
      pkgs = import nixpkgs { inherit system; };
    in
    {
      packages.${system}.default = pkgs.callPackage ./default.nix { };

      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          gcc
          SDL2
        ];
        shellHook = ''
          exec zsh
        '';
      };
    };
}

