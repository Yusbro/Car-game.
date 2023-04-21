
#include "gridcar.hpp"
#include <iostream>
namespace Game{
	GridCar::GridCar(){
		GridCar::start_position = {0, 0, 100};
		GridCar::grid_count = 10;
		GridCar::chunk_length = 30;
		
		//putting car inside each grid!!!
		for(std::size_t i = 0; i<GridCar::grid_count; i++){
			GridChunk temp_chunk;
			temp_chunk.position = {0,0,i*chunk_length};
			GridCar::add_cars(temp_chunk);
			GridCar::grid.push_back(temp_chunk);
		}

		//loading some model!!
		GridCar::model = LoadModel("asset/mobieus_car.obj");
	}

	GridCar::~GridCar(){
		for(auto& i : GridCar::grid){
			i.car_positions.clear();
		}
		GridCar::grid.clear();
		UnloadModel(GridCar::model);
	}
	
	void GridCar::update(){
		float end_point = 0;//((GridCar::grid_count+1) * 0) - GridCar::start_position.z;
		for(auto &chunk : GridCar::grid){
			chunk.position.z -= 10 * GetFrameTime();
		
			if(chunk.position.z < end_point){
				//chunk.position.z = GridCar::start_position.z;
				//GridCar::add_cars(chunk);
			}	
		}
	}

	void GridCar::draw(Shader shader){
		for(auto chunk : GridCar::grid){
			Vector3 offset = chunk.position;
			for(auto pos : chunk.car_positions){
				Vector3 final_pos = {pos.x + offset.x, pos.y + offset.y, pos.z + offset.z};
				DrawModelEx(GridCar::model, final_pos, (Vector3){0, 1, 0}, -90, (Vector3){0.3,0.3, 0.3}, WHITE);
			}
		}
	}


	//-------------private functions!!!
	
	std::vector<float> GridCar::shuffled_numbers(){
		std::vector<float> ret = {0,1,2,3,4,5};
		for(int i=0; i< 5; i++){
			int a = GetRandomValue(0,5);
			int b = GetRandomValue(0,5);
			
			int temp = ret[a];
			ret[a] = ret[b];
			ret[b] = temp;
		}
		return ret;
	}

	void GridCar::add_cars(GridChunk &chunk){
		std::vector<float> offsets = GridCar::shuffled_numbers();
		int index = 0;	
		for(float &f : offsets){
			float z_pos = (f/6) * GridCar::chunk_length;	
			chunk.car_positions.push_back({(float)index*2, 0, z_pos});
			index++;
		}	
	}
}

