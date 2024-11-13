#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include <vector>
#include <mutex>
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
#include "../../common/events/score.h"
#include "../../common/events/game_over.h"

using namespace SDL2pp;

class Game{
    private:
        //SDLTTF ttf;
        
        Client &client;

        SDL sdl; 

        SDLTTF ttf;
        
        Font font;

        Window window;

        Renderer renderer;

        DrawMap map;

        std::vector<std::shared_ptr<Duck>> ducks;

        std::list<Crate> crates;

        std::list<Bullet> bullets;

        std::list<Weapon> weaponSpawns;

        // std::vector<Explosion> explosions;

        DrawWeapon weapon;

        DrawHelmet helmet;

        DrawChestplate chestplate;

        DrawBullet bullet;

        DrawCrate crate;

        std::mutex mutex;

        bool stop;

        bool pause;

        void loadTextures(Renderer &renderer);

        int render();

        int processEvent();

        void showVictoryScreen(const GameOver& gameOver);

    public:
        Game(Client &client);

        void update(const Broadcast& broadcast);

        void showScores();

        void end(const GameOver& gameOver);
        
        int start();

        
        
};
#endif