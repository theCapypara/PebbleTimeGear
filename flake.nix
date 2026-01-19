{
  description = "Pebble TimeGear watch face";

  inputs = {
    pebble.url = "github:pebble-dev/pebble.nix/nixpkgs-bump";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { pebble, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system: {
      devShell = pebble.pebbleEnv.${system} { withCoreDevices = true; };
    });
}
