#ifndef __SCENE_H__
#define __SCENE_H__

// **********************
// ** Standard library **
//***********************
#include <cassert>     // assert
#include <type_traits> // std::is_base_of
#include <vector>      // std::vector

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include <sdl/api/iupdatable.h> // sdl::api::IUpdatable
#include <sdl/ecs/ecs.h>        // sdl::ecs::BaseComponent
#include <sdl/idrawable.h>      // sdl::IDrawable

namespace sdl {

  template<class T>
  constexpr auto is_updatable_component = ecs::api::is_component<T> && std::is_base_of<api::IUpdatable, T>::value;

  template<class T>
  constexpr auto is_drawable_component = ecs::api::is_component<T> && std::is_base_of<IDrawable, T>::value;

  class SceneComponent : public ecs::Component {
  public:
    SceneComponent() = default;
    virtual ~SceneComponent() = default;
  };
  
  template<class T>
  constexpr auto is_scene_component = std::is_base_of<SceneComponent, T>::value;
  
  namespace api {
    using BaseSceneComponent = ecs::api::RootComponent<SceneComponent>;
  } // namespace sdl::api
  
  class Scene :
    private api::BaseSceneComponent,
    public api::IUpdatable,
    public IDrawable
  {
    using Base = ecs::api::RootComponent<SceneComponent>;
  public:
    Scene() = default;
    virtual ~Scene() = default;
    template<class T, class ...Args>
    T& add(Args... args);
    using Base::get;
    void update() override;
  private:
    void on_window(Window& window, Point const& coords, NullableRect const& src_rect = api::NULL_VAL) const override;
    std::vector<api::IUpdatable *> updatables_;
    std::vector<IDrawable *> drawables_;
  };

  template<class T, class ...Args>
  T& Scene::add(Args... args) {
    static_assert(is_scene_component<T>, "Not a SceneComponent");
    auto& elem = api::BaseSceneComponent::add<T>(args...);
    if (is_updatable_component<T>) {
      updatables_.push_back(dynamic_cast<api::IUpdatable*>(&elem));
    }
    if (is_drawable_component<T>) {
      drawables_.push_back(dynamic_cast<IDrawable*>(&elem));
    }
    return elem;
  }

  void Scene::update() {
    for (auto& elem : updatables_) {
      assert(elem && "Null pointer");
      elem->update();
    }
  }

  void Scene::on_window(Window& window, Point const& coords, NullableRect const& src_rect) const {
    for (auto const ptr : drawables_) {
      assert(ptr && "Null pointer");
      ptr->on_window(window, coords, src_rect);
    }
  }
} // namespace sdl

#endif // __SCENE_H__
