#include "car.hpp"
#include <raylib.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <math.h>

namespace Game{
	Car::Car(int lane, int row):lanes(lane), rows(row){
		for(int r=0;r<row;r++){
			car_chunk local_chunk;
			for(int l=0;l<lane;l++){
				local_chunk.state.push_back(0);
			}
			local_chunk.offset=((float)r/(float)row);
			
			cars.push_back(local_chunk);
		}
		Car::timer = 0;
	}	
	Car::~Car(){
		std::for_each(
				Car::cars.begin(),
				Car::cars.end(),
				[&](car_chunk& chunk){
					chunk.state.clear();
				});
		Car::cars.clear();
	}

	void Car::draw(){
		//looping thru every function!!!
		for(auto chunk : Car::cars){
			int index = 0;
			std::for_each(//iterating thru the car
					chunk.state.begin(),
					chunk.state.end(),
					[&](int& state){
						float y = chunk.offset*600;//the y position of the car
						float x = 245 + index * 64;//the x position of the car
						if(state==1) DrawCircle(x,y,20, RED);
						index++;
					});
		}
	}
	
	void Car::update(){
		for(auto &chunk : Car::cars){
			chunk.offset += 0.02;
			if(chunk.offset > 1.0f){
				chunk.offset -= 1.0f;
				
				float sin_val = std::sin(Car::timer);
				int index = 0;
				std::for_each(
						chunk.state.begin(), 
						std::next(chunk.state.begin(),3), 
						[sin_val, &index](int& i){
							int sin_index = (int)(((sin_val+1)*0.5f)*3);	
							i = (index==sin_index) ?  0 : GetRandomValue(0,1);
							index++;
						});
				std::for_each(
						std::next(chunk.state.begin(),3), 
						chunk.state.end(), 
						[sin_val, &index](int& i){
							int sin_index = (int)(((sin_val+1)*0.5f)*3) + 3;	
							i = (index==sin_index) ? 0 : GetRandomValue(0,1);
							index++;
						});	
			}
		}
		Car::timer += 0.1;
	}
	
	std::vector<int> Car::generate_state(std::vector<int>& top_chunk){
		std::vector<int> ret(6,0);
		//for the left part!!!
		auto l_value = 3 - std::accumulate(top_chunk.begin(), std::next(top_chunk.begin(),2),0);
		auto r_value = 3 - std::accumulate(std::next(top_chunk.begin(),3), top_chunk.end(), 0);
		 
		//for the left
		for(int i=0;i<l_value;i++){
			int index = GetRandomValue(0,2);
			ret[index] = 1;
		}

		for(int i=0;i<r_value;i++){
			int index = GetRandomValue(3,5);
			std::cout<<"righty stuff!!! "<<index<<"\n";
			ret[index] = 1;
		}
		return ret;
	}
	
	//for getting the top chunk data!!!
	std::vector<int> Car::top_chunk_state(){
		float min_val = 9;int index = -1;
		for(auto chunk : Car::cars){
			if(chunk.offset < min_val) min_val = chunk.offset;
			index++;
		}
		std::vector<int> ret(Car::cars[index].state);	// Car::cars[index].state;
		return ret;
	}
}
