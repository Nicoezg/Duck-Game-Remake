#ifndef SOUND_H
#define SOUND_H

#include <SDL2pp/SDL2pp.hh>
#include <memory>

class Sound {

private:
  std::unique_ptr<SDL2pp::Mixer> mixer;
  std::shared_ptr<SDL2pp::Chunk> sound;

  bool played;
  int loops;
  int channel;

public:
  explicit Sound(std::shared_ptr<SDL2pp::Chunk> sound);
  Sound();

  void change(std::shared_ptr<SDL2pp::Chunk> nuevoSound, int loops = 0);
  void play();
  void reset();
};

#endif // Sound_h