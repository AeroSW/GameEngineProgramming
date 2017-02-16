#ifndef SCENENODE_H_
#define SCENENODE_H_

#include "Ogre.h"

class scenenode{
	std::shared_ptr<Ogre::SceneNode> my_node;
	std::shared_ptr<scenenode> > my_parent;
	std::vector<std::shared_ptr<scenenode> > my_children;
	
	void add_rotate(const std::vector<double> &rotation);
	void add_scale(const std::vector<double> &scaling);
	void add_translation(const std::vector<double> &translation);
	
	
	public:
		scenenode(const std::string &name, std::shared_ptr<Ogre::SceneManager> &sm);
		virtual ~scenenode();
		
		void add_transform(const transform &trans);
		void give_child(const std::shared_ptr<scenenode> &cnode);
		
}

#endif