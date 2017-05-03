#ifndef MANAGERS_CORE_H
#define MANAGERS_CORE_H

// STD Libraries
#include <string>
#include <vector>
// Personal Libraries
#include "include/type_defs.h"
#include "include/enums.h"

// Forward Declarations
class Audio;
class Input;
//class level;
class Logger; // Going to be static methods.
class Render;
class Scripter;
//class gameparser;
class CoreParser;

//enum input_t{KEYBOARD=1,MOUSE,DUALSHOCK4,XBOX1};

class Core{
	private:
		static Core * core_manager;
		static Audio * audio_manager;
	//	static level * level_manager; // Planning on making this a sub-type to render_manager
		static Scripter * script_manager;
		static Render * render_manager;
		
		static CoreParser * my_parser;
		
		static bool input_flag;
		
	//	enum gamepad_t{DS4=1,XB1,NONE};
		std::vector<input*> input_managers;
	//	gamepad_t gamepad_type;

		virtual void coreInit(const std::string &dox);
		virtual void renderInit(const std::string &dox);
		virtual void audioInit(const std::string &dox);
		virtual void inputsInit(input_t &type, const std::string &dox);
		virtual void scriptsInit(const std::string &dox);

	protected:
		/*!
		 *	\brief The constructor for the game engine's core.
		 *	\details The constructor which creates the game engine based off the given XML
		 *	file.
		 *
		 *	\param my_dox The document which acts as the blueprint defining how to build
		 *	the game engine.
		 *	\exception GameError A GameError is generated when certain criteria are not met for the
		 *	game engine's creation.
		 */
		Core(const std::string &my_dox);
		/*!
		 *	\brief The destructor for the game engine.
		 *	\details The destructor which calls the destructors for the fundamental components
		 *	in this game engine if they exist.
		 */
		virtual ~Core();

	public:
		/*!
		 *	\brief A function which will initialize the game engine.
		 *	\details A function which initializes the game engine using the given xml
		 *	document name as an argument.
		 *
		 *	\param dox A name to the XML file which holds the names of the other documents
		 *	needed to finish constructing the game engine.
		 *
		 *	\return A boolean value indicating whether the game engine was successfully
		 *	constructed or not.
		 */
		static bool initialize(const std::string &dox);
		/*!
		 *	\brief A function which will terminate the game engine.
		 *	\details A function which will call the core's destructor to terminate the
		 *	game engine's processes.
		 */
		static bool destroy();
		/*!
		 *	\brief A function which will return a pointer reference to the core manager.
		 *	\details A function which returns a pointer to the core manager singleton object.
		 *
		 *	\param void
		 *	\return A pointer to the reference of the core manager.
		 *	\exception GameError A GameError will be generated if the singleton object
		 *	does not exist.
		 */
		static core * getSingletonPtr();
		
		/*************************************************//***********
		 *		Manager Creation Functions.
		 *************************************************//**********/
		
		/*!
		 *	\brief Function to construct the render manager.
		 *	\details A function which will construct the render manager object using
		 *	the provided XML document.
		 *
		 *	\param render_dox Path/Name of the XML document which will construct the Render Manager.
		 *	\return void
		 *	\exception GameError The GameError exception is generated whenever a failure to
		 *	initialize the render manager occurs.
		 */
		virtual void createRender(const std::string &render_dox);
		/*!
		 *	\brief A function which will create an input of the given type.
		 *	\details A function which will create the input manager for the given type of
		 *	input.
		 *
		 *	\param type An input_t enum describing the type of input manager to create.
		 *	\return void
		 *	\exception GameError A GameError is generated if the input manager is failed
		 *	to be created or already exists.
		 */
		virtual void createInput(input_t &type, const std::string &input_dox);
	//	virtual void create_level(const std::string &lvl_dox);
		/*!
		 *	\brief A function which initializes the log manager.
		 *	\details A function which initializes the log manager to store log information
		 *	into the given log text document.
		 *
		 *	\param log_dox Path and name for the document where the logs for the core
		 *	will be stored.
		 *	\return void
		 */
		virtual void createLogger(const std::string &log_dox);
		/*!
		 *	\brief A function which will initialize the script manager.
		 *	\details A function which will initialize the script manager with the given XML
		 *	documentation.
		 *
		 *	\param script_dox The document which is needed to initialize the script manager.
		 *	\return void
		 *	\exception GameError A GameError will be generated if the script manager is failed to be
		 *	initialized.
		 */
		virtual void createScripter(const std::string &script_dox);
		/*!
		 *	\brief A function which will initialize the audio manager with the given document.
		 *	\details A function which will initialize the audio manager with the given XML document.
		 *
		 *	\param audio_dox An XML document containing the information needed for the script manager
		 *	to be initialized.
		 *	\return void
		 *	\exception GameError A GameError is generated when the audio manager is not initialized
		 *	properly.
		 */
		virtual void createAudio(const std::string &audio_dox);
	//	virtual void create_level(const std::string &level_dox);
		
		/***************************************************//******************
		 *			Window Functions
		 ***************************************************//*****************/
		 
		/*!
		 *	\brief A function which returns the height of the window in pixels.
		 *	\details A function which returns the height of the window in pixels.
		 *
		 *	\param void
		 *	\return Unsigned 32-bit integer.
		 */
		virtual uint32 getWindowHeight();
		/*!
		 *	\brief A function which returns the width of the window in pixels.
		 *	\details A function which returns the width of the window in pixels.
		 *
		 *	\param void
		 *	\return Unsigned 32-bit integer.
		 */
		virtual uint32 getWindowWidth();
		/*!
		 *	\brief A function which returns the handler for the window.
		 *	\details A function which returns the handler for the window.
		 *
		 *	\param void
		 *	\return Unsigned 32-bit integer.
		 */
		virtual uint32 getWindowHandler();
		
		/*!
		 *	\brief A function which returns the name of the current level.
		 *	\details A function which returns the name of the current level.
		 *
		 *	\param void
		 *	\return C++ Standard String object containing the level's name.
		 */
		virtual std::string levelName();
		
		/******************************************************************//*****
		 *				Manager Message Passing Routines
		 ***************************//*******************************************/
		 
		 // Script Message Passing Methods
		 
		/*!
		 *	\brief A function which passes the method to execute a script to the script manager.
		 *	\details A function which passes the name of a script to be executed and its
		 *	arguments to the script manager.
		 *
		 *	\param script The path and name of the script which will be executed be the script
		 *	manager.
		 *	\param script_arguments A vector of arguments which the script will need to execute.
		 *	(Note, the vector of script arguments can be empty if the script has no arguments.)
		 *	\return void
		 */
		virtual void callScript(const std::string &script, std::vector<std::string> &script_arguments);
		
		// Audio Message Passing Methods
		
		/*!
		 *	\brief A function which will start the audio queue.
		 *	\details A function which will inform the audio manager to play all songs which have
		 *	been queued up until this point and until the queue is empty.
		 *
		 *	\param void
		 *	\return void
		 */
		virtual void playAudio();
		/*!
		 *	\brief A function which will stop audio from playing.
		 *	\details A function which will tell the audio manager to stop playing audio and
		 *	empty the current queued list.
		 *
		 *	\param void
		 *	\return void
		 */
		virtual void stopAudio();
		/*!
		 *	\brief A function which will add the given audio file onto the audio manager's queue.
		 *	\details A function which informs the audio manager to add the given mp3 file onto its
		 *	play queue.
		 *
		 *	\param audio_name The path and name for the MP3 audio file which is to be placed onto
		 *	the queue.
		 *	\return void
		 *	\exception GameError A GameError will be generated if the audio file does not exist.
		 */
		virtual void queueAudio(const std::string &audio_name);
		
		// Render Message Passing Methods
		
		/*!
		 *	\brief Loads level with given name.
		 *	\details This function passes a message to the render manager to load a level with the
		 *	given name.
		 *
		 *	\param level_name The name of the level to be loaded.
		 *	\return void
		 *	\exception GameError A GameError will be generated if a level with the given name
		 *	does not exist.
		 */
		virtual void switchLevel(const std::string &level_name);
		/*!
		 *	\brief Translates the given object by the given adjustments.
		 *	\details Translates the object with name 'object_name' by x, y, and z units from its local
		 *	position.
		 *
		 *	\param object_name The name of the object to be moved.
		 *	\param x The amount of units along the x axis for the object to be moved.
		 *	\param y The amount of units along the y axis for the object to be moved.
		 *	\param z The amount of units along the z axis for the object to be moved.
		 *	\return void
		 *	\exception GameError A GameError will be generated if an object with the given name does
		 *	not exist.
		 */
		virtual void moveObject(const std::string &object_name, float x, float y, float z);
		/*!
		 *	\brief Rotates the given object about the given axis(global or local) by w radians.
		 *	\details Informs the render manager that the object with 'object_name' needs to be
		 *	rotated by 'w' radians along its local/global 'axis'.
		 *
		 *	\param object_name The name of the object being rotated.
		 *	\param axis An enum value describing which axis to rotate about.
		 *	\param type An enum value describing if the rotation is about the global or local axis.
		 *	\param w The angle in radians which the object will be rotated.
		 *	\return void
		 *	\exception GameError A GameError will be generated if an object with the given name does
		 *	not exist.
		 */
		virtual void rotateObject(const std::string &object_name, axis_t &axis, rotation_t &type, float w);
		/*!
		 *	\brief A function which will scale the requested object's dimensions.
		 *	\details A function which will tell the render manager to scale the object with the
		 *	given name by the provided values.  The object's local x will be scaled by the given
		 *	x value.  The same will occur with the given y and z values.
		 *
		 *	\param object_name The name of the object which is being scaled.
		 *	\param x The value which the object's local x will be scaled by.
		 *	\param y The value which the object's local y will be scaled by.
		 *	\param z The value which the object's local z will be scaled by.
		 *	\return void
		 *	\exception GameError A GameError will be generated if the object does not exist.
		 */
		virtual void scaleObject(const std::string &object_name, float x, float y, float z);
		/*!
		 *	\brief A function which reveals a hidden object with the given name.
		 *	\details A function which tells the render manager to reveal an object
		 *	with the name 'object_name'.
		 *
		 *	\param object_name The name of the object to be revealed.
		 *	\return void
		 *	\exception GameError A GameError will be generated if the object does not exist.
		 */
		virtual void showObject(const std::string &object_name);
		/*!
		 *	\brief A function which hides an object with the given name.
		 *	\details A function which tells the render manager to hide an object
		 *	with the name 'object_name'.
		 *
		 *	\param object_name The name of the object to be hidden.
		 *	\return void
		 *	\exception GameError A GameError will be generated if the object does not exist.
		 */
		virtual void hideObject(const std::string &object_name);
		
		// Input Methods
		
		/*!
		 *	\brief A function which simulates the described key being pressed.
		 *	\details A function which informs render manager of a key being pressed by giving it
		 *	the key's ascii value.
		 *
		 *	\param key The ascii character representation of the key being pressed.
		 *	\return void
		 *	\exception GameError A GameError will be generated if the given key is not supported
		 *	by the game engine.
		 */
		virtual void keyPressed(char &key);
		/*!
		 *	\brief A function which simulates the described key being released.
		 *	\details A function which informs render manager of a key being released by giving it
		 *	the key's ascii value.
		 *
		 *	\param key The ascii character representation of the key being released.
		 *	\return void
		 *	\exception GameError A GameError will be generated if the given key is not supported
		 *	by the game engine.
		 */
		virtual void keyReleased(char &key);
		/*!
		 *	\brief A function which simulates a mouse button being clicked at the given location.
		 *	\details A function which simulates a mouse button being pressed at the absolute and
		 *	relative positions given.  This function passes the values given to it to the render
		 *	manager.
		 *
		 *	\param button The button on the mouse which was pressed.
		 *	\param abs_vals The absolute coordinates for the mouse.
		 *	\param rel_vals The relative coordinates for the mouse.
		 *	\return void
		 *	\exception GameError The action caused by the simulated mouse events does not exist.
		 */
		virtual void mButtonPressed(uint8 button, std::vector<int> &abs_vals, std::string<int> &rel_vals);
		/*!
		 *	\brief A function which simulates a mouse button being released at the given location.
		 *	\details A function which simulates a mouse button being released at the absolute and
		 *	relative positions given.  This function passes the values given to it to the render
		 *	manager.
		 *
		 *	\param button The button on the mouse which was released.
		 *	\param abs_vals The absolute coordinates for the mouse.
		 *	\param rel_vals The relative coordinates for the mouse.
		 *	\return void
		 *	\exception GameError The action caused by the simulated mouse events does not exist.
		 */
		virtual void mButtonReleased(uint8 button, std::vector<int> &abs_vals, std::string<int> &rel_vals);
		/*!
		 *	\brief A function which simulates the mouse's movements.
		 *	\details A function which simulates the movement of a computer mouse.  It passes
		 *	the given position values onto the render manager.
		 *
		 *	\param button The button on the mouse which was released.
		 *	\param abs_vals The absolute coordinates for the mouse.
		 *	\param rel_vals The relative coordinates for the mouse.
		 *	\return void
		 *	\exception GameError The action caused by the simulated mouse events does not exist.
		 */
		virtual void mouseMoved(std::vector<int> &abs_vals, std::string<int> &rel_vals);
		
		/*********************************************//*****************
		 *		Listener Message Passing Routines
		 ********************************************//*****************/
		
		// Audio Listener
		/*!
		 *	\brief A function which checks whether the audio should still be playing or not.
		 *	\details A function which asks the audio manager to check if the current audio
		 *	has ended or not if it is playing.
		 *
		 *	\param timestep The current timestep in the render process.
		 *	\return void
		 */
		virtual void updateAudio(float timestep);
		// Input Listener
		/*!
		 *	\brief A function which polls all inputs for changes in their state.
		 *	\details A function which will ask each input to process a change in state if
		 *	an event occurred.
		 *
		 *	\param timestep The current timestep in the render process.
		 *	\return void
		 */
		virtual void pollInputs(float timestep);
		
		// Initialization of game
		virtual void startEngine();
};

#endif
