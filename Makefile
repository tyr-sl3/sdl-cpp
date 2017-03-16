TARGET = sdltest
CXX = clang++
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)
CXXFLAGS = -std=c++1z -Wold-style-cast -Woverloaded-virtual -Wfloat-equal \
			-Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align \
			-Wconversion -Wshadow -Weffc++ -Wredundant-decls \
			-Winit-self -Wswitch-default -Wswitch-enum -Wundef \
			-Winline -Wunused -Wuninitialized
FLAGS_DEBUG = -D __SDL__ -O0 -g $(SDL_CFLAGS)
FLAGS_RELEASE = -D __SDL__ -O2 -DNDEBUG $(SDL_CFLAGS)
LDFLAGS = -lm $(SDL_LDFLAGS)

SOURCES=src/*.cpp
INCLUDE=./include

all: debug

debug:
	$(CXX) -o $(TARGET) $(OBJECTS) $(CXXFLAGS) $(FLAGS_DEBUG) $(LDFLAGS)
  
debug:
	$(CXX) -o $(TARGET) $(OBJECTS) $(CXXFLAGS) $(FLAGS_RELEASE) $(LDFLAGS)
  
clean:
	rm -f *.o game/*.o game/ai/*.o y3d/*.o ${TARGET}
 
