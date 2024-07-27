{ pkgs }: {
	deps = [
   pkgs.sqlitecpp
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
        pkgs.sqlite
	];
}