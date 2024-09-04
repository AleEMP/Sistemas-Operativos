all: driver_s.exe

driver_s.exe: ucsp.o driver.o libucsp.a
	gcc -o $@ ucsp.o driver.o -L. -lucsp

driver.o:driver.c ucsp.h
	gcc -c -fPIC $< -o $@

ucsp.o:ucsp.c ucsp.h
	gcc -c $< -o $@

libucsp.a:ucsp.o
	ar rcs $@ $<

clean:
	rm -f driver.o libucsp.a ucsp.o driver_s.exe
