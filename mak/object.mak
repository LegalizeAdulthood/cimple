%.o : %.cpp
	$(CXX) -c $(FLAGS) $(DEFINES) $(INCLUDES) -o $*.o $*.cpp
