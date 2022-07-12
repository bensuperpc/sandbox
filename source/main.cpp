#include <iostream>  // std::cout, std::endl
#include <vector>  // std::vector

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "sandbox.hpp"

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#  if __has_include("omp.h")
#    include <omp.h>
#  else
#    if _MSC_VER && !__INTEL_COMPILER
#      pragma message("Can t find omp.h, please install OpenMP")
#    else
#      warning Can t find omp.h, please install OpenMP.
#    endif
#  endif
#endif

auto main() -> int
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;
  const uint32_t targetFPS = 120;
  const uint32_t gridUpdatePerSecond = 10;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

  raylib::Window window(screenWidth, screenHeight, "raylib-cpp game of life");

  raylib::Image gridImage(screenWidth, screenHeight, RAYWHITE);

  Color* pixels;

  raylib::Texture gridTexture(gridImage);

  SetTargetFPS(targetFPS);

  auto sandbox = benlib::Gol(screenWidth, screenHeight);

  uint64_t framesCounter = 0;

  bool paused = false;
  bool displayHelp = true;

  while (!WindowShouldClose()) {
    framesCounter++;

    Vector2 mousePosition = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      sandbox.Circle(mousePosition.x, mousePosition.y, 20, 1);
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      sandbox.Circle(mousePosition.x, mousePosition.y, 20, 0);
    }

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_P)) {
      if (paused) {
        paused = false;
      } else {
        paused = true;
      }
    }

    if (IsKeyPressed(KEY_U)) {
      const std::string filename = "sandbox.txt";
      sandbox.Serialize(filename);
    }

    if (IsKeyPressed(KEY_L)) {
      const std::string filename = "sandbox.txt";
      sandbox.Deserialize(filename);
    }

    if (IsKeyPressed(KEY_H)) {
      displayHelp = !displayHelp;
    }

    if (framesCounter % (targetFPS / gridUpdatePerSecond) == 0 && !paused) {
      sandbox.Update();
    }

    if (IsKeyPressed(KEY_C)) {
      sandbox.Reset();
    }

    if (IsKeyPressed(KEY_R)) {
      sandbox.RandomFill();
    }

    // Not need, all cells are override
    // gridImage.ColorTint(RAYWHITE);

#if defined(_OPENMP)
#  pragma omp parallel for collapse(2) schedule(auto)
#endif
    // Draw grid
    for (uint64_t x = 0; x < screenWidth; x++) {
      for (uint64_t y = 0; y < screenHeight; y++) {
        // If cell is alive
        if (sandbox.GetCell(x, y) == 0) {
          gridImage.DrawPixel(
              static_cast<int>(x), static_cast<int>(y), LIGHTGRAY);
        } else if (sandbox.GetCell(x, y) == 1) {
          gridImage.DrawPixel(static_cast<int>(x), static_cast<int>(y), BLACK);
        } else if (sandbox.GetCell(x, y) == 2) {
          gridImage.DrawPixel(static_cast<int>(x), static_cast<int>(y), YELLOW);
        } else if (sandbox.GetCell(x, y) == 3) {
          gridImage.DrawPixel(static_cast<int>(x), static_cast<int>(y), RED);
        } else if (sandbox.GetCell(x, y) == 4) {
          gridImage.DrawPixel(static_cast<int>(x), static_cast<int>(y), GREEN);
        } else if (sandbox.GetCell(x, y) == 5) {
          gridImage.DrawPixel(static_cast<int>(x), static_cast<int>(y), BLUE);
        } else if (sandbox.GetCell(x, y) == 6) {
          gridImage.DrawPixel(
              static_cast<int>(x), static_cast<int>(y), MAGENTA);
        } else if (sandbox.GetCell(x, y) == 7) {
          gridImage.DrawPixel(static_cast<int>(x), static_cast<int>(y), LIME);
        } else {
          gridImage.DrawPixel(static_cast<int>(x), static_cast<int>(y), WHITE);
        }
      }
    }

    pixels = gridImage.LoadColors();

    gridTexture.Update(pixels);
    UnloadImageColors(pixels);

    BeginDrawing();

    DrawTexture(gridTexture, 0, 0, WHITE);

    ClearBackground(RAYWHITE);

    // DrawTextureRec(gridTexture.texture, (Rectangle) { 0, 0,
    // (float)gridTexture.texture.width, (float)-gridTexture.texture.height },
    // (Vector2) { 0, 0 }, WHITE);

    if (displayHelp) {
      DrawRectangle(10, 10, 250, 113, Fade(SKYBLUE, 0.95f));
      DrawRectangleLines(10, 10, 250, 113, BLUE);

      DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
      DrawText("- D-Pad to move Offset", 40, 40, 10, DARKGRAY);
      DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
      DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
      DrawText("- B to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);

      DrawRectangle(10, 123, 250, 153, Fade(SKYBLUE, 0.95f));
      DrawRectangleLines(10, 123, 250, 153, BLUE);

      DrawText("Game of life controls:", 20, 133, 10, BLACK);
      DrawText("- R to random values", 40, 153, 10, DARKGRAY);
      DrawText("- C to clear game", 40, 173, 10, DARKGRAY);
      DrawText("- Space to pause", 40, 193, 10, DARKGRAY);
      DrawText("- ---------------", 40, 213, 10, DARKGRAY);
      DrawText("- H to display help", 40, 233, 10, DARKGRAY);
      DrawText("- U to Serialize, L to Deserialize", 40, 253, 10, DARKGRAY);
    }

    // display FPS
    DrawRectangle(screenWidth - 90, 10, 80, 20, Fade(SKYBLUE, 0.95f));
    DrawText(
        TextFormat("FPS: %02d", GetFPS()), screenWidth - 80, 15, 15, DARKGRAY);

    EndDrawing();
  }

  // CloseWindow();  // Close window and OpenGL context

  return 0;
}
