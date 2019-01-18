#ifndef _POWERSET_ENUMERATOR_H_
#define _POWERSET_ENUMERATOR_H_

#include <vector>
#include "assert.h"
#include "set_enumerator.h"
#include "enumerator.h"

template <typename T>
class PowersetEnumerator : public SetEnumerator<T> {
	public:
		PowersetEnumerator(const std::vector<T>& set) : set(set), cur(0) {
			assert ( set.size() <= 64 );
		}
		
		void reset() override;
	protected:
		void step(std::vector<T>& group) override;
		bool stop() override;

		unsigned int cur;
		std::vector<T> set;
};


template <typename T>
void PowersetEnumerator<T>::reset() {
	cur = 0;
}


template <typename T>
void PowersetEnumerator<T>::step(std::vector<T>& group) {
	group.clear();
	for (int i = 0; i < set.size(); i++) {
		if (cur & (1 << i)) {
			group.push_back(set[i]);
		}
	}
	cur++;
}

template <typename T>
bool PowersetEnumerator<T>::stop() {
	return (cur == 1 << set.size());
}

#endif
