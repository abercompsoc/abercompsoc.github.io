 with import <nixpkgs> {}; {
   jekyllEnv = stdenv.mkDerivation {
     name = "jekyll";
     buildInputs = [ stdenv jekyll ];
   };
 }
