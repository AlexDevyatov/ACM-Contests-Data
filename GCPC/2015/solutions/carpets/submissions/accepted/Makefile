CFLAGS += -Wall -std=c++11 -Werror -pedantic
CXXFLAGS += -Wall -std=c++11 -Werror -pedantic

%: %.cxx
	$(CXX) $(CXXFLAGS) -o $@ $^

%.class: %.java
	javac $<
