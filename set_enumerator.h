#ifndef _SET_ENUMERATOR_H_
#define _SET_ENUMERATOR_H_

#include <vector>

template <typename T>
class SetEnumerator {
	public:
		virtual bool next(std::vector<T>& val) {
			if (stop()) return false;
			
			step(val);
			return true;
		}
        
        virtual bool has_next() { return stop(); }

		virtual bool run(void (*func)(const std::vector<T>&)) {
			std::vector<T> val;
			while (next(val)) {
				func(val);
			}
			return true;
		}
		
		virtual void reset();

	protected:
		SetEnumerator(){}	// to prevent instantiation of abstract base class
		
		virtual void step(std::vector<T>&) = 0;
		virtual bool stop() = 0;
};

#endif
