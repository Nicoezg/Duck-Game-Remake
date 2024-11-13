#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL_rect.h>
#include <SDL2pp/SDL2pp.hh>
#include "animation_state.h"
#include <map>
#include <memory>

#define DATA_PATH "../client/sprites/"


class Duck
{
    public:
		//The dimensions of the duck
		static const int DUCK_WIDTH = 32;
		static const int DUCK_HEIGHT = 32;

		//Initializes the variables
		Duck(SDL2pp::Renderer& renderer, int id);

		void render(SDL2pp::Renderer& renderer);

		//void update(const Player &player);

		void updateFrame(int it = 1);

		int getPosX();

		int getPosY();

		bool isFacingRight();

		void loadTextures();

		//Destructor
		~Duck();

    // Duck class definition

    private:
		//The X and Y offsets of the duck

		int posX, posY;

		uint8_t id;

		bool direction;

		SDL2pp::Renderer &renderer;

		std::shared_ptr<SDL2pp::Texture> texture = nullptr;

		AnimationState animationState;

		SDL2pp::Rect walkClips[4];
		SDL2pp::Rect jumpClips[2];
		SDL2pp::Rect playDeadClips[3];
};
#endif