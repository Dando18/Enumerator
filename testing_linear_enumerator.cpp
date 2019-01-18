#include <cstdio>
#include "linear_enumerator.h"

int main(int argc, char** argv) {

	LinearEnumerator<float> lin_enum (-10.0, 10.0, 0.5);
	float val;

	while (lin_enum.next(val)) {
		printf("%.1f\n", val);
	}

	return 0;
}
