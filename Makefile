appname := string-longer

CXX := g++
CXXFLAGS := -Wall -g

srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

clean:
	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend
