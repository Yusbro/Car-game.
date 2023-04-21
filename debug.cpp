#include "debug.hpp"
#include "raygui.h"
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "json.hpp"


#define RECT(X,Y,W,H)\
	(Rectangle){(X), (Y), (W), (H)}


#define SLIDE(Y_POS, NAME, VER)\
	GuiSlider((Rectangle){100, (Y_POS), 100, 10},\
	(NAME),\
	TextFormat("%f", (VER).x),\
	(VER).x,\
	(VER).y, (VER).z);

using json = nlohmann::json; 


namespace Game{

	Debug::Debug(){
		//making da stuff!!!
		Debug::data.insert({"PLAYER", {99, 99, 99}});
		Debug::data.insert({"player_speed", {0, 0 ,1}});//player
		Debug::data.insert({"player_position_z", {0, -100,0}});

		Debug::data.insert({"PLATFORM", {99,99,99}});
		Debug::data.insert({"model_offset", {0, 0, 200}});//platform
		Debug::data.insert({"chunk_count", {0,0,40}});
		Debug::data.insert({"disapper_limit", {0, -2,2}});

		Debug::data.insert({"HONEY_CAR", {99,99,99}});
		Debug::data.insert({"lane_padding", {0,-5,5}});//honey_car;
		Debug::data.insert({"center_offset", {0,-5,5}});
		Debug::data.insert({"spawn_point", {0,0,200}});
		Debug::data.insert({"destroy_point", {0,-10,0}});
		Debug::data.insert({"left_speed", {0,0,50}});	
		Debug::data.insert({"right_speed", {0,0,50}});

		std::ifstream infile("test.json");
		if(infile.good()){
			Debug::load();
		}
		else{
			Debug::save();
		}
	}

	Debug::~Debug(){
		Debug::data.clear();
	}

	void Debug::update(){

		Debug::edit_toggle_option = GuiToggleGroup(RECT(10, 10, 60, 20), "close;Player;Platform;Honey_car", Debug::edit_toggle_option);
		
		switch(Debug::edit_toggle_option){
			case 0:
				break;
			case 1://the player!!!
				Debug::data["player_speed"].x = SLIDE(110, "speed", Debug::data["player_speed"]);
				Debug::data["player_position_z"].x = SLIDE(130, "position", Debug::data["player_position_z"]);	
				break;
					
			case 2://for the platform!!!
				Debug::data["model_offset"].x = SLIDE(110, "offset", Debug::data["model_offset"]);
				Debug::data["chunk_count"].x = SLIDE(130, "count", Debug::data["chunk_count"]);
				Debug::data["disapper_limit"].x = SLIDE(150, "destroy point", Debug::data["disapper_limit"]);	
				break;

			case 3://for the honey_car!!!
				Debug::data["lane_padding"].x = SLIDE(110, "lane padding", Debug::data["lane_padding"]);
				Debug::data["center_offset"].x = SLIDE(130, "center offset", Debug::data["center_offset"]);
				Debug::data["spawn_point"].x = SLIDE(150, "spawn point", Debug::data["spawn_point"]);
				Debug::data["destroy_point"].x = SLIDE(170, "destroy point", Debug::data["destroy_point"]);
				Debug::data["left_speed"].x = SLIDE(200, "left_speed", Debug::data["left_speed"]);
				Debug::data["right_speed"].x = SLIDE(220, "right_speed", Debug::data["right_speed"]);
				break;
			defualt:
				break;
		}

		//for saving da stuff!!
		if(GuiButton((Rectangle){700,500,50,50}, "Save")){
			Debug::save();
		}
	}


	//saving the config!!!
	void Debug::save(){	
		//EXPERIMENTAL
		//saving a json file!!!
		json j;
		for(auto &i : Debug::data){
			std::string name = i.first;
			j[name] = i.second.x;
		}

		std::ofstream output("test.json");
		output << j.dump(4);
	}
	
	//loading the config!!!
	void Debug::load(){
		//loading from a json file!!
		std::ifstream input("test.json");
		json j;
		input >> j;

		for(auto &i : Debug::data){
			std::string name = i.first;
			i.second.x = j[name];
		}
	}

	std::unordered_map<std::string, Vector3> Debug::collected_data(){
		return data;
	}
}
