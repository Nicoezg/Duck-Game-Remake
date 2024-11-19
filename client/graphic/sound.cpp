#include "sound.h"

Sound::Sound(std::shared_ptr<SDL2pp::Chunk> sound): mixer(std::make_unique<SDL2pp::Mixer>(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096)),
                                      sound(sound),
                                      played(false),
                                      loops(0),
                                      channel(1) {}

Sound::Sound():   mixer(std::make_unique<SDL2pp::Mixer>(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096)),
                    played(true),
                    loops(0),
                    channel(1) {}

void Sound::change(std::shared_ptr<SDL2pp::Chunk> nuevoSound, int loops) {
    this->sound = nuevoSound;
    this->played = false;
    this->loops = loops;
}

// El channel donde se reproduce el Sound se libera automaticamente una vez que el
// Sound termino de reproducirse. No es necesario liberar explicitamente el channel.
void Sound::play() {

    if (this->mixer->IsChannelPlaying(this->channel)) {
        return;
    }

    if (not played) {
        this->sound->SetVolume(SDL_MIX_MAXVOLUME / 10);
        this->channel = this->mixer->PlayChannel(-1, *(this->sound), 0, this->loops);

        this->played = true;
    }
}