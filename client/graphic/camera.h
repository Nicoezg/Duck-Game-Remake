#include <SDL2pp/SDL2pp.hh>
#include <vector>
class CameraZoom {
    private: 
        SDL2pp::Renderer& renderer;
        SDL2pp::Rect viewport;
        float minScale, maxScale, zoomSpeed, scale;
    public:
        CameraZoom(SDL2pp::Renderer& renderer, const SDL2pp::Rect& viewport, float minScale = 0.5f, float maxScale = 2.0f, float zoomSpeed = 0.1f);
        
        void update(const std::vector<SDL2pp::Rect>& playerRects);
};