#ifndef __SDL_INIT_H__
#define __SDL_INIT_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include <sdl/color.h>           // sdl::Color
#include <sdl/ecs/ecs.h>         // sdl::ecs::Component
#include <sdl/event.h>           // sdl::Event, sdl::EventHandler
#include <sdl/api/noncopyable.h> // sdl::api::NonCopyable
#include <sdl/pixel.h>           // sdl::Pixel
#include <sdl/point.h>           // sdl::Point
#include <sdl/rect.h>            // sdl::Rect
#include <sdl/size.h>            // sdl::Size
#include <sdl/surface.h>         // sdl::Surface
#include <sdl/window.h>          // sdl::Window

#ifdef main
#undef main
#endif

namespace sdl{
  constexpr auto INIT_TIMER = SDL_INIT_TIMER;
  constexpr auto INIT_AUDIO = SDL_INIT_AUDIO;
  constexpr auto INIT_VIDEO = SDL_INIT_VIDEO;
  constexpr auto INIT_JOYSTICK = SDL_INIT_JOYSTICK;
  constexpr auto INIT_HAPTIC = SDL_INIT_HAPTIC;
  constexpr auto INIT_GAMECONTROLLER = SDL_INIT_GAMECONTROLLER;
  constexpr auto INIT_EVENTS = SDL_INIT_EVENTS;
  constexpr auto INIT_NOPARACHUTE = SDL_INIT_NOPARACHUTE;
  constexpr auto INIT_EVERYTHING = SDL_INIT_EVERYTHING;

  inline void init(Uint32 flags){
    if(SDL_Init(flags)){
      const std::string error_message = "Failed to init SDL: ";
      throw std::runtime_error{error_message + SDL_GetError()};
    }
  }

  inline void quit() {
    SDL_Quit();
  }

  class Context : api::NonCopyable, public ecs::BaseComponent{
  public:
    Context(unsigned flags = 0);
    virtual ~Context();
  };

} // namespace sdl

#endif // __SDL_INIT_H__
