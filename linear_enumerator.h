#ifndef _LINEAR_ENUMERATOR_H_
#define _LINEAR_ENUMERATOR_H_

#include "enumerator.h"

template <typename T>
class LinearEnumerator : public Enumerator<T> {
	public:
		LinearEnumerator(const T& start, const T& end, const T& step_size) : start(start), end(end), step_size(step_size), cur(start) {
			increasing = (end >= start);
		}

		void reset() override;
	protected:
		void step(T&) override;
		bool stop() override;

		T cur;
		T start;
		T end;
		T step_size;		
		bool increasing;
};


template <typename T>
void LinearEnumerator<T>::reset() {
	cur = start;
}

template <typename T>
void LinearEnumerator<T>::step(T& val) {
	val = cur;
	cur += step_size;
}

template <typename T>
bool LinearEnumerator<T>::stop() {
	if (increasing)	return cur > end;
	else return cur < end;
}



#endif
