all: driver_d.exe

driver_d.exe: ucsp.o driver.o libucsp.so
	gcc -o $@ ucsp.o driver.o -L. -lucsp

driver.o:driver.c ucsp.h
	gcc -c -fPIC $< -o $@

ucsp.o:ucsp.c ucsp.h
	gcc -c $< -o $@

libucsp.so:ucsp.o
	gcc -shared $< -o $@
run: all
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH
	
clean:
	rm -f driver.o libucsp.so ucsp.o driver_d.exe
