#include <cstdio>
#include "enumerators.h"


int main(int arc, char** argv) {

	LinearEnumerator<int> le (1, 3, 1);
	DiscreteEnumerator<int> de1 ({5, -3, -2});
	DiscreteEnumerator<int> de2 ({4, 5, 6});

	CartesianEnumerator<int> ce ({&le, &de1, &de2});
	std::vector<int> vals;

	while (ce.next(vals)) {
		printf("(");
		for (int i = 0; i < vals.size(); i++)
			printf("%d%s", vals[i], (i==vals.size()-1)?")\n":", ");
	}
	return 0;
}
