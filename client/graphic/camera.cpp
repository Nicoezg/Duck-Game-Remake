#include "camera.h"
#include <cmath>
#include <algorithm>
#include <iostream>
    CameraZoom::CameraZoom(SDL2pp::Renderer& renderer, const SDL2pp::Rect& viewport, float minScale, float maxScale, float zoomSpeed)
        : renderer(renderer), viewport(viewport), minScale(minScale), maxScale(maxScale), zoomSpeed(zoomSpeed), scale(1.0f) {
        }
        
    void CameraZoom::update(const std::vector<SDL2pp::Rect>& playerRects) {
        if (playerRects.empty()) return;

        // Calculate the bounding box that contains all players
        int minX = std::numeric_limits<int>::max();
        int minY = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int maxY = std::numeric_limits<int>::min();

        // Debug output
        std::cout << "Number of players: " << playerRects.size() << std::endl;

        for (const auto& playerRect : playerRects) {
            minX = std::min(minX, playerRect.x);
            minY = std::min(minY, playerRect.y);
            maxX = std::max(maxX, playerRect.x + playerRect.w);
            maxY = std::max(maxY, playerRect.y + playerRect.h);
            std::cout << "Player at: (" << playerRect.x << ", " << playerRect.y << ")" << std::endl;
        }

        // Calculate the center point of all players
        float centerX = (minX + maxX) / 2.0f;
        float centerY = (minY + maxY) / 2.0f;

        // Calculate the width and height of the area containing all players
        float width = maxX - minX;
        float height = maxY - minY;

        // Add padding (20% of the content size)
        width *= 1.2f;
        height *= 1.2f;

        // Calculate required scale to fit all players
        float scaleX = viewport.w / width;
        float scaleY = viewport.h / height;

        // Use the smaller scale to ensure everything fits
        float targetScale = std::min(scaleX, scaleY);

        // If there's only one player, use a fixed scale
        if (playerRects.size() == 1) {
            targetScale = 1.0f;
        }

        // Clamp scale within bounds
        targetScale = std::clamp(targetScale, minScale, maxScale);

        // Smoothly interpolate to target scale
        scale = scale + (targetScale - scale) * zoomSpeed;

        // Calculate new viewport position
        int newViewportX = static_cast<int>(centerX - (viewport.w / (2 * scale)));
        int newViewportY = static_cast<int>(centerY - (viewport.h / (2 * scale)));

        // Assuming your game world dimensions - adjust these values
        const int WORLD_WIDTH = 640;  // Replace with your actual world width
        const int WORLD_HEIGHT = 480; // Replace with your actual world height

        // Ensure viewport stays within world bounds
        newViewportX = std::max(0, std::min(newViewportX, WORLD_WIDTH - viewport.w));
        newViewportY = std::max(0, std::min(newViewportY, WORLD_HEIGHT - viewport.h));

        // Update viewport position
        viewport.x = newViewportX;
        viewport.y = newViewportY;

        // Debug output
        std::cout << "Scale: " << scale << std::endl;
        std::cout << "Viewport: (" << viewport.x << ", " << viewport.y 
                  << ") " << viewport.w << "x" << viewport.h << std::endl;
        std::cout << "Center: (" << centerX << ", " << centerY << ")" << std::endl;

        // Apply transformations
        renderer.SetScale(scale, scale);
        renderer.SetViewport(viewport);
    }