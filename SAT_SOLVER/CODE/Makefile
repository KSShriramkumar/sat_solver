CXX = g++
CXX_FLAGS = 

TARGET = solv
SRCS = src/main.cpp src/cnf_reader.cpp src/sat_solver.cpp
HDRS = header/cnf_reader.h header/sat_solver.h
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXX_FLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

	


