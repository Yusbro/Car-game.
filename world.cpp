#include "world.hpp"
#include <vector>
#include <iostream>

namespace Game{	
	App::App(){
		App::width = 800;
		App::height = 600;
		
		App::render_width = 800;
		App::render_height = 600;
		InitWindow(App::width, App::height, "Fast bear prototype!!");
		SetTargetFPS(60);
		
		App::world.push_back(new Player());
		App::world.push_back(new HoneyCar());
		App::world.push_back(new Platform());

		App::debug = new Debug();
	}

	App::~App(){
		for(auto &i: App::world){
			delete i;
		}
		delete App::debug;
		CloseWindow();
	}
	

	void App::run(){
		RenderTexture2D depth_tex = LoadRenderTexture(App::render_width, App::render_height);
		RenderTexture2D outline_tex = LoadRenderTexture(App::render_width, App::render_height);
		RenderTexture2D blur_tex = LoadRenderTexture(App::render_width, App::render_height);
		RenderTexture2D light_tex = LoadRenderTexture(App::render_width, App::render_height);
		RenderTexture2D final_tex = LoadRenderTexture(App::render_width, App::render_height);
			

		Rectangle src = {0.0, 0.0, App::width, -App::height};
		Rectangle dest = {1.33, 1.33, App::render_width, App::render_height };	

		auto config_data = App::debug->collected_data();
		

		//all the shaders!!!
		Shader depth = LoadShader("shader/main.vs", "shader/main.fs");//for the depth texture
		
		Shader blur = LoadShader(0, "shader/blur.fs");
		int blur_screen_size = GetShaderLocation(blur, "screen_size");	
		int blur_size = GetShaderLocation(blur, "size");
		std::cout<<"BOOO!!!! "<<blur_size<<std::endl;


		Shader blur_sub = LoadShader(0, "shader/blur_sub.fs");
		int blur_sub_text = GetShaderLocation(blur_sub, "tex");
			

		Shader light = LoadShader("shader/light.vs", "shader/light.fs");


		Shader outline = LoadShader(0, "shader/outline.fs");
		int outline_tex_loc = GetShaderLocation(outline, "tex");
		
		Shader combine = LoadShader(0, "shader/combine.fs");
		int combine_tex_loc = GetShaderLocation(combine, "blur_tex");

		//updating the code and stuff!!!
		while(!WindowShouldClose()){
			//debug stuff!!!	

			for(auto &i : App::world){
				i->debug(config_data);
				i->update();
			}

			App::score += 0.5;
				
			Player& player = dynamic_cast<Player&>(*App::world[0]);	
			HoneyCar& honey = dynamic_cast<HoneyCar&>(*App::world[1]);

			player.collide(honey.cars);

			//draws a 3D screen with a shader!!!
			#define SHADE(TEX, SHADER)\
			BeginTextureMode(TEX);\
				ClearBackground(RAYWHITE);\
				BeginMode3D(player.get_camera());\
					for(auto i: App::world){\
						i->draw(SHADER);\
					}\
				EndMode3D();\
			EndTextureMode();
			
			#define TEX_SHADE(INPUT, OUTPUT, SHADE, ...)\
			BeginTextureMode(OUTPUT);\
				BeginShaderMode(SHADE);\
					ClearBackground(RAYWHITE);\
					__VA_ARGS__;\
					DrawTexturePro(INPUT, src, dest, {0,0}, 0, WHITE);\
				EndShaderMode();\
			EndTextureMode();
			

			//for depth stuff!!!
			SHADE(depth_tex, depth);//first drawing the depth shader
			
			//doing the blur stuff!!!
			float blur_intensity = 2.0; 
			Vector2 screen_size = {App::render_width, App::render_height};
			
			TEX_SHADE(depth_tex.texture, outline_tex, outline);
			
			TEX_SHADE(outline_tex.texture, blur_tex, blur, 
				SetShaderValue(blur, blur_screen_size, &screen_size, SHADER_UNIFORM_VEC2),
				SetShaderValue(blur, blur_size, &blur_intensity, SHADER_UNIFORM_FLOAT));

			SHADE(light_tex, light);
			
			TEX_SHADE(light_tex.texture, final_tex, combine, 
				SetShaderValueTexture(combine, combine_tex_loc, blur_tex.texture));

			BeginDrawing();
				ClearBackground(RAYWHITE);	
				
				if(!player.player_hit()){
					DrawTexturePro(final_tex.texture, src, dest, {0,0}, 0, WHITE);
				}
				DrawText(TextFormat("%i", (int)App::score), 750, 50, 30, GREEN);				App::debug->update();
				//config_data = App::debug->collected_data();
			EndDrawing();
		}
		UnloadShader(depth);
		UnloadShader(light);
		UnloadShader(outline);
		UnloadShader(blur);
		UnloadShader(blur_sub);
		UnloadShader(combine);
	}
}
