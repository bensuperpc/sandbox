#include <array>    // std::array
#include <iostream> // std::cout, std::endl
#include <map>      // std::map
#include <memory>   // std::unique_ptr
#include <vector>   // std::vector

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "sandbox.hpp"

auto main() -> int {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // const int internalWidth = 1280;
    // const int internalHeight = 720;

    const uint32_t targetFPS = 60;

    const uint32_t gridUpdatePerSecond = 5;
    const uint32_t ImageUpdatePerSecond = 30;

    // Colours to choose from
    constexpr std::array<Color, 23> colors = {RAYWHITE, YELLOW, GOLD,   ORANGE,     PINK,  RED,   MAROON,    GREEN,     LIME, DARKGREEN, SKYBLUE, BLUE,
                                              DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN, LIGHTGRAY, GRAY, DARKGRAY,  BLACK};

    // Map colors to Cell
    std::map<Cell, Color> colorMap = {{Cell::air, RAYWHITE}, {Cell::fire, YELLOW}, {Cell::glass, GOLD},  {Cell::plant, ORANGE},
                                      {Cell::sand, PINK},    {Cell::steam, RED},   {Cell::water, MAROON}};

    // Define colorsRecs data (for every rectangle)
    Rectangle colorsRecs[colors.size()] = {0};

    for (int i = 0; i < colors.size(); i++) {
        colorsRecs[i].x = 10 + 30.0f * i + 2 * i;
        colorsRecs[i].y = 10;
        colorsRecs[i].width = 30;
        colorsRecs[i].height = 30;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

    raylib::Window window(screenWidth, screenHeight, "sandbox by Bensuperpc");

    SetTargetFPS(targetFPS);

    raylib::Image gridImage(screenWidth, screenHeight, RAYWHITE);

    Color *pixels = gridImage.LoadColors();

    raylib::Texture gridTexture(gridImage);

    float brushSize = 20.0f;

    Cell selectedElement = Cell::air;
    auto sandbox = benlib::Sandbox(screenWidth, screenHeight);

    uint64_t framesCounter = 0;

    bool paused = false;

    while (!WindowShouldClose()) {
        framesCounter++;

        Vector2 mousePosition = GetMousePosition();

        if (mousePosition.y > 50) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                sandbox.SetCircle(mousePosition.x, mousePosition.y, static_cast<uint64_t>(brushSize), selectedElement);
            }

            if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                sandbox.SetCircle(mousePosition.x, mousePosition.y, static_cast<uint64_t>(brushSize), Cell::air);
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < colors.size(); i++) {
                if (CheckCollisionPointRec(mousePosition, colorsRecs[i])) {
                    // TODO: avoid out of range
                    selectedElement = static_cast<Cell>(i);
                    break;
                }
            }
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
            auto img = raylib::Image(pixels, screenWidth, screenHeight);
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

        // Update image
        if (framesCounter % (targetFPS / ImageUpdatePerSecond) == 0) {
            // #if defined(_OPENMP)
            // #  pragma omp parallel for collapse(2) schedule(auto)
            // #endif
            for (uint64_t x = 0; x < screenWidth; x++) {
                for (uint64_t y = 0; y < screenHeight; y++) {
                    pixels[static_cast<uint64_t>(x + y * screenWidth)] = colorMap[sandbox.GetCell(x, y)];
                }
            }

            // Update texture
            gridTexture.Update(pixels);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(gridTexture, 0, 0, WHITE);

        // If eraser is selected, draw a circle without filling
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            DrawCircleLines((int)mousePosition.x, (int)mousePosition.y, brushSize, colorMap[selectedElement]);
        } else {
            DrawCircle(GetMouseX(), GetMouseY(), brushSize, colorMap[selectedElement]);
        }

        DrawRectangle(0, 0, GetScreenWidth(), 50, RAYWHITE);
        DrawLine(0, 50, GetScreenWidth(), 50, LIGHTGRAY);

        for (int i = 0; i < colors.size(); i++) {
            DrawRectangleRec(colorsRecs[i], colors[i]);
        }

        DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);
        DrawRectangleRec(colorsRecs[std::distance(colorMap.begin(), colorMap.find(selectedElement))], Fade(WHITE, 0.6f));

        // Draw selected element rectangle
        DrawRectangleLinesEx((Rectangle){colorsRecs[std::distance(colorMap.begin(), colorMap.find(selectedElement))].x - 2,
                                         colorsRecs[std::distance(colorMap.begin(), colorMap.find(selectedElement))].y - 2,
                                         colorsRecs[std::distance(colorMap.begin(), colorMap.find(selectedElement))].width + 4,
                                         colorsRecs[std::distance(colorMap.begin(), colorMap.find(selectedElement))].height + 4},
                             2, BLACK);
        // display FPS
        DrawRectangle(screenWidth - 90, 10, 80, 20, Fade(SKYBLUE, 0.95f));
        DrawText(TextFormat("FPS: %02d", GetFPS()), screenWidth - 80, 15, 15, DARKGRAY);

        EndDrawing();
    }
    gridImage.UnloadColors(pixels);

    return 0;
}
