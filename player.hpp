#include "honey_car.hpp"
#include <raylib.h>
#include <unordered_map>
#include <string>
#include "mono.hpp"
namespace Game{	
	class Player : public Mono{
		private:

			//for moving the stuff!!!
			float normalized_speed;//just a value from 0 to 1!!!, which is multiplied to max_speed. to get a value from 0 to max_speed 
			float normalized_accelration;// the amount of value that gets incremented to normalized_speed*deltaTime
			float max_speed;//the maximum speed the player can move
			
			//for the tilt stuff!!
			float tilt_angle = 0;//just a value from 0 to 1.
			float tilt_speed = 6;//the rate of change of tilt_angle
			float max_tilt_angle=10;//the max angle you can tilt;		

			Model model;
			Texture texture;
			float scale;
			
			Camera camera;

			//some private functions!!
			float control();
			void move(float direction);
			void tilt(float direction);
			bool is_hit = false;

		public:
			Vector3 position;
			Vector3 rotation;

			Player();
			~Player();
			
			void draw(Shader shader);
			void update();
			void debug(std::unordered_map<std::string, Vector3> data);

			void collide(std::vector<HoneyCarChunk> &chunk);
			Camera get_camera();
			bool player_hit();
	};
}
