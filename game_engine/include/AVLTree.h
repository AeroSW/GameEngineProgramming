#ifndef AVLTREE_H
#define AVLTREE_H

#include "Pair.h"

#include <iostream>

template<class T>
class avl_tree{
	private:
		class avl_node : public pair_t<T,std::string>{
			private:
				avl_node * left_child;
				avl_node * right_child;
			public:
				avl_node(const T &obj, const std::string &str);
				avl_node(T * obj, std::string * str);
				avl_node(const avl_node &n);
				avl_node(avl_node * n);
				~avl_node();

				int compare(T &obj);
				int compare(std::string &str);

				unsigned int get_height();

				avl_node* left();
				avl_node* right();

				void set_left(avl_node * n);
				void set_right(avl_node * n);

				avl_node& operator=(const avl_node &n);
				avl_node* operator=(avl_node * n);
		};

		avl_node * root;
	//	unsigned int height;

		unsigned int calculate_height(std::string &skey);
		avl_node * check_balance(avl_node * node);
		avl_node * counter_clockwise_rotation(avl_node * node);
		avl_node * clockwise_rotation(avl_node * node);
		avl_node * insert(avl_node * curr, avl_node * node);
		avl_node * remove_left(std::string &skey, avl_node * node);
		avl_node * remove_right(std::string &skey, avl_node * node);
		void print_tree(avl_node * n);

	public:
		avl_tree();
		avl_tree(const avl_tree &tree);
		avl_tree(avl_tree * tree);
		~avl_tree();

		void add(const T &obj, const std::string &key);
		void add(T * obj, std::string * key);

		void remove(std::string &skey);
		T * pop(std::string &skey);

		T * get(const std::string &skey);
		void print_tree();
};

/*
 *	AVL Node definitions
 */
 template<class T>
avl_tree<T>::avl_node::avl_node(const T &obj, const std::string &key):
pair_t<T,std::string>(obj, key){
	left_child = nullptr;
	right_child = nullptr;
}
template<class T>
avl_tree<T>::avl_node::avl_node(T * obj, std::string * key):
pair_t<T,std::string>(obj,key){
	left_child = nullptr;
	right_child = nullptr;
}
template<class T>
avl_tree<T>::avl_node::avl_node(const avl_node &n):
pair_t<T,std::string>(){
	if(n.left_child != nullptr)
		left_child = new avl_node(n.left_child);
	else
		left_child = nullptr;

	if(n.right_child != nullptr)
		right_child = new avl_node(n.right_child);
	else
		right_child = nullptr;
}
template<class T>
avl_tree<T>::avl_node::avl_node(avl_node * n):
pair_t<T,std::string>(n){
	if(n->left_child != nullptr)
		left_child = new avl_node(n->left_child);
	else
		left_child = nullptr;

	if(n->right_child != nullptr)
		right_child = new avl_node(n->right_child);
	else
		right_child = nullptr;
}
template<class T>
avl_tree<T>::avl_node::~avl_node(){
	if(left_child != nullptr){
		delete left_child;
		left_child = nullptr;
	}
	if(right_child != nullptr){
		delete right_child;
		right_child = nullptr;
	}
}

template<class T>
unsigned int avl_tree<T>::avl_node::get_height(){
	unsigned int my_left_count = 0;
	unsigned int my_right_count = 0;
	if(left_child == nullptr && right_child == nullptr) return 1;
	if(left_child != nullptr)
		my_left_count = left_child->get_height() + 1;
	if(right_child != nullptr)
		my_right_count = right_child->get_height() + 1;
	if(my_left_count > my_right_count) return my_left_count;
	return my_right_count;
}

template<class T>
int avl_tree<T>::avl_node::compare(T &obj){
	T * my_first = &pair_t<T,std::string>::first();
	if(my_first == &obj) return 1;
	return 0;
}
template<class T>
int avl_tree<T>::avl_node::compare(std::string &skey){
	std::string &my_key = pair_t<T,std::string>::second();
	return my_key.compare(skey);
}

template<class T>
typename avl_tree<T>::avl_node * avl_tree<T>::avl_node::left(){
	return left_child;
}
template<class T>
typename avl_tree<T>::avl_node * avl_tree<T>::avl_node::right(){
	return right_child;
}

template<class T>
void avl_tree<T>::avl_node::set_left(avl_node * n){
	left_child = n;
}
template<class T>
void avl_tree<T>::avl_node::set_right(avl_node * n){
	right_child = n;
}

template<class T>
typename avl_tree<T>::avl_node& avl_tree<T>::avl_node::operator=(const avl_node &n){
	pair_t<T,std::string>::operator=(&n);
	if(left_child == nullptr){
		delete left_child;
		left_child = nullptr;
	}
	left_child = n.left_child;
	if(right_child == nullptr){
		delete right_child;
		right_child = nullptr;
	}
	right_child = n.right_child;
	return *this;
}
template<class T>
typename avl_tree<T>::avl_node* avl_tree<T>::avl_node::operator=(avl_node * n){
	pair_t<T,std::string>::operator=(n);
	if(left_child == nullptr){
		delete left_child;
		left_child = nullptr;
	}
	left_child = n->left_child;
	if(right_child == nullptr){
		delete right_child;
		right_child = nullptr;
	}
	right_child = n->right_child;
	return this;
}

/*******************************************//******************************************************************//*
 *	AVL Tree methods.
 *//****************************************//*******************************************************************/

template<class T>
avl_tree<T>::avl_tree(){
	root = nullptr;
}
template<class T>
avl_tree<T>::avl_tree(const avl_tree &tree){
	root = new avl_node(tree.root);
}
template<class T>
avl_tree<T>::avl_tree(avl_tree * tree){
	root = new avl_node(tree->root);
}

template<class T>
avl_tree<T>::~avl_tree(){
	delete root;
}

template<class T>
void avl_tree<T>::add(const T &obj, const std::string &key){
	avl_node * new_node = new avl_node(obj, key);
	if(root != nullptr){
		root = insert(root, new_node);
	//	std::cout << "Root key 1: " << root->second() << std::endl;
		root = check_balance(root);
	//	std::cout << "Root key 2: " << root->second() << std::endl;
	}
	else{
		root = new_node;
	}
}
template<class T>
void avl_tree<T>::add(T * obj, std::string * key){
	avl_node * new_node = new avl_node(obj, key);
	if(root == nullptr){
		root = new_node;
		return;
	}
	insert(root, new_node);
	root = check_balance(root);
}

template<class T>
void avl_tree<T>::remove(std::string &skey){
	avl_node * node;
	int val = root->compare(skey);
	if(val < 0){
		node = remove_left(skey, root);
	}
	else if(val > 0){
		node = remove_right(skey, root);
	}
	else{
		node = root;
		avl_node * root_right = root->right();
		avl_node * root_left = root->left();
	//	root = root_left;
		if(root_left != nullptr){
			avl_node * curr = root_left->right();
			avl_node * prev = root_left;
			while(curr != nullptr){
				prev = curr;
				curr = curr->right();
			}
			prev->set_right(root_right);
			root = check_balance(root_left);
		}
		else{
			root = check_balance(root_right);
		}
	}
	if(node != nullptr){
		node->set_right(nullptr);
		node->set_left(nullptr);
		delete node;
	}
}
template<class T>
T * avl_tree<T>::pop(std::string &skey){
	avl_node * node;
	int val = root->compare(skey);
//	std::cout << "Remove Value: " << val << std::endl;
	if(val > 0){
		node = remove_left(skey, root);
	}
	else if(val < 0){
		node = remove_right(skey, root);
	}
	else{
		node = root;
		avl_node * root_right = root->right();
		avl_node * root_left = root->left();
	//	root = root_left;
		if(root_left != nullptr){
			avl_node * curr = root_left->right();
			avl_node * prev = root_left;
			while(curr != nullptr){
				prev = curr;
				curr = curr->right();
			}
			prev->set_right(root_right);
			root = check_balance(root_left);
		}
		else{
			root = check_balance(root_right);
		}
	}
//	std::cout << "Finished finding node." << std::endl;
	if(node != nullptr){
		T * my_obj = new T(node->first());
	//	std::cout << "Mem Ref for node: " << &node->first() << "\n";
	//	std::cout << "Mem Ref for obj:  " << my_obj << "\n";
		node->set_right(nullptr);
		node->set_left(nullptr);
		delete node;
		return my_obj;
	}
	return nullptr;
}
template<class T>
T * avl_tree<T>::get(const std::string &skey){
	T obj;
	avl_node * curr = root;
	bool flag = false;
	while(curr != nullptr){
		int cmp = curr->compare(skey);
		if(cmp > 0){
			curr = curr->right();
		}
		else if(cmp < 0){
			curr = curr->left();
		}
		else{
			obj = &curr->first();
			flag = true;
			break;
		}
	}
	if(flag) return obj;
	return nullptr;
}



/* Private Methods */
template<class T>
typename avl_tree<T>::avl_node * avl_tree<T>::insert(avl_node * curr, avl_node * node){
	if(curr == nullptr) return node;
//	std::cout << "insert" << std::endl;
	std::string node_key = node->second();
	int comparison = curr->compare(node_key);
//	std::cout << "Comparison: " << comparison << std::endl;
	if(comparison > 0){
	//	std::cout << "Left" << std::endl;
		avl_node * curr_left = curr->left();
		if(curr_left != nullptr){
			curr_left = insert(curr_left, node);
			curr->set_left(curr_left);
		}
		else{
			curr->set_left(node);
			curr_left = node;
		}
	}
	else{
	//	std::cout << "Right" << std::endl;
		avl_node * curr_right = curr->right();
		if(curr_right != nullptr){
			curr_right = insert(curr_right, node);
			curr->set_right(curr_right);
		}
		else{
			curr->set_right(node);
			curr_right = node;
		}
	}
	return check_balance(curr);
}

template<class T>
typename avl_tree<T>::avl_node * avl_tree<T>::remove_left(std::string &skey, avl_node * parent){
	avl_node * child = parent->left();
	if(child == nullptr){
		return nullptr; // Ran into the end.  No match.
	}
	int res = child->compare(skey); // Handle comparison
	if(res > 0){ // If skey is in left branch
		return remove_left(skey, child);
	}
	else if(res < 0){ // If skey is in right branch
		return remove_right(skey, child);
	}
	avl_node * node_left = child->left();
	avl_node * node_right = child->right();
//	parent->set_left(node_left);
	if(node_left != nullptr){
		avl_node * curr = node_left->right();
		avl_node * prev = node_left;
		while(curr != nullptr){ // Iterate untill NULL is reached.
			prev = curr;
			curr = curr->right();
		}
		prev->set_right(node_right);
		node_left = check_balance(node_left);
		parent->set_left(node_left);
	}
	else{
		parent->set_left(node_right);
	}
	return child;
}
template<class T>
typename avl_tree<T>::avl_node * avl_tree<T>::remove_right(std::string &skey, avl_node * parent){
	avl_node * child = parent->right();
	if(child == nullptr) return nullptr; // Ran into the end.  No match.

	int res = child->compare(skey); // Handle comparison
	if(res > 0){ // If skey is in left branch
		return remove_left(skey, child);
	}
	else if(res < 0){ // If skey is in right branch
		return remove_right(skey, child);
	}
	avl_node * node_left = child->left();
	avl_node * node_right = child->right();
//	parent->set_left(node_left);
	if(node_right != nullptr){
		avl_node * curr = node_right->left();
		avl_node * prev = node_right;
		while(curr != nullptr){ // Iterate untill NULL is reached.
			prev = curr;
			curr = curr->left();
		}
		prev->set_left(node_left);
		node_right = check_balance(node_right);
		parent->set_right(node_right);
	}
	else{
		parent->set_right(node_left);
	}
	return child;
}


template<class T>
typename avl_tree<T>::avl_node * avl_tree<T>::check_balance(avl_node * node){ // Successfully checked!!!!!!
//	std::cout << "check_balance" << std::endl;
	if(node == nullptr) return nullptr;
	avl_node * node_left = node->left(); // Function instance methods declarations.
	avl_node * node_right = node->right();
	avl_node * left_child = nullptr;	// Predeclare these to save on # of lines
	avl_node * right_child = nullptr;
	unsigned int left_child_height = 0;
	unsigned int right_child_height = 0;
	unsigned int left_height = 0;
	unsigned int right_height = 0;

	if(node_left != nullptr) left_height = node_left->get_height(); // Get the heights of node's respective children's height
	if(node_right != nullptr) right_height = node_right->get_height();

	//std::cout << "Left Height: " << nod

	int height_diff = left_height - right_height; // Get their height difference

	if(height_diff > 1){ // Is left taller?
		left_child = node_left->left();
		right_child = node_left->right();
		if(left_child != nullptr) left_child_height = left_child->get_height();
		if(right_child != nullptr) right_child_height = right_child->get_height();
		if(left_child_height < right_child_height){
			node_left = counter_clockwise_rotation(node_left);
			node->set_left(node_left);
		}
		return clockwise_rotation(node);
	}
	else if(height_diff < -1){ // Is right taller?
		left_child = node_right->left();
		right_child = node_right->right();
		if(left_child != nullptr) left_child_height = left_child->get_height();
		if(right_child != nullptr) right_child_height = right_child->get_height();
		if(left_child_height > right_child_height){
			node_right = clockwise_rotation(node_right);
			node->set_right(node_right);
		}
		return counter_clockwise_rotation(node);
	}
	return node;
}

template<class T>
typename avl_tree<T>::avl_node * avl_tree<T>::clockwise_rotation(avl_node * node){ // Successfully checked!!!!!
//	std::cout << "CW Rotation" << std::endl;
	// node is the root of the rotation.
	avl_node * node_left = node->left(); // Detach node's left child
	node->set_left(nullptr);
	avl_node * left_right_child = node_left->right(); // Detach left child's right child
	node_left->set_right(nullptr);
	node->set_left(left_right_child); // Attach left child's right child to be node's new left child.
	node_left->set_right(node); // Attach node as left child's new right child.
	return node_left; // return the new root node.
}
template<class T>
typename avl_tree<T>::avl_node * avl_tree<T>::counter_clockwise_rotation(avl_node * node){
//	std::cout << "CCW Rotation" << std::endl;
	avl_node * node_right = node->right();
	node->set_right(nullptr);
	avl_node * right_left_child = node_right->left();
	node_right->set_left(nullptr);
	node->set_right(right_left_child);
	node_right->set_left(node);
	return node_right;
}



template<class T>
void avl_tree<T>::print_tree(){
	print_tree(root);
}
template<class T>
void avl_tree<T>::print_tree(avl_node * n){
	std::cout << "Node: " << n->second() << "\n";
	avl_node * left_ = n->left();
	if(left_ != nullptr){
		std::cout << "n left -  ";
		print_tree(left_);
	}
	avl_node * right_ = n->right();
	if(right_ != nullptr){
		std::cout << "n right - ";
		print_tree(right_);
	}
}

#endif
