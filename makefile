NAME = Main
LFLAGS = -lglfw -ldl -lGL

all:
	g++ -Ofast -o bin/$(NAME).exe src/*.c src/*.cpp -D NDEBUG -I include -L lib $(LFLAGS)

debug:
	g++ -o bin/$(NAME)DEBUG.exe src/*.c src/*.cpp -I include -L lib $(LFLAGS)
