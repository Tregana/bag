let
  nixpkgs = import src/nix/pinnedNixpkgs.nix;
  pkgs = import nixpkgs {
    config = {};
    overlays = [
      (import src/nix/overlay.nix)
    ];
  };
in pkgs.bag
