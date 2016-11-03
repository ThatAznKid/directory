dir.out: main.c
	gcc main.c -o dir.out

run: dir.out
	./dir.out 

clean:
	rm dir.out