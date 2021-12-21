OBJS := main.o
LDLIBS := -lpthread

all: c-srv

c-srv: $(OBJS)
	$(CXX) -o c-serve ${LDLIBS} $(CXXFLAGS) $(OBJS)

.PHONY: clean
clean:
	rm $(OBJS)