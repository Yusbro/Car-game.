#include "platform.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


namespace Game{
	
	Platform::Platform(){
		//loading all the texturd
		Platform::model = LoadModel("asset/road.obj");
		Platform::platform_texture = LoadTexture("asset/road.png");

		//for debugging
		Platform::model_offset = 15;
		Platform::chunk_count = 4;
		Platform::disapper_limit = -0.52;
	}

	Platform::~Platform(){
		UnloadTexture(Platform::platform_texture);
		UnloadModel(Platform::model);
	}

	void Platform::draw(Shader shader){
		Color color = {15, 94, 157, 255};		
		Platform::model.materials[0].shader = shader;
		std::for_each(
				Platform::platform_offset.begin(),
				Platform::platform_offset.end(),
				[&](const float& f){
					float z = (1-f + Platform::disapper_limit)*Platform::model_offset;
					Vector3 position = (Vector3){0.0, -0.3, z};
					//DrawModel(Platform::model, position, 1.0, WHITE);
					DrawModelEx(Platform::model, position, (Vector3){0,1,0}, 90.0f, (Vector3){1,1,1}, color);
				});	
	}
	

	//updating the stuff!!
	void Platform::update(){	
		std::for_each
				(Platform::platform_offset.begin(),
				Platform::platform_offset.end(),
				[&](float& f){
					f += 0.01;
					if(f > 1.0f) f -= 1.0f;
				});	
	}

	void Platform::debug(std::unordered_map<std::string, Vector3> data){
		Platform::model_offset = data["model_offset"].x;
		Platform::chunk_count = data["chunk_count"].x;
		//this code kinda adds new chunks. and erase the old chunks. when the chunk size has changed
		if(Platform::chunk_count != Platform::platform_offset.size()){
			Platform::platform_offset.clear();
			for(int i=0;i<Platform::chunk_count;i++){
				float offset = (float)i/(float)Platform::chunk_count;
				Platform::platform_offset.push_back(offset);
			}
		}
		Platform::disapper_limit = data["disapper_limit"].x;
	}

}
