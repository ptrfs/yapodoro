all:
	clang src/*
	mv a.out bin/pom

install:
	clang src/*
	mv a.out bin/pom
	sudo mv bin/pom /usr/local/bin
