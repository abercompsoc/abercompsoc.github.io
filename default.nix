 with import <nixpkgs> {}; {
   jekyllEnv = stdenv.mkDerivation {
     name = "jekyll";
     # see https://github.com/NixOS/nixpkgs/issues/11564 for the nodejs dep
     buildInputs = [ stdenv jekyll nodejs ];
   };
 }
