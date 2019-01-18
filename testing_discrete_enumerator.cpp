#include <cstdio>
#include <vector>
#include "discrete_enumerator.h"

int main(int argc, char** argv) {

	unsigned int len = 15;
	std::vector<int> nums (len);
	for (int i = 0; i < len; i++) nums[i] = i;

	DiscreteEnumerator<int> dis_enum (nums);
	int cur;

	while (dis_enum.next(cur)) {
		printf("%d\n", cur);
	}

	return 0;
}
