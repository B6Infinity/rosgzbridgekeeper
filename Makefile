WXCONFIG_FLAGS = `wx-config --cppflags --libs`

INCLUDE_DIR = include/

SRC = $(wildcard src/*.cpp src/*/*.cpp)

OUTFILE = app.o


app: src/App.cpp
	g++ -I $(INCLUDE_DIR) $(SRC) -o $(OUTFILE) $(WXCONFIG_FLAGS)

nbake: app
	@echo "\033[32mStarting...\033[0m"
	./app.o

.PHONY: clean
clean:
	rm -f *.o $(OUTFILE)