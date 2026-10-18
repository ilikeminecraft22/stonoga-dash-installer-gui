CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3 $(shell pkg-config --cflags gtkmm-4.0)
LDLIBS = $(shell pkg-config --libs gtkmm-4.0)

TARGET = stonoga-dash-installer

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean