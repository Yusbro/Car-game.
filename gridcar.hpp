#include <raylib.h>
#include <vector>
#include "mono.hpp"
namespace Game{

	struct GridChunk{
		std::vector<Vector3> car_positions;
		Vector3 position;
	};

	class GridCar : Mono{
		private:
			std::vector<GridChunk> grid;
			Vector3 start_position;
			float chunk_length;//the length of a chunk
			int grid_count;//the total number of chunks in a grid!
			Model model;
			
			std::vector<float> shuffled_numbers();
			void add_cars(GridChunk& chunk);
			

		public:
			GridCar();
			~GridCar();
			void update();
			void draw(Shader shader);
	};
}
