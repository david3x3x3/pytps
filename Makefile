CC=gcc

libpytps.so: pytps.c
	$(CC) -shared -fPIC -o libpytps.so -DUSE_TCL_STUBS `python3.4m-config --includes` -I$(HCIROOT)/tcl/include -L$(HCIROOT)/tcl/lib pytps.c -ltclstub8.6 -lpython3.4m

clean:
	rm *.o *.so
