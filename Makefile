
build:
	gcc -std=c99 -Wall -Werror -g -o ./bin/vm-test ./src/vm-inst-handle.c ./src/vm.c ./src/vm-test.c

test:
	./bin/vm-test
