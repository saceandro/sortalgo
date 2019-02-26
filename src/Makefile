SRCS := $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)
TARGETS = binarySearch insertionSort ternaryQsort ternaryQsortCheck msdRadixSort merSearch
RM = rm -f

all: $(TARGETS)
%: %.cc
	g++ -Wall -g -o $@ $<
clean:
	$(RM) $(OBJS) $(TARGETS)
check-syntax:
	$(CXX) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
.PHONY: clean check-syntax
