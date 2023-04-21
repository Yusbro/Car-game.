#include <raylib.h>
#include "rlgl.h"
#include "player.hpp"
#include "raygui.h"
#include "raymath.h"
#include <math.h>
#include <algorithm>
#include <iostream>


namespace Game{
	Player::Player(){
		Player::position = (Vector3){0,0,0};
		Player::rotation = (Vector3){0, -90, 0};
		
		//setting the speed and stuff!!
		Player::max_speed = 6;
		Player::normalized_speed = 0;
		Player::normalized_accelration = 5;


		//loading the assets!!
		Player::model = LoadModel("asset/mobieus_car.obj");
		Player::texture = LoadTexture("asset/player_car.png");

		//setting the camera!!!
		Player::camera.fovy = 30.0f;
		Player::camera.position = {0, 2, -8};
		Player::camera.target = {0, 0, 0};
		Player::camera.projection = CAMERA_PERSPECTIVE;
		Player::camera.up = {0, 1, 0};
	}
	Player::~Player(){
		UnloadModel(Player::model);
		UnloadTexture(Player::texture);
	}
	void Player::draw(Shader shader){
		Color color = {116, 204, 244, 255};
		Player::model.materials[0].shader = shader;
		DrawModelEx(Player::model, Player::position, {0, 1, 0}, 90, {0.2, 0.2, 0.2}, color);
		
		//for the debugging stuff!!!
		BoundingBox box = GetModelBoundingBox(Player::model);
	}

	void Player::update(){//the update function!!!---- pretty important!!!
		float direction = Player::control();
		Player::move(direction);//moving the player!!!
		Player::tilt(direction);//tilting the player!!!;
	}

	void Player::debug(std::unordered_map<std::string, Vector3> data){
		Player::max_speed = data["player_speed"].x;
		Player::position.z = data["player_position_z"].x;
	}

	Camera Player::get_camera(){
		return Player::camera;
	}

	//-------------------------private functions!!!
	
	float Player::control(){
		float direction = 0;
		if(IsKeyDown(KEY_A)) direction = 1;
		if(IsKeyDown(KEY_D)) direction = -1;
		return direction;	
	}

	void Player::move(float direction){
			
		if(direction != 0){
			Player::normalized_speed += Player::normalized_accelration * GetFrameTime() * direction;
			Player::normalized_speed = (abs(Player::normalized_speed) > 1.0f) ? direction: Player::normalized_speed;
		}
		if(direction == 0 && abs(Player::normalized_speed) > 0.01){
			Player::normalized_speed += (-Player::normalized_speed * GetFrameTime() * 13.0);
			if(abs(Player::normalized_speed) < 0.01) Player::normalized_speed = 0;
		}
		Player::position.x += (Player::normalized_speed * Player::max_speed);

		//moving da camera!!
		Player::camera.position.x = Player::position.x;
		Player::camera.target.x = Player::position.x;
	}

	void Player::tilt(float direction){
		
		if(direction != 0){
			Player::tilt_angle += Player::tilt_speed * GetFrameTime() * direction;
			Player::tilt_angle = (abs(Player::tilt_angle) > 1.0f ) ? direction : Player::tilt_angle;
		}
		if(direction == 0 && abs(Player::tilt_angle) > 0.01){
			Player::tilt_angle += (-Player::tilt_angle * GetFrameTime() * 13.0);
			if(abs(Player::tilt_angle) < 0.01) Player::tilt_angle = 0;
		}
		Player::rotation.x = DEG2RAD * (Player::tilt_angle * Player::max_tilt_angle);	
		Matrix mat = MatrixIdentity();
		Player::model.transform = MatrixMultiply(mat, MatrixRotateX(Player::rotation.x));
	}

	void Player::collide(std::vector<HoneyCarChunk> &chunk){
		BoundingBox box = GetModelBoundingBox(Player::model);

		for(auto i : chunk){
			for(auto position : i.position){
				BoundingBox player = {
					{
						Player::position.x - box.min.x,
						Player::position.y - box.min.y,
						Player::position.z - box.min.z
					},{
						Player::position.x - box.max.x,
						Player::position.y - box.max.y,
						Player::position.z - box.max.z
					}
				};

				BoundingBox enemy = {
					{
						position.x - box.min.x,
						position.y - box.min.y,
						position.z - box.min.z
					},{
						position.x - box.max.x,
						position.y - box.max.y,
						position.z - box.max.z
					}
				};

				if(CheckCollisionBoxes(player, enemy)){
					Player::is_hit = true;
				}
			}
		}
	}

	bool Player::player_hit(){
		return Player::is_hit;
	}
}
