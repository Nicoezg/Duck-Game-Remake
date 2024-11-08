#include <SDL2/SDL_video.h>
#include <string>
#include "game.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define DATA_PATH "../client/sprites/"


Game::Game(Client &client, int players) try : client(client), 
sdl(SDL_INIT_VIDEO), 
window("Duck Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN), 
renderer(window, -1, SDL_RENDERER_ACCELERATED), weapon(renderer), helmet(renderer), chestplate(renderer), bullet(renderer) {
    for (int i = 0; i < players; i++) {
        ducks.emplace_back(renderer, i);
    }
} catch (std::exception &e) {
    throw std::exception();
}

int Game::start() {
    try {
        window.SetIcon(SDL2pp::Surface(DATA_PATH "icon.png"));

        // Inicializar musica

        // Inicializar textures
        // loadSounds(renderer);
        // loadColors(renderer);



        // Game Loop
        ActionHandler actionHandler(client);

        auto rate = 1000 / 60; // 60 FPS

        while (true)
        {
            auto t1 = SDL_GetTicks();
            actionHandler.processEvents(); // Procesamos los eventos del pato
            render();
            
            /* IF BEHIND, KEEP WORKING */
            // Buscamos mantener un ritmo constante para ejecutar las funciones 'actualizar' y 'renderizar'
            // a una velocidad especifica 'rate'

            auto t2 = SDL_GetTicks();    // Inicializamos 't2' con el tiempo actual en milisegundos
            int rest = rate - (t2 - t1); // Cantidad de tiempo que debe esperarse
                                        // antes de la proxima iteracion. Al tiempo deseado entre iteraciones le restamos
                                        // la diferencia entre 't2' y 't1' que es el tiempo que se tardo en actualizar y renderizar

            // Si 'rest' es menor a cero quiere decir que nos estamos retrasando en comparacion
            // con el ritmo deseado
            if (rest < 0)
            {
                auto behind = -rest;                // ¿Cuanto tiempo estamos retrasados?
                auto lost = behind - behind % rate; // ¿Cuanto tiempo perdimos?
                t1 += lost;                         // Ajustamos 't1' para ponernos al dia con el tiempo perdido
                for (auto &duck : ducks) {
                    duck.updateFrame(int(lost / rate));
                }                                   
                // Aumentamos 'it' para reflejar las iteraciones que se han perdido debido al retraso

                // Si 'rest' es mayor o igual a cero quiere decir que no nos estamos quedando atras
            }
            else
            {
                // std::cout << rest << std::endl;
                SDL_Delay(rest); // Descansamos el valor 'rest' antes de la proxima iteracion para
                                // mantener un ritmo constante
            }

            t1 += rate; // Aumentamos 't1' en 'rate' para programar la proxima iteracion
            for (auto &duck : ducks) {
                duck.updateFrame();
            }  

            // Nota: Si no casteamos a int la variable 'rest' se produce un desbordamiento y rest puede ser igual a '4294967294' lo cual hace
            // 		 que se cuelgue el juego
        }

    } catch (std::exception &e) { // 
        return 1;
    }
}

void Game::loadTextures(Renderer &renderer) {
    // FONDO
    this->textures[0] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "maps/background/forest.png").SetColorKey(true, 0));
    
    // PLATAFORMAS
    this->textures[1] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "maps/tiles/scaffolding.png").SetColorKey(true, 0));

    // PATO
    // Separar en manos, caminar, saltar, hacerse el muerto, etc.
    this->textures[2] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/white-duck.png").SetColorKey(true, 0));
    this->textures[3] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/greyduck.png").SetColorKey(true, 0));
    this->textures[4] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/yellowduck.png").SetColorKey(true, 0));
    this->textures[5] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/orangeduck.png").SetColorKey(true, 0));
    // Puede haber más patos

    // ARMAS
    this->textures[6] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/grenade.png").SetColorKey(true, 0));
    this->textures[7] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/banana.png").SetColorKey(true, 0));
    this->textures[8] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/pew-pew-laser.png").SetColorKey(true, 0));
    this->textures[9] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-rifle.png").SetColorKey(true, 0));
    this->textures[10] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/ak-47.png").SetColorKey(true, 0));
    this->textures[11] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/duel-pistol.png").SetColorKey(true, 0));
    this->textures[12] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/cowboy-pistol.png").SetColorKey(true, 0));
    this->textures[13] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/magnum.png").SetColorKey(true, 0));
    this->textures[14] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/shotgun.png").SetColorKey(true, 0));
    this->textures[15] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/sniper.png").SetColorKey(true, 0));

    // BALAS
    this->textures[16] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-flare.png").SetColorKey(true, 0));
    this->textures[17] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-beam.png").SetColorKey(true, 0));
    this->textures[18] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-rebound.png").SetColorKey(true, 0));
    this->textures[19] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/chain-bullet.png").SetColorKey(true, 0));
    this->textures[20] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/pistol-shell.png").SetColorKey(true, 0));
    this->textures[21] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/magnum-shell.png").SetColorKey(true, 0));
    this->textures[22] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/shotgun-shell.png").SetColorKey(true, 0));

    // ARMADURAS Y CASCOS
    this->textures[23] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/chestplate-equipped.png").SetColorKey(true, 0));
    this->textures[24] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/knight-helmet-equipped.png").SetColorKey(true, 0));
    this->textures[25] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/helmet-equipped.png").SetColorKey(true, 0));
    this->textures[26] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/chestplate.png").SetColorKey(true, 0));
    this->textures[27] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/knight-helmet.png").SetColorKey(true, 0));
    this->textures[28] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/helmet.png").SetColorKey(true, 0));

    // CRATES
    this->textures[29] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "props/crate.png").SetColorKey(true, 0));

}

void Game::update(Broadcast broadcast) {
    for (auto &player : broadcast.get_players()) {
        ducks[player.get_player_id()].update(player);
    }

    /* for (auto &bulletDTO : broadcast.get_bullets()) {
        bullets.push_back(bullet);
    }
    for (auto &weaponDTO : broadcast.get_weapon_spawns()) {
        weapons_spawns.push_back(weapon);
    } */
}

// Puede haber un problema de sincronizacion entre update y render.

void Game::render()
{
    renderer.SetDrawColor(0,0,0,255);
    renderer.Clear();
    for (auto &duck : ducks) {
        duck.render(renderer);
        weapon.render(duck.getPosX(), duck.getPosY(), 0); // a cambiar
        helmet.render(duck.getPosX(), duck.getPosY(), 0); // si hay helmet
        chestplate.render(duck.getPosX(), duck.getPosY(), 0); // si hay chestplate
    }
    // for (auto &bullet : bullets) { // Dibujo las balas
        // bullet.render(bullet.getPosX(), bullet.getPosY(), bullet.get_rotation(), bullet.get_type());
    // }
    // for (auto &weaponSpawn : weaponSpawns){ // Dibujo las arams que spawnearon
        // weapon.render(weaponSpawn.getPosX(), weaponSpawn.getPosY(), weaponSpawn.get_type());
    // }
    // bullets.clear();
    // weaponSpawns.clear();
    renderer.Present();
}