#ifndef ASW_SINGLETON_H
#define ASW_SINGLETON_H

class singleton{
	protected:
		static singleton * my_reference;
		static unsigned int my_ref_count;
		virtual ~singleton();
	public:
		virtual unsigned int my_count() = 0;
	//	static singleton * get_ref(){return nullptr;}
		virtual void deref() = 0;
};

#endif
