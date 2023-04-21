#pragma once
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "mono.hpp"

namespace Game{
	struct HoneyCarChunk{
		std::vector<Vector3> position;
		std::vector<float> speed;
		float timer;
	};

	class HoneyCar : public Mono{
		private:
			
			Model model;
			Texture texture;
			
			//for debugging stuff!!!
			float center_offset = 0;
			float lane_padding=0;
			float spawn_point = 0;
			float destroy_point = -1;

			float left_speed = 0;
			float right_speed = 0;
			
		public:
			std::vector<HoneyCarChunk> cars;	
			HoneyCar();
			~HoneyCar();
			void update();
			void draw(Shader shader);
			void debug(std::unordered_map<std::string, Vector3> data);
	};
}
