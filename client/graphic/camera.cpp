#include "camera.h"
#include <cmath>
#include <algorithm>
#include <iostream>
    CameraZoom::CameraZoom(SDL2pp::Renderer& renderer, const SDL2pp::Rect& viewport, float minScale, float maxScale, float zoomSpeed)
        : renderer(renderer), viewport(viewport), minScale(minScale), maxScale(maxScale), zoomSpeed(zoomSpeed), scale(1.0f) {
        }
    void CameraZoom::update(const std::vector<SDL2pp::Rect>& playerRects) {
        // Calculate the center of all players
        float centerX = 0, centerY = 0;
        for (const auto& playerRect : playerRects) {
            centerX += playerRect.x + playerRect.w / 2;
            centerY += playerRect.y + playerRect.h / 2;
        }
        centerX /= playerRects.size();
        centerY /= playerRects.size();
        // Calculate the maximum distance from the center to any player
        float maxDistance = 0;
        for (const auto& playerRect : playerRects) {
            float distance = std::sqrt(std::pow(playerRect.x + playerRect.w / 2 - centerX, 2) +
                                      std::pow(playerRect.y + playerRect.h / 2 - centerY, 2));
            maxDistance = std::max(maxDistance, distance);
        }
        // Adjust the camera scale based on the maximum distance
        scale = std::clamp(1.0f - maxDistance / viewport.w * zoomSpeed, minScale, maxScale);
        // Update the camera position to keep the center of all players centered
        viewport.x = centerX - viewport.w / (2 * scale);
        viewport.y = centerY - viewport.h / (2 * scale);
        // Apply the camera transformation to the renderer
        renderer.SetScale(scale, scale);
        renderer.SetViewport(viewport);
    }