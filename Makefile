OBJS := main.o Server.o Request.o Response.o
LDLIBS := -lpthread
CXXFLAGS := -g --std=c++17

all: kshttp

Request.o: Request.cpp Request.hpp

Response.o: Response.cpp Response.hpp Server.hpp

Server.o: Request.o Server.cpp Server.hpp

main.o: main.cpp Server.o

kshttp: $(OBJS)
	$(CXX) -o c-serve ${LDLIBS} $(CXXFLAGS) $(OBJS)

.PHONY: clean
clean:
	rm $(OBJS)