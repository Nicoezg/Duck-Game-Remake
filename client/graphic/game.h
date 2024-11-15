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
#include "draw/draw_explosion.h"
#include "../../common/events/base/event.h"
#include "../../common/events/map.h"
#include "../../common/events/score.h"
#include "../../common/events/game_over.h"
#include "camera.h"

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

        CameraZoom camera;

        DrawMap map;

        std::vector<std::shared_ptr<Duck>> ducks;

        std::list<CrateDTO> crates;

        std::list<BulletDTO> bullets;

        std::list<WeaponDTO> weaponSpawns;

        std::list<Explosion> explosions;

        DrawWeapon weapon;

        DrawHelmet helmet;

        DrawChestplate chestplate;

        DrawBullet bullet;

        DrawCrate crate;

        DrawExplosion explosion;

        std::mutex mutex;

        bool stop;

        bool pause;

        void loadTextures(Renderer &renderer);

        int render();

        int processEvent();

        void showVictoryScreen(const GameOver& gameOver);

    public:
        Game(Client &client);

        void update(const Event &broadcast);

        void showScores();

        void end(const GameOver& gameOver);
        
        int start();


    void update_state();
};
#endif