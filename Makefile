all:
	gcc -Wall -Werror -g -o stars stars.c `sdl2-config --cflags --libs`
run:
	gcc -Wall -Werror -g -o stars stars.c `sdl2-config --cflags --libs` && ./stars
clean:
	rm -rf ray
