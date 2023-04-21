#pragma once
#include <string>
#include <unordered_map>
#include <raylib.h>

namespace Game{

	class Mono{
		
		public:
			virtual void update(){}
			virtual void draw(Shader shader){}
			virtual void debug(std::unordered_map<std::string, Vector3> data){}
	};
}


