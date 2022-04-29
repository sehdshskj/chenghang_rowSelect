main:*.c *.h
	gcc  *.c *.h -o main
clean:
	-rm -rf *.o main;

