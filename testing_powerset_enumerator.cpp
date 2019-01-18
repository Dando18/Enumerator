#include <vector>
#include <string>
#include <cstdio>
#include "powerset_enumerator.h"

int main(int argc, char** argv) {

	std::vector<std::string> names { "bill", "joe", "howard", "ed" };
	
	PowersetEnumerator<std::string> pow_enum (names);
	std::vector<std::string> group;

	while (pow_enum.next(group)) {
		for (int i = 0; i < group.size(); i++)
			printf("%s ", group[i].c_str());
		printf("\n");
	}

	return 0;
}
