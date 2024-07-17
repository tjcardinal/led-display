{
  description = "An LED display driven by an ESP8266";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      formatter.${system} = pkgs.nixpkgs-fmt;
      devShells.${system}.default =
        pkgs.mkShell {
          buildInputs = with pkgs; [
            platformio
          ];
        };
    };
}
