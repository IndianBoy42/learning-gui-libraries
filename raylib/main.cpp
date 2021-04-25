#include <algorithm>
#include <random>

#include "imgui_impl_opengl3.h"
#include "imgui_impl_raylib.h"
#include "raylib-cpp.hpp"

void drawing(auto fn) {
	BeginDrawing();
	fn();
	EndDrawing();
}

int main(void) {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	std::string windowTitle = "raylib [core] example - keyboard input";
	raylib::Window window(screenWidth, screenHeight, windowTitle);

	Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};
	static constexpr size_t N = 1000;
	auto balls = ([&] {
		std::vector<raylib::Vector2> balls;
		balls.reserve(N);
		std::random_device rnd_device;
		std::mt19937 eng{rnd_device()};	 // Generates random integers
		std::uniform_real_distribution<float> x{0., screenWidth};
		std::uniform_real_distribution<float> y{0., screenHeight};
		std::generate_n(std::back_inserter(balls), N, [&] { return Vector2{x(eng), y(eng)}; });
		return balls;
	})();

	float inputColor[3];
	raylib::Color ballColor{SKYBLUE};
	raylib::Color bgColor{RAYWHITE};

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplOpenGL3_Init();
	ImGui_ImplRaylib_Init();
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.ShouldClose())  // Detect window close button or ESC key
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplRaylib_NewFrame();
		ImGui::NewFrame();
		ImGui_ImplRaylib_ProcessEvent();

		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
		if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
		if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
		if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------

		drawing([&] {
			bgColor.ClearBackground();

			ImGui::Begin("Sample window");	// begin window
			// Background color edit
			if (ImGui::ColorEdit3("Background color", inputColor)) {
				// this code gets called if color value changes, so
				// the background color is upgraded automatically!
				bgColor.r = static_cast<char>(inputColor[0] * 255.f);
				bgColor.g = static_cast<char>(inputColor[1] * 255.f);
				bgColor.b = static_cast<char>(inputColor[2] * 255.f);
			}

			// Window title text edit
			ImGui::InputText("Window title", windowTitle.data(), 255);

			if (ImGui::Button("Update window title")) {
				// this code gets if user clicks on the button
				// yes, you could have written if(ImGui::InputText(...))
				// but I do this to show how buttons work :)
				window.SetTitle(windowTitle);
			}
			ImGui::End();  // end window

			DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

			DrawCircleV(ballPosition, 50, MAROON);

			std::random_device rnd_device;
			std::mt19937 eng{rnd_device()};	 // Generates random integers
			std::uniform_real_distribution<float> dx{-2, 2};
			for (auto&& ball : balls) {
				ball.DrawCircle(10, ballColor);
				ball += {dx(eng), dx(eng)};
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		});

		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();	// Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
