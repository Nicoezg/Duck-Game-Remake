#include "camera.h"
#include <algorithm>
#include <cmath>

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480

CameraZoom::CameraZoom(SDL2pp::Renderer &renderer, const SDL2pp::Rect &viewport,
                       float minScale, float maxScale, float zoomSpeed)
    : renderer(renderer), viewport(viewport), minScale(minScale),
      maxScale(maxScale), zoomSpeed(zoomSpeed), scale(1.0f) {}

void CameraZoom::update(const std::vector<SDL2pp::Rect> &playerRects) {
  float centerX = 0, centerY = 0;
  for (const auto &playerRect : playerRects) {
    centerX += playerRect.x + playerRect.w / 2;
    centerY += playerRect.y + playerRect.h / 2;
  }

  centerX /= playerRects.size();
  centerY /= playerRects.size();

  float maxDistance = 0;
  for (const auto &playerRect : playerRects) {
    float distance =
        std::sqrt(std::pow(playerRect.x + playerRect.w / 2 - centerX, 2) +
                  std::pow(playerRect.y + playerRect.h / 2 - centerY, 2));
    maxDistance = std::max(maxDistance, distance);
  }

  scale = std::clamp(3.0f - maxDistance * zoomSpeed, minScale, maxScale);

  float scaledViewportWidth = viewport.w / scale;
  float scaledViewportHeight = viewport.h / scale;

  viewport.x = static_cast<int>(centerX - scaledViewportWidth / 2);
  viewport.y = static_cast<int>(centerY - scaledViewportHeight / 2);

  viewport.x = -std::max(
      0, std::min(viewport.x, WINDOW_WIDTH - static_cast<int>(scaledViewportWidth)));
  viewport.y = -std::max(
      0, std::min(viewport.y, WINDOW_HEIGHT - static_cast<int>(scaledViewportHeight)));

  renderer.SetScale(scale, scale);
  renderer.SetViewport(viewport);
}

void CameraZoom::reset() {
  renderer.SetScale(1.0f, 1.0f);
  renderer.SetViewport(SDL2pp::Rect{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT});
}
