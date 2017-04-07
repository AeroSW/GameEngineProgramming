#ifndef INTERFACES_INTERFACE_ACTION_H
#define INTERFACES_INTERFACE_ACTION_H

class interface;
class interface_event;

typedef void (interface::*ui_action)(const interface_args&);

class interface_action{
	protected:
		std::string key;
		ui_action action_reference;
		
	public:
		virtual ~interface_action(){}
		virtual std::string get_key() = 0;
		virtual ui_action get_action() = 0;
};

#endif