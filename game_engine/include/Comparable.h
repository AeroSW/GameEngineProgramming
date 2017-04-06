#ifndef COMPARABLE_H
#define COMPARABLE_H

template<class T>
class comparable{
	private:
	//	T myself;
	public:
	//	comparable(T obj);
		virtual ~comparable(){}
		virtual int compare(T &obj) = 0;
};

#endif