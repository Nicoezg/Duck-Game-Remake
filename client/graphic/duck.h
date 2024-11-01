#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL_rect.h>
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class Duck
{
    public:
		//The dimensions of the duck
		static const int DUCK_WIDTH = 32;
		static const int DUCK_HEIGHT = 32;

		//Initializes the variables
		Duck(std::shared_ptr<SDL2pp::Texture> texture);

		void render(SDL2pp::Renderer& renderer, int frame);

		int getPosX();

		int getPosY();

		bool isJumping();

		bool isStill();

		void setClips();

		//Destructor
		~Duck();

    private:
		//The X and Y offsets of the duck
		int posX, posY;

		uint8_t id;

		bool falling;

		bool jumping;

		bool dead;

		bool playDead;

		bool direction;

		bool aimingUp;

		bool newAction;

		std::shared_ptr<SDL2pp::Texture> texture;

		SDL2pp::Rect walkClips[4];
		SDL2pp::Rect jumpClips[2];
		SDL2pp::Rect playDeadClips[3];
};
#endif