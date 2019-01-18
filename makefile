CC = g++
FLAGS = -O3 -std=c++11 -g
TARGETS = testing_linear_enumerator testing_discrete_enumerator testing_cartesian_enumerator testing_powerset_enumerator
ABSTRACT = enumerator.h set_enumerator.h

all: $(TARGETS)

testing_linear_enumerator: testing_linear_enumerator.cpp linear_enumerator.h $(ABSTRACT)
	$(CC) $(FLAGS) -o $@ $<

testing_discrete_enumerator: testing_discrete_enumerator.cpp discrete_enumerator.h $(ABSTRACT)
	$(CC) $(FLAGS) -o $@ $<

testing_cartesian_enumerator: testing_cartesian_enumerator.cpp cartesian_enumerator.h $(ABSTRACT)
	$(CC) $(FLAGS) -o $@ $<

testing_powerset_enumerator: testing_powerset_enumerator.cpp powerset_enumerator.h $(ABSTRACT)
	$(CC) $(FLAGS) -o $@ $<

clean:
	rm -rf *.o $(TARGETS)
