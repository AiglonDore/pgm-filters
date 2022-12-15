LCC=g++
WCC=x86_64-w64-mingw32-g++-posix

ifneq ($(RELEASE), TRUE)
	CFLAGS=-Wall -Wextra -g -std=c++2a --shared -fPIC
else
	CFLAGS=-Wall -Wextra -O3 -std=c++2a -s --shared -fPIC
endif

all: linux windows

linux : obj/filter.o obj/image.o
	$(LCC) $(CFLAGS) -o bin/filter.so $^
	
windows : obj/filter.obj obj/image.obj
	$(WCC) $(CFLAGS) -o bin/filter.lib $^

obj/filter.o : src/filter.cpp header/filter.h
	$(LCC) $(CFLAGS) -c -o $@ $< 

obj/image.o : src/image.cpp header/filter.h header/image.h
	$(LCC) $(CFLAGS) -c -o $@ $< 

obj/filter.obj : src/filter.cpp header/filter.h
	$(WCC) $(CFLAGS) -c -o $@ $< 

obj/image.obj : src/image.cpp header/filter.h header/image.h
	$(WCC) $(CFLAGS) -c -o $@ $< 

doc :
	doxygen Doxyfile

clean :
	rm -vf obj/*.o obj/*.obj bin/*.so bin/*.lib
	@echo "Cleaned"