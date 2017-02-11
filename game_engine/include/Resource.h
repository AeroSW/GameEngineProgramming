/*
 * Resource.h
 *
 *  Created on: Feb 2, 2017
 *      Author: uge
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <vector>
#include <string>

class level;

class resource{
	private:
		std::vector<level*> levels; // Need to treat is as 1-based.
		uint32 num_levels; // Number of total levels in game.
		uint32 curr_level; // The current level's index.
		uint32 num_finished_levels; // Number of levels currently finished.

	public:
		resource(); // Generates resource object with no levels.
		resource(uint32 num_levels); // Generated resource object with specified number of levels.
		resource(std::string xml_filename); // Builds resource object based on xml file.
		resource(const std::vector<level*> &pre_gen); // Builds resource with pre-generated levels.
		resource(const resource &res); // Copy constructor
		virtual ~resource();

		void restart(); // Needs to return information for the first level
		void replay(uint32 index); // Replay a past level.
		std::string get_curr_level_name();
		std::string get_level_name(uint32 index); // Passed as 1-based.
		uint32 get_num_finished(); // Retrieve the number of levels finished.
		uint32 get_tot_num_levels(); // How many levels exist in this game.
		uint32 get_curr_level_num(); // Returns 1-based.
		bool mod_level(level* l, uint32 index); // Modifies level index to be l. *l is lower case L*
		bool append_level(level* l); // Adds l to the end of the levels.
		bool insert_level(level* l, uint32 index); // Inserts l into index in levels.
};


#endif /* RESOURCE_H_ */
