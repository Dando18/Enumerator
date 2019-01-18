#ifndef _ENUMERATOR_H_
#define _ENUMERATOR_H_

template <typename T>
class Enumerator {
	public:
		virtual bool next(T& val) {
			if (stop()) return false;
			
			val = step();
			return true;
		}
		virtual bool run(void (*func)(const T&)) {
			T val;
			do {
				func(val);
			} while (next(val));
		}

	protected:
		Enumerator(){}	// to prevent instantiation of abstract base class
		virtual T step() = 0;
		virtual bool stop() = 0;
		
		T last;
};

#endif
