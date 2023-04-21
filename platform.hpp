#include <raylib.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "mono.hpp"
namespace Game{
	class Platform : public Mono{
		private:
			std::size_t platform_count;
			Texture platform_texture;
			Model model;
			std::vector<float> platform_offset;
			
			//for debugging
			float model_offset;
			std::size_t chunk_count;
			float disapper_limit;
		public:
			Platform();
			~Platform();
			void draw(Shader shader);
			void update();
			void debug(std::unordered_map<std::string, Vector3> data);
	};
}
