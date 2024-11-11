#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include <vector>
#include "../communication/client.h"
#include "duck.h"
#include "action_handler.h"
#include "../../common/events/broadcast.h"
#include "draw/draw_weapon.h"
#include "draw/draw_chestplate.h"
#include "draw/draw_helmet.h"
#include "draw/draw_bullet.h"
#include "draw/draw_crate.h"
#include "draw/draw_map.h"
#include "../../common/events/base/event.h"
#include "../../common/events/map.h"

using namespace SDL2pp;

class Game{
    private:
        //SDLTTF ttf;
        
        Client &client;

        SDL sdl;

        Window window;

        Renderer renderer;

        DrawMap map;

        std::vector<std::shared_ptr<Duck>> ducks;

        std::list<Crate> crates;

        std::list<Bullet> bullets;

        std::list<Weapon> weaponSpawns;

        // std::vector<Explosion> explosions;

        std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

        DrawWeapon weapon;

        DrawHelmet helmet;

        DrawChestplate chestplate;

        DrawBullet bullet;

        DrawCrate crate;

        void loadTextures(Renderer &renderer);

        void render();

        int processEvent();

        void showScores(const Scores& scores)

        void update(const Broadcast& broadcast);

        void showVictoryScreen();

    public:
        Game(Client &client, int players);
        
        int start();

        
        
};
#endif