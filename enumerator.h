#ifndef _ENUMERATOR_H_
#define _ENUMERATOR_H_

template <typename T>
class Enumerator {
	public:
		virtual bool next(T& val) {
			if (stop()) return false;
			
			step(val);
			return true;
		}

        virtual bool has_next() { return stop(); };

		virtual bool run(void (*func)(const T&)) {
			T val;
			while (next(val)) {
				func(val);
			}
			return true;
		}
		
		virtual void reset();

	protected:
		Enumerator(){}	// to prevent instantiation of abstract base class
		
		virtual void step(T&) = 0;
		virtual bool stop() = 0;
};

#endif
