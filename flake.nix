{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};

        stringspect = pkgs.stdenv.mkDerivation {
          pname = "stringspect";
          version = "1.0.0";

          src = ./.;

          nativeBuildInputs = [ pkgs.stdenv.cc ];

          buildPhase = ''
            gcc -O3 -o stringspect stringspect.c
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp stringspect $out/bin/
          '';
        };
      in
      {
        packages.default = stringspect;
      }
    );
}
