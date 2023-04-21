#include <raylib.h>
#include "platform.hpp"
#include "player.hpp"
#include "honey_car.hpp"
#include "debug.hpp"
#include "gridcar.hpp"

namespace Game{ 
	class App{
		std::vector<Mono*> world;
		Debug* debug;
		
		float width, height;
		float render_width, render_height;

		float score = 0;
		public:
			App();
			~App();
			void run();
	};
}
