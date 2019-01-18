#ifndef _DISCRETE_ENUMERATOR_H_
#define _DISCRETE_ENUMERATOR_H_

#include <vector>
#include "enumerator.h"

template <typename T>
class DiscreteEnumerator : public Enumerator<T> {
	public:
		DiscreteEnumerator(const std::vector<T>& input) : input(input), pos(0) {}

		void reset() override;
	protected:
		void step(T& val) override;
		bool stop() override;
		
		unsigned int pos;
		std::vector<T> input;
};


template <typename T>
void DiscreteEnumerator<T>::reset() {
	pos = 0;
}

template <typename T>
void DiscreteEnumerator<T>::step(T& val) {
	val = input.at(pos++);
}

template <typename T>
bool DiscreteEnumerator<T>::stop() {
	return (pos == input.size());
}



#endif
