CC = g++
INCDIRS = -I/usr/include -I/home/michaelb/dev/sword/include/thirdparty
WFLAGS = -std=c++17 -Wall -W -Wno-parentheses -Wno-unused-variable -Wno-sign-compare -Wno-reorder -Wno-uninitialized -Wno-unused-parameter -Wno-unused-local-typedefs
CFLAGS = -std=c++17 -g $(WFLAGS) $(INCDIRS) -fPIC
LDFLAGS = -lsword -lpthread -lxcb -lvulkan -lX11 -lreadline -ldl
LIB = /home/michaelb/dev/sword/lib
LDIRS = -L$(LIB) #-L$(LIB)/loader 
LINK = $(LDIRS) $(LDFLAGS)
SPV = build/shaders
BIN = bin
BUILD = build
CORE = src/core
PROG = src/programs
THIRD = src/thirdparty
TEST = test
_OBJS = lodepng.o context.o swapchain.o window.o renderer.o mem.o commander.o description.o event.o commandstate.o
OBJS = $(patsubst %, $(BUILD)/%, $(_OBJS))

main: $(BUILD)/main.o $(LIB)/libsword.a
	$(CC) $^ -o $(BIN)/$@ $(LINK) ; ctags -R .

%: $(BUILD)/%.o $(LIB)/libsword.a
	$(CC) $^ -o $(BIN)/$@ $(LINK) ; ctags -R .

$(TEST)/%: $(BUILD)/%.o $(LIB)/libsword.a
	$(CC) $^ -o $@ $(LINK) ; ctags -R .

$(TEST)/test : $(BUILD)/main.o
	$(CC) $^ -o $@ $(LINK) ; ctags -R .

$(BIN)/app : $(OBJS) 
	$(CC) $^ -o $@ $(LINK) ; ctags -R .

$(BUILD)/%.o : $(CORE)/%.cpp $(CORE)/%.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/%.o : $(PROG)/%.cpp $(PROG)/%.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/window.o : $(CORE)/window.cpp $(CORE)/window.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/mem.o : $(CORE)/mem.cpp $(CORE)/mem.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/event.o : $(CORE)/event.cpp $(CORE)/event.hpp $(CORE)/window.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/context.o : $(CORE)/context.cpp $(CORE)/context.hpp $(CORE)/commander.hpp $(CORE)/mem.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/swapchain.o : $(CORE)/swapchain.cpp $(CORE)/swapchain.hpp $(CORE)/context.hpp $(CORE)/window.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/commander.o : $(CORE)/commander.cpp $(CORE)/commander.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/util.o : $(CORE)/util.cpp $(CORE)/util.hpp $(CORE)/swapchain.hpp $(CORE)/context.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/lodepng.o : src/thirdparty/lodepng.cpp include/thirdparty/lodepng.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/occupant.o : $(CORE)/occupant.cpp $(CORE)/occupant.hpp $(CORE)/context.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/description.o : $(CORE)/description.cpp $(CORE)/description.hpp $(CORE)/context.hpp $(CORE)/mem.hpp $(CORE)/occupant.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/renderer.o : $(CORE)/renderer.cpp $(CORE)/renderer.hpp $(CORE)/context.hpp $(CORE)/commander.hpp $(CORE)/mem.hpp $(CORE)/util.hpp $(CORE)/swapchain.hpp $(CORE)/window.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/commandstate.o : $(CORE)/commandstate.cpp $(CORE)/commandstate.hpp $(CORE)/util.hpp $(CORE)/event.hpp $(CORE)/renderer.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/%.o : $(PROG)/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/lodepng.o : $(THIRD)/lodepng.cpp $(THIRD)/lodepng.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIB)/libsword.a : $(OBJS)
	ar rcs $@ $(OBJS)

.PHONY: clean shaders

clean:
	rm -f $(BUILD)/*.o ; rm -f $(LIB)/*.a

shaders: 
	python3 tools/compileShaders.py
