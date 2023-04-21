#include <raylib.h>
#include <vector>

namespace Game{		
	struct car_chunk{
		std::vector<int> state;
		float offset;
	};

	class Car{
		private:
			int lanes, rows;
			std::vector<car_chunk> cars;
			
			std::vector<int> generate_state(std::vector<int>& top_chunk);
			std::vector<int> top_chunk_state();
			
			float timer;
		public:
			Car(int lane, int row);
			~Car();
			void draw();
			void update();
	};

}
