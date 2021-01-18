CC = clang
C_OPTS = -fsanitize=address -g -Wall -Wextra -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -I./src src/lib.c

all: clean prep compile

clean:
	rm -rf dist

prep:
	mkdir dist

compile: create_bins

touch:
	doxygen Doxyfile

create_bins: main.bin

main.bin: src/main.c
	$(CC) $(C_OPTS) $< -o ./dist/$@