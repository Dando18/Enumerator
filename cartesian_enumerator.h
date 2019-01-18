#ifndef _CARTESIAN_ENUMERATOR_H_
#define _CARTESIAN_ENUMERATOR_H_

#include <vector>
#include <assert.h>
#include <cstdio>
#include "set_enumerator.h"
#include "enumerator.h"

template <typename T>
class CartesianEnumerator : public SetEnumerator<T> {
	public:
		CartesianEnumerator(const std::vector<Enumerator<T>*>& enums) : enums(enums), done(false), loc(enums.size()-1) {
			should_enum = std::vector<bool> (enums.size(), true);
		}

		void reset() override;
	protected:
		void step(std::vector<T>& val) override;
		bool stop() override;

		std::vector<Enumerator<T>*> enums;
		std::vector<bool> should_enum;
		int loc;
		bool done;
};


template <typename T>
void CartesianEnumerator<T>::reset() {
	for (int i = 0; i < enums.size(); i++) {
		enums[i]->reset();
	}	
	loc = enums.size()-1;
}


template <typename T>
void CartesianEnumerator<T>::step(std::vector<T>& val) {
    val.resize(enums.size());
 
	
	for (int i = 0; i < should_enum.size(); i++) {
		if (!should_enum[i]) continue;
		enums[i]->next(val[i]);
		should_enum[i] = false;
	}

	while (loc >= 0 && enums[loc]->has_next()) { 
		enums[loc]->next(val[loc]); 
		enums[loc]->reset();
		loc--;
	}
	if (loc == -1) {
		done = true;
	} else {
		should_enum[loc] = true;
		loc = enums.size()-1;
	}
	
}

template <typename T>
bool CartesianEnumerator<T>::stop() {
	return done;
}

#endif
