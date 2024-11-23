#ifndef DUCK_H
#define DUCK_H

#include <SDL2/SDL_rect.h>
#include <SDL2pp/SDL2pp.hh>
#include "animation_movement.h"
#include "draw/draw_helmet.h"
#include "draw/draw_chestplate.h"
#include "draw/draw_weapon.h"
#include "sound.h"
#include "common/events/player.h"
#include <map>
#include <memory>


class Duck
{
    public:
		//The dimensions of the duck
		static const int DUCK_WIDTH = 32;
		static const int DUCK_HEIGHT = 32;

		//Initializes the variables
		Duck(SDL2pp::Renderer& renderer, int id);

		void render();

		void update(const PlayerDTO &player);

		void updateFrame(int it = 1);

		int getPosX();

		int getPosY();

		bool isFacingRight();

		void loadTextures();

		DrawWeapon& getWeapon() { return weapon; }

		~Duck();

    private:
		int posX, posY;

		uint8_t id;

		bool direction;

		bool dead;

		SDL2pp::Renderer &renderer;

		std::shared_ptr<SDL2pp::Texture> weaponsTexture = nullptr;

		std::shared_ptr<SDL2pp::Texture> wingsTexture = nullptr;

		std::map<int, std::shared_ptr<SDL2pp::Chunk>> sfx;

		AnimationMovement animationMovement;

		Sound sound;

		DrawWeapon weapon;

		DrawHelmet helmet;

		DrawChestplate chestplate;

		SDL2pp::Rect walkClips[5];
		SDL2pp::Rect jumpClip;
		SDL2pp::Rect fallClip;
		SDL2pp::Rect stillClipWings;
		SDL2pp::Rect flappingClips[3];
		SDL2pp::Rect playDeadClips[3];

		SDL2pp::Rect walkWeaponClips[4];
		SDL2pp::Rect jumpWeaponClip;
		SDL2pp::Rect fallWeaponClip;
		SDL2pp::Rect stillClipWeapon;
		SDL2pp::Rect aimingUpwardsClip;
		SDL2pp::Rect recoilClip;
};
#endif