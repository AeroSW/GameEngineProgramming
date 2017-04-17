#ifndef QUEUE_H
#define QUEUE_H

template<class T>
class queue_t{
	private:
		struct queue_node{
			T * ref;
			queue_node * next;
			queue_node();
			queue_node(T* ref);
			~queue_node();
		};
		queue_node * front;
		queue_node * end;
	public:
		queue_t();
		queue_t(const queue_t &q);
		virtual ~queue_t();

		virtual void enqueue(const T &obj);
		virtual void enqueue(T * obj);
		virtual T * dequeue();
		virtual T * peek(); // First item in queue
		virtual unsigned int size();
};


template<class T>
queue_t<T>::queue_node::queue_node(){
	ref = nullptr;
	next = nullptr;
}


template<class T>
queue_t<T>::queue_node::queue_node(T * ref){
	this->ref = ref;
	next = nullptr;
}

template<class T>
queue_t<T>::queue_node::~queue_node(){
	if(ref != nullptr){
		delete ref;
		ref = nullptr;
	}
	if(next != nullptr){
		delete next;
		next = nullptr;
	}
}

template<class T>
queue_t<T>::queue_t(){
	front = nullptr;
	end = nullptr;
}

template<class T>
queue_t<T>::queue_t(const queue_t &q){
	front = nullptr;
	end = nullptr;
	queue_node * prev = nullptr;
	queue_node * curr = q.front;
	while(curr != nullptr){
		T * curr_ref = curr->ref; // pull q's node's reference value
		T * copy_ref = new T(*curr_ref); // copy the item being referenced
		queue_node * copy = new queue_node(copy_ref); // Create a new node with the copy's reference
		if(front == nullptr) front = copy; //
		if(prev != nullptr) prev->next = copy;
		prev = copy;
		curr = curr->next;
	}
	if(end == nullptr) end = prev;
}

template<class T>
queue_t<T>::~queue_t(){
	if(front != nullptr){ // should recursively delete everthing.
		delete front;
	}
}

template<class T>
void queue_t<T>::enqueue(const T &obj){
	T * copy = new T(obj);
	queue_node * node = new queue_node(copy);
	if(front == nullptr) front = node;
	if(end == nullptr) end = node;
	else{
		end->next = node;
		end = node;
	}
}

template<class T>
void queue_t<T>::enqueue(T * obj){
	queue_node * node = new queue_node(obj);
	if(front == nullptr) front = node;
	if(end == nullptr) end = node;
	else{
		end->next = node;
		end = node;
	}
}

template<class T>
T * queue_t<T>::dequeue(){
	if(front == nullptr) return nullptr;
	queue_node * node = front->next;
	T * obj = front->ref;
	front->ref = nullptr; // Prevents obj's memory from being deallocated.
	front->next = nullptr; // Prevents recursive node cleaning.
	delete front;
	front = node;
	if(front == nullptr) end = nullptr;
	return obj;
}

template<class T>
T * queue_t<T>::peek(){
	if(front == nullptr) return nullptr;
	return front->ref;
}

template<class T>
unsigned int queue_t<T>::size(){
	queue_node * curr = front;
	unsigned int count = 0;
	while(curr != nullptr){
		count++;
		curr = curr->next;
	}
	return count;
}

#endif
