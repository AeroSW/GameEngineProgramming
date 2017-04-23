#ifndef ASW_TRIPLET_H
#define ASW_TRIPLET_H

namespace asw{
	template<class T, class U, class V>
	class triplet{
		private:
			T * t_obj;
			U * u_obj;
			V * v_obj;
		public:
			triplet();
			triplet(const T &t, const U &u, const V &v);
			triplet(T * t, U * u, V * v);
			triplet(const triplet &t);
			virtual ~triplet();
			
			virtual T * first_ptr();
			virtual U * second_ptr();
			virtual V * third_ptr();
			
			virtual T& first();
			virtual U& second();
			virtual V& third();
			
			virtual void set_first(const T &t);
			virtual void set_first(T * t);
			virtual void set_second(const U &u);
			virtual void set_second(U * u);
			virtual void set_third(const V &v);
			virtual void set_third(V * v);
			
			virtual triplet& operator=(const triplet &t);
	};
	template<class T, class U, class V>
	triplet<T,U,V>::triplet(){
		t_obj = nullptr;
		u_obj = nullptr;
		v_obj = nullptr;
	}
	template<class T, class U, class V>
	triplet<T,U,V>::triplet(const T &t, const U &u, const V &v){
		t_obj = new T(t);
		u_obj = new U(u);
		v_obj = new V(v);
	}
	template<class T, class U, class V>
	triplet<T,U,V>::triplet(T * t, U * u, V * v){
		t_obj = t;
		u_obj = u;
		v_obj = v;
	}
	template<class T, class U, class V>
	triplet<T,U,V>::triplet(const triplet &t){
		t_obj = new T(*t.t_obj);
		u_obj = new U(*t.u_obj);
		v_obj = new V(*v.v_obj);
	}
	template<class T, class U, class V>
	triplet<T,U,V>::~triplet(){
		if(t_obj != nullptr){
			delete t_obj;
			t_obj = nullptr;
		}
		if(u_obj != nullptr){
			delete u_obj;
			u_obj = nullptr;
		}
		if(v_obj != nullptr){
			delete v_obj;
			v_obj = nullptr;
		}
	}
	template<class T, class U, class V>
	T * triplet<T,U,V>::first_ptr(){
		return t_obj;
	}
	template<class T, class U, class V>
	U * triplet<T,U,V>::second_ptr(){
		return u_obj;
	}
	template<class T, class U, class V>
	V * triplet<T,U,V>::third_ptr(){
		return v_obj;
	}
	template<class T, class U, class V>
	T& triplet<T,U,V>::first(){
		return *t_obj;
	}
	template<class T, class U, class V>
	U& triplet<T,U,V>::second(){
		return *u_obj;
	}
	template<class T, class U, class V>
	V& triplet<T,U,V>::third(){
		return *v_obj;
	}
	template<class T, class U, class V>
	void triplet<T,U,V>::set_first(const T &t){
		if(t_obj != nullptr){
			delete t_obj;
			t_obj = nullptr;
		}
		t_obj = new T(t);
	}
	template<class T, class U, class V>
	void triplet<T,U,V>::set_first(T * t){
		if(t_obj != nullptr){
			delete t_obj;
			t_obj = nullptr;
		}
		t_obj = t;
	}
	template<class T, class U, class V>
	void triplet<T,U,V>::set_second(const U &u){
		if(u_obj != nullptr){
			delete u_obj;
			u_obj = nullptr;
		}
		u_obj = new U(u);
	}
	template<class T, class U, class V>
	void triplet<T,U,V>::set_second(U * u){
		if(u_obj != nullptr){
			delete u_obj;
			u_obj = nullptr;
		}
		u_obj = u;
	}
	template<class T, class U, class V>
	void triplet<T,U,V>::set_third(const V &v){
		if(v_obj != nullptr){
			delete v_obj;
			v_obj = nullptr;
		}
		v_obj = new V(v);
	}
	template<class T, class U, class V>
	void triplet<T,U,V>::set_third(V * v){
		if(v_obj != nullptr){
			delete v_obj;
			v_obj = nullptr;
		}
		v_obj = v;
	}
	template<class T, class U, class V>
	triplet& triplet<T,U,V>::operator=(const triplet &t){
		if(t_obj != nullptr){
			delete t_obj;
			t_obj = nullptr;
		}
		if(u_obj != nullptr){
			delete u_obj;
			u_obj = nullptr;
		}
		if(v_obj != nullptr){
			delete v_obj;
			v_obj = nullptr;
		}
		t_obj = new T(*t.t_obj);
		u_obj = new U(*t.u_obj);
		v_obj = new V(*t.v_obj);
		return *this;
	}
}

#endif