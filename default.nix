{ stdenv, lib, SDL2 }:

stdenv.mkDerivation {
  pname = "stars";
  version = "0.1.0";

  src = ./.;

  buildInputs = [ SDL2 ];

  buildPhase = ''
    $CC -Wall -g -o stars stars.c \
      -I${SDL2}/include/SDL2 \
      -L${SDL2}/lib \
      -lSDL2
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp stars $out/bin/
  '';

  meta = {
    description = "A twinkling stars animation using SDL2";
    platforms = lib.platforms.darwin;
  };
}
