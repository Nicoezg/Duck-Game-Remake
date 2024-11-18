#include <SDL2/SDL_video.h>
#include <string>
#include "game.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2pp/Font.hh>
#include <SDL2pp/SDL2pp.hh>

#define BACKGROUND_MUSIC_VOLUME SDL_MIX_MAXVOLUME / 15
#define BACKGROUND_MUSIC_CHANNEL 0
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480


Game::Game(Client &client) try: client(client),
                                sdl(SDL_INIT_VIDEO), font("../client/sprites/font.ttf", 24),
                                window("Duck Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                       WINDOW_HEIGHT, SDL_WINDOW_SHOWN),
                                renderer(window, -1, SDL_RENDERER_ACCELERATED), camera(renderer, SDL2pp::Rect{0,0,640,480}), map(renderer), ducks(), crates(),
                                bullets(), weaponSpawns(), explosions(), weapon(renderer), helmet(renderer), chestplate(renderer),
                                bullet(renderer), crate(renderer), explosion(renderer), mutex(), stop(false), pause(false) {
} catch (std::exception &e) {
    throw std::exception();
}

int Game::start() {
    try {
        // processEvent(); // Cargo el mapa
        // SDL_SetWindowSize(window.Get(), map.getWidth(), map.getHeight());

        // window.SetIcon(SDL2pp::Surface(DATA_PATH "icon.png").SetColorKey(true, 0)); // Creo que no funciona

        // Inicializar musica

        Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

        Chunk sound("../client/graphic/audio/background-music.wav");

        sound.SetVolume(BACKGROUND_MUSIC_VOLUME);

        mixer.PlayChannel(BACKGROUND_MUSIC_CHANNEL, sound, -1);

        // Game Loop
        ActionHandler actionHandler(client);

        auto rate = 1000 / 60; // 60 FPS

        while (true)
        {
            auto t1 = SDL_GetTicks();
            update_state();
            actionHandler.processEvents(); // Idea: podria ser otro hilo. como se podria parar el juego si se va?
            int code = render(); // Renderizamos el juego
            if (code == 1) {
                return 0;
            }
            if (code == 2) {
                continue;
            }

            /* IF BEHIND, KEEP WORKING */
            // Buscamos mantener un ritmo constante para ejecutar las funciones 'actualizar' y 'renderizar'
            // a una velocidad especifica 'rate'

            auto t2 = SDL_GetTicks();    // Inicializamos 't2' con el tiempo actual en milisegundos
            int rest = rate - (t2 - t1); // Cantidad de tiempo que debe esperarse
            // antes de la proxima iteracion. Al tiempo deseado entre iteraciones le restamos
            // la diferencia entre 't2' y 't1' que es el tiempo que se tardo en actualizar y renderizar

            // Si 'rest' es menor a cero quiere decir que nos estamos retrasando en comparacion
            // con el ritmo deseado
            if (rest < 0) {
                auto behind = -rest;                // ¿Cuanto tiempo estamos retrasados?
                auto lost = behind - behind % rate; // ¿Cuanto tiempo perdimos?
                t1 += lost;                         // Ajustamos 't1' para ponernos al dia con el tiempo perdido
                for (auto &duck: ducks) {
                    duck->updateFrame(int(lost / rate));
                }
                // Aumentamos 'it' para reflejar las iteraciones que se han perdido debido al retraso

                // Si 'rest' es mayor o igual a cero quiere decir que no nos estamos quedando atras
            } else {
                // std::cout << rest << std::endl;
                SDL_Delay(rest); // Descansamos el valor 'rest' antes de la proxima iteracion para
                // mantener un ritmo constante
            }

            t1 += rate; // Aumentamos 't1' en 'rate' para programar la proxima iteracion
            for (auto &duck: ducks) {
                duck->updateFrame();
            }

            // Nota: Si no casteamos a int la variable 'rest' se produce un desbordamiento y rest puede ser igual a '4294967294' lo cual hace
            // 		 que se cuelgue el juego

        }

        return 0;

    } catch (std::exception &e) { // 
        return 1;
    }
}

void Game::update_state() {
    std::shared_ptr<Event> event = client.try_read();
    if (event->get_type() == BROADCAST) {
        update(*event);
    } else if (event->get_type() == MAP_LOAD) {
        map.load(*event);
    }
}

void Game::update(const Event &broadcast) {
    std::lock_guard<std::mutex> lock(mutex);
    //std::vector<SDL2pp::Rect> playerRects;
    if (ducks.size() != broadcast.get_players().size()) {
        ducks.clear();
        for (auto &player: broadcast.get_players()) {
            std::shared_ptr duck = std::make_shared<Duck>(renderer, player.get_player_id());
            duck->loadTextures();
            ducks.push_back(duck);
        }
    }
    for (auto &player: broadcast.get_players()) {
        ducks[player.get_player_id()-1]->update(player);
        //playerRects.push_back(SDL2pp::Rect(player.get_position_x(), player.get_position_y(), Duck::DUCK_WIDTH, Duck::DUCK_HEIGHT));
    }
    //camera.update(playerRects);

    bullets = broadcast.get_bullets();
    weaponSpawns = broadcast.get_weapons();
    crates = broadcast.get_crates();
    // explosions = broadcast.get_explosions();
}

void Game::showScores() {
    std::lock_guard<std::mutex> lock(mutex);
    pause = true;
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();
    // std::vector<std::string> names = score.get_names();
    // std::vector<int> scores = score.get_scores();
    Uint32 startTime = SDL_GetTicks();
    bool flash = true;
    while (SDL_GetTicks() - startTime < 5000) { // Flash for 5 seconds
        renderer.SetDrawColor(0, 0, 0, 255);
        renderer.Clear();
        if (flash) {
            for (size_t i = 0; i < 4; ++i) {
                std::string scoreText = "Player " + std::to_string(2);
                SDL2pp::Texture scoreTexture(renderer,
                                             font.RenderText_Blended(scoreText, SDL_Color{255, 255, 255, 255}));
                renderer.Copy(scoreTexture, SDL2pp::NullOpt,
                              SDL2pp::Rect(50, 50 + i * 30, scoreTexture.GetWidth(), scoreTexture.GetHeight()));
            }
            std::string timer =
                    "Time until next round: " + std::to_string((5000 - (SDL_GetTicks() - startTime)) / 1000);
            SDL2pp::Texture timerTexture(renderer, font.RenderText_Blended(timer, SDL_Color{255, 255, 255, 255}));
            renderer.Copy(timerTexture, SDL2pp::NullOpt,
                          SDL2pp::Rect(50, 50 + 4 * 30, timerTexture.GetWidth(), timerTexture.GetHeight()));
        }

        renderer.Present();
        SDL_Delay(500); // Flash interval
        flash = !flash;
    }
}

void Game::showVictoryScreen(const GameOver &gameOver) {
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();
    // Le podria agregar flash
    std::string victoryText = gameOver.get_winner() + " wins!";
    SDL2pp::Texture victoryTexture(renderer, font.RenderText_Blended(victoryText, SDL_Color{255, 255, 255, 255}));
    renderer.Copy(victoryTexture, SDL2pp::NullOpt,
                  SDL2pp::Rect(50, 50, victoryTexture.GetWidth(), victoryTexture.GetHeight()));
    renderer.Present();
    SDL_Delay(5000); // Victory screen duration
}

void Game::end(const GameOver &gameOver) {
    std::lock_guard<std::mutex> lock(mutex);
    stop = true;
    showVictoryScreen(gameOver);


    // a definir
}

int Game::render() {
    std::lock_guard<std::mutex> lock(mutex);
    if (stop) {
        return 1;
    }
    if (pause) {
        pause = false;
        return 2;
    }
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();
    // map.render();
    for (auto &duck: ducks) {
        duck->render();
    }
    for (auto &crateDTO: crates) { // Dibujo los crates
        crate.render(crateDTO);
    }
    for (auto &bulletDTO: bullets) { // Dibujo las balas
        bullet.render(bulletDTO);
    }
    for (auto &weaponDTO: weaponSpawns) { // Dibujo las armas que spawnearon
        weapon.render(weaponDTO);
    }
    for (auto &explosionDTO: explosions){
        explosion.render(explosionDTO);
    }
    renderer.Present();
    return 0;
}