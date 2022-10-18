CC = clang

create:
	$(CC) src/main.c -o pnp

clean:
	rm pnp