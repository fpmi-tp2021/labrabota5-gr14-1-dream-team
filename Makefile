# Makefile for task5


task5: ISql.o TP_lab5.o mkout
	gcc -o task5 ISql.o TP_lab5.o -lsqlite3
	mv -f *.o obj
	mv -f task5 bin	
ISql.o: src/ISql.c
	gcc -c src/ISql.c 
TP_lab5.o: src/TP_lab5.c
	gcc -c src/TP_lab5.c 
clean:
	rm -rf bin obj
check:
	echo "Nothing to check"
distcheck:
	echo "nothing to distcheck"
mkout:
	mkdir -p bin obj
