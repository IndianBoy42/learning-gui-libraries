#include <algorithm>
#include <random>

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

	raylib::Window window(screenWidth, screenHeight, "raylib [core] example - keyboard input");

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

	raylib::Color ballColor{SKYBLUE};
	raylib::Color bgColor{RAYWHITE};

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.ShouldClose())  // Detect window close button or ESC key
	{
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

			DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

			DrawCircleV(ballPosition, 50, MAROON);

			std::random_device rnd_device;
			std::mt19937 eng{rnd_device()};	 // Generates random integers
			std::uniform_real_distribution<float> dx{-2, 2};
			for (auto&& ball : balls) {
				ball.DrawCircle(10, ballColor);
				ball += {dx(eng), dx(eng)};
			}
		});

		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();	// Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
