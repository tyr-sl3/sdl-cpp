#include <sdl/event.h>

sdl::EventHandler::EventHandler()
  : keyboard_handler_(add<KeyboardStateHandler>(false)),
  mouse_handler_(add<MouseStateHandler>(false)),
  on_quit_defined_(false)
{
}

void sdl::EventHandler::on_quit(Action const& fun) {
  assert(!on_quit_defined_ && "Already defined");
  on_quit_ = fun;
  on_quit_defined_ = true;
}

void sdl::EventHandler::update() {
  /*if (!on_quit_defined_) {
    throw std::runtime_error{"You must bind an exit function by calling EventHandler::on_quit before using it"};
  }*/
  sdl::Event e;
  while (SDL_PollEvent(&e)) {
    if (on_quit_defined_ && e.type == SDL_QUIT) {
      on_quit_();
    }
  }
  keyboard_handler_.update();
  mouse_handler_.update();
  if (key_actions_.size() > 0 || click_actions_.size() > 0) {
    handle_actions();
  }
}

void sdl::EventHandler::on_press(sdl::KeyCode code, Action const& fun) {
  key_actions_.insert(std::pair<KeyCode, Action>(code, fun));
}

void sdl::EventHandler::on_click(ClickCode code, Action const& fun) {
  click_actions_.insert(std::pair<ClickCode, Action>(code, fun));
}

void sdl::EventHandler::handle_actions() {
  const auto keyboard_state = keyboard_handler_.state();
  for (auto& pair : key_actions_) {
    if (keyboard_state[pair.first].pressed) {
      pair.second();
    }
  }
  const auto mouse_state = mouse_handler_.state();
  for (auto& pair : click_actions_) {
    if (mouse_state.clicked(pair.first)) {
      pair.second();
    }
  }
}
