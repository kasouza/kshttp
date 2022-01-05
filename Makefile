OBJS := $(addprefix build/, main.o Server.o Request.o Response.o)
# LDLIBS := -lpthread
CXXFLAGS := -g --std=c++17 -Iinclude

all: $(OBJS)
	$(CXX) -o kshttp -lpthread $(OBJS)

build/main.o: src/main.cpp include/Request.hpp include/Response.hpp include/Server.hpp
build/Request.o: src/Request.cpp include/Request.hpp
build/Response.o: src/Response.cpp include/Response.hpp
build/Server.o: src/Server.cpp include/Request.hpp include/Response.hpp include/Server.hpp

build/%.o: src/%.cpp
	$(CXX) -Iinclude -c -o $@ $<

clean:
	rm $(OBJS)

.PHONY: clean