#include <array>  // std::array
#include <iostream>  // std::cout, std::endl
#include <vector>  // std::vector

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "sandbox.hpp"
#include "water.hpp"

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

  // Colours to choose from
  constexpr std::array<Color, 23> colors = {
      RAYWHITE, YELLOW, GOLD,   ORANGE,     PINK,  RED,   MAROON,    GREEN,     LIME, DARKGREEN, SKYBLUE, BLUE,
      DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN, LIGHTGRAY, GRAY, DARKGRAY,  BLACK};

  // Define colorsRecs data (for every rectangle)
  Rectangle colorsRecs[colors.size()] = {0};

  for (int i = 0; i < colors.size(); i++) {
    colorsRecs[i].x = 10 + 30.0f * i + 2 * i;
    colorsRecs[i].y = 10;
    colorsRecs[i].width = 30;
    colorsRecs[i].height = 30;
  }

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

  raylib::Window window(screenWidth, screenHeight, "raylib-cpp game of life");

  SetTargetFPS(targetFPS);

  raylib::Image gridImage(screenWidth, screenHeight, RAYWHITE);

  Color* pixels;

  raylib::Texture gridTexture(gridImage);

  float brushSize = 20.0f;

  uint64_t selectedColor = 1;
  uint64_t colorMouseHover = -1;

  auto sandbox = benlib::Gol(screenWidth, screenHeight);

  uint64_t framesCounter = 0;

  bool paused = false;

  while (!WindowShouldClose()) {
    framesCounter++;

    Vector2 mousePosition = GetMousePosition();

    if (mousePosition.y > 50) {
      if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        sandbox.Circle(mousePosition.x, mousePosition.y, static_cast<uint64_t>(brushSize), selectedColor);
      }

      if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        sandbox.Circle(mousePosition.x, mousePosition.y, static_cast<uint64_t>(brushSize), 0);
      }
    }

    for (int i = 0; i < colors.size(); i++) {
      if (CheckCollisionPointRec(mousePosition, colorsRecs[i])) {
        colorMouseHover = i;
        break;
      } else
        colorMouseHover = colors.size();
    }
    if ((colorMouseHover < colors.size()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      selectedColor = colorMouseHover;
    }

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_P)) {
      if (paused) {
        paused = false;
      } else {
        paused = true;
      }
    }

    if (IsKeyPressed(KEY_S)) {
      const std::string filename = "image.png";
      gridImage.FlipVertical();
      gridImage.Export(filename);
      gridImage.FlipVertical();
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

    brushSize += GetMouseWheelMove() * 5;
    if (brushSize < 2)
      brushSize = 2;
    if (brushSize > 70)
      brushSize = 70;

#if defined(_OPENMP)
#  pragma omp parallel for collapse(2) schedule(auto)
#endif
    // Update image
    for (uint64_t x = 0; x < screenWidth; x++) {
      for (uint64_t y = 0; y < screenHeight; y++) {
        gridImage.DrawPixel(static_cast<int>(x), static_cast<int>(y), colors[sandbox.GetCell(x, y).get_id()]);
      }
    }

    // Get pixels from image
    pixels = gridImage.LoadColors();

    // Update texture
    gridTexture.Update(pixels);
    gridImage.UnloadColors(pixels);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(gridTexture, 0, 0, WHITE);

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      DrawCircleLines((int)mousePosition.x, (int)mousePosition.y, brushSize, GRAY);
    } else {
      DrawCircle(GetMouseX(), GetMouseY(), brushSize, colors[selectedColor]);
    }

    DrawRectangle(0, 0, GetScreenWidth(), 50, RAYWHITE);
    DrawLine(0, 50, GetScreenWidth(), 50, LIGHTGRAY);

    for (int i = 0; i < colors.size(); i++)
      DrawRectangleRec(colorsRecs[i], colors[i]);
    DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);

    if (colorMouseHover < colors.size())
      DrawRectangleRec(colorsRecs[colorMouseHover], Fade(WHITE, 0.6f));

    DrawRectangleLinesEx((Rectangle) {colorsRecs[selectedColor].x - 2,
                                      colorsRecs[selectedColor].y - 2,
                                      colorsRecs[selectedColor].width + 4,
                                      colorsRecs[selectedColor].height + 4},
                         2,
                         BLACK);

    // display FPS
    DrawRectangle(screenWidth - 90, 10, 80, 20, Fade(SKYBLUE, 0.95f));
    DrawText(TextFormat("FPS: %02d", GetFPS()), screenWidth - 80, 15, 15, DARKGRAY);

    EndDrawing();
  }

  return 0;
}
