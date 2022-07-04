CXX=g++
CXXFLAGS= -std=c++11

prisoners: main.cpp main.h
	$(CXX) -o main main.cpp $(CXXFLAGS)