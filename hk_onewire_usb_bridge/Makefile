MAKEFLAGS += --no-print-directory

default: build/Makefile
	make -C build

build:
	mkdir -p build

build/Makefile: build
	cd build && cmake ..

upload:
	# TODO