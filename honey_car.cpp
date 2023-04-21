
#include "honey_car.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include "raygui.h"
#include <map>
#include <string>

namespace Game{
	HoneyCar::HoneyCar(){
		for(int i=0;i<6;i++){
			HoneyCarChunk temp_car;
			temp_car.timer = 0.0;
			HoneyCar::cars.push_back(temp_car);
		}

		//loadinhg the asset stuff
		HoneyCar::model = LoadModel("asset/mobieus_car.obj");
	}
	HoneyCar::~HoneyCar(){
		HoneyCar::cars.clear();
		UnloadModel(HoneyCar::model);
	}
	
	void HoneyCar::update(){		
		//just for moving!!. and is working fine!
		for(auto &chunk : HoneyCar::cars){
			int index = 0;
			for(Vector3 &pos : chunk.position){
				pos.z -= chunk.speed[index]*GetFrameTime();
				index++;
			}
		}
		
		//just for deleting the stuff!!. Working good too!!
		for(auto &chunk : HoneyCar::cars){
			int index = 0;
			for(Vector3 &pos : chunk.position){
				if(pos.z < HoneyCar::destroy_point){
					chunk.position.erase(std::next(chunk.position.begin(), index));
					chunk.speed.erase(std::next(chunk.speed.begin(), index));
				}
				index++;
			}
		}
		
		//spawning new stuff!!!
		int _index = 0;
		for(auto &chunk : HoneyCar::cars){
			chunk.timer -= 0.01f;
			if(chunk.timer<0){
				float timer = ((float)GetRandomValue(50,100)/100) * 1.0;
				float x_pos = ((float)(_index)*HoneyCar::lane_padding) - HoneyCar::center_offset;
				Vector3 position = (Vector3){x_pos, 0, HoneyCar::spawn_point};				
				float speed = (_index < 3)? HoneyCar::left_speed : HoneyCar::right_speed;//GetRandomValue(3,5);
				chunk.timer = timer;
				chunk.position.push_back(position);
				chunk.speed.push_back(speed);
			}
			_index++;
		}
	}

	void HoneyCar::draw(Shader shader){
		Color color = {90, 188, 216, 255};
		HoneyCar::model.materials[0].shader = shader;
		for(auto chunk : HoneyCar::cars){
			for(Vector3 pos:chunk.position){
				DrawModelEx(HoneyCar::model, pos, (Vector3){0,1,0}, 90, (Vector3){0.2, 0.2, 0.2}, RED);
			}
		}
	}

	void HoneyCar::debug(std::unordered_map<std::string, Vector3> data){
		//put the new stuff here!!!
		HoneyCar::lane_padding = data["lane_padding"].x;
		HoneyCar::center_offset = data["center_offset"].x;
		HoneyCar::spawn_point = data["spawn_point"].x;
		HoneyCar::destroy_point = data["destroy_point"].x;
		HoneyCar::left_speed = data["left_speed"].x;
		HoneyCar::right_speed = data["right_speed"].x;
	}
}
