SFLAGS = -std=c++11 -fsanitize=address,leak,undefined -g
CPP_FILES = file_sys.cpp cli.cpp utils.cpp tester.cpp
H_FILES = file_sys.h cli.h utils.h

all: tester tester_leak

tester: $(CPP_FILES) $(H_FILES)
	g++ -o $@ $(CPP_FILES)

tester_leak: $(CPP_FILES) $(H_FILES)
	g++ $(SFLAGS) -o $@ $(CPP_FILES)