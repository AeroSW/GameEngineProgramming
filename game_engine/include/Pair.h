#ifndef PAIR_H
#define PAIR_H

#include "Comparable.h"
#include "PairException.h"

template<class T, class U>
class pair_t : comparable<T>, comparable<U>{
	private:
		T * f;
		U * s;

	public:
		/*!	\brief The identity constructor for pair_t.
		 *	This is the identity constructor for a pair_t object.
		 *	It does not initialize the objects.
		 */
		pair_t();
		pair_t(const T &obj, const U &ref);
		pair_t(T * obj, U * ref);
		pair_t(const pair_t &p);
		pair_t(pair_t * p);
		virtual ~pair_t();

		virtual int compare(T &skey) = 0;
		virtual int compare(U &skey) = 0;
		virtual T& first();
		virtual U& second();

		virtual void set_first(const T &obj);
		virtual void set_first(T * obj);
		virtual void set_second(const U &ref);
		virtual void set_second(U * obj);

		virtual pair_t& operator=(const pair_t &p);
		virtual pair_t* operator=(pair_t * p);
};

template<class T, class U>
pair_t<T,U>::pair_t(){
	f = nullptr;
	s = nullptr;
}

template<class T, class U>
pair_t<T,U>::pair_t(const T &one, const U &two){
	f = new T(one);
	s = new U(two);
}

template<class T, class U>
pair_t<T,U>::pair_t(T * one, U * two){
	f = one;
	s = two;
}

template<class T, class U>
pair_t<T,U>::pair_t(const pair_t &p){
	f = new T(*p.f);
	s = new U(*p.s);
}

template<class T, class U>
pair_t<T,U>::pair_t(pair_t * p){
	f = new T(*p->f);
	s = new U(*p->s);
}

template<class T, class U>
pair_t<T,U>::~pair_t(){
	if(f != nullptr)
		delete f;
	if(s != nullptr)
		delete s;
	f = nullptr;
	s = nullptr;
}

template<class T, class U>
T& pair_t<T,U>::first(){
	if(f == nullptr) PAIR_ASSERT(false, "Value being accessed is NULL.");
	return *f;
}
template<class T, class U>
U& pair_t<T,U>::second(){
	if(s == nullptr) PAIR_ASSERT(false, "Value being accessed is NULL.");
	return *s;
}

template<class T, class U>
void pair_t<T,U>::set_first(const T &value){
	if(f != nullptr){
		delete f;
		f = nullptr;
	}
	f = new T(value);
}
template<class T, class U>
void pair_t<T,U>::set_first(T * value){
	if(f != nullptr){
		delete f;
		f = nullptr;
	}
	f = value;
}
template<class T, class U>
void pair_t<T,U>::set_second(const U &value){
	if(s != nullptr){
		delete s;
		s = nullptr;
	}
	s = new U(value);
}
template<class T, class U>
void pair_t<T,U>::set_second(U * value){
	if(s != nullptr){
		delete s;
		s = nullptr;
	}
	s = value;
}

template<class T, class U>
pair_t<T,U>& pair_t<T,U>::operator=(const pair_t &p){
	if(f != nullptr)
		delete f;
	if(s != nullptr)
		delete s;
	f = new T(*p.f);
	s = new U(*p.s);
	return *this;
}
template<class T, class U>
pair_t<T,U>* pair_t<T,U>::operator=(pair_t * p){
	if(f != nullptr)
		delete f;
	if(s != nullptr)
		delete s;
	f = p->f;
	s = p->s;
	return this;
}

#endif
