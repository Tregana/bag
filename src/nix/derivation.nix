{ glibcLocales, stdenv, gcc10, lib, cmake, ninja, git}:
let
  doCheck = false;
in stdenv.mkDerivation {
  name = "vae";
  src = ../../.;
  nativeBuildInputs = [cmake];
  buildInputs = [ glibcLocales];
  doCheck = doCheck;
  cmakeFlags = []
    ++ lib.mapAttrsToList (k: v: "-D${k}=${if v then "ON" else "OFF"}") {
      BUILD_TESTING=true;
      BUILD_CONCEPT=false;
      BUILD_MODULE=false;
    };
  buildPhase = "cmake --build .";
  checkPhase = "ctest --verbose";
  installPhase = "cmake --build . --target install|grep -v '^-- '";
  #installCheckPhase = "ctest";
}
