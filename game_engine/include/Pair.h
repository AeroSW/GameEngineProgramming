#ifndef ASW_PAIR_H
#define ASW_PAIR_H

namespace asw{
	template<class T, class U>
	class pair{
		private:
			T * t_obj;
			U * u_obj;
		public:
			pair();
			pair(const T &t, const U &u);
			pair(T * t, U * u);
			pair(const pair &p);
			~pair();

			T * first();
			U * second();

			void set_first(const T &t);
			void set_first(T * t);
			void set_second(const U &u);
			void set_second(U * u);

			pair& operator=(const pair &p);
	};
	template<class T, class U>
	pair<T,U>::pair(){
		t_obj = nullptr;
		u_obj = nullptr;
	}
	template<class T, class U>
	pair<T,U>::pair(const T &t, const U &u){
		t_obj = new T(t);
		u_obj = new U(u);
	}
	template<class T, class U>
	pair<T,U>::pair(T * t, U * u){
		t_obj = t;
		u_obj = u;
	}
	template<class T, class U>
	pair<T,U>::pair(const pair<T,U> &p){
		t_obj = new T(*p.t_obj);
		u_obj = new U(*p.u_obj);
	}
	template<class T, class U>
	pair<T,U>::~pair(){
		if(t_obj != nullptr){
			delete t_obj;
			t_obj = nullptr;
		}
		if(u_obj != nullptr){
			delete u_obj;
			u_obj = nullptr;
		}
	}
	template<class T, class U>
	T * pair<T,U>::first(){
		return t_obj;
	}
	template<class T, class U>
	U * pair<T,U>::second(){
		return u_obj;
	}
	template<class T, class U>
	void pair<T,U>::set_first(const T &t){
		if(t_obj != nullptr){
			delete t_obj;
			t_obj = nullptr;
		}
		t_obj = new T(t);
	}
	template<class T, class U>
	void pair<T,U>::set_first(T * t){
		if(t_obj != nullptr){
			delete t_obj;
			t_obj = nullptr;
		}
		t_obj = t;
	}
	template<class T, class U>
	void pair<T,U>::set_second(const U &u){
		if(u_obj != nullptr){
			delete u_obj;
			u_obj = nullptr;
		}
		u_obj = new U(u);
	}
	template<class T, class U>
	void pair<T,U>::set_second(U * u){
		if(u_obj != nullptr){
			delete u_obj;
			u_obj = nullptr;
		}
		u_obj = u;
	}
	template<class T, class U>
	pair<T,U>& pair<T,U>::operator=(const pair<T,U> &p){
		if(t_obj != nullptr){
			delete t_obj;
			t_obj = nullptr;
		}
		if(u_obj != nullptr){
			delete u_obj;
			u_obj = nullptr;
		}
		t_obj = new T(*p.t_obj);
		u_obj = new U(*p.u_obj);
		return *this;
	}
}

#endif
