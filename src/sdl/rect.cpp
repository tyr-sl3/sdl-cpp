#include <sdl/rect.h>

sdl::Rect::Rect() noexcept
	: x(0), y(0), w(0), h(0){}

sdl::Rect::Rect(int coordX, int coordY) noexcept
	: Rect(coordX, coordY, 0, 0){}

sdl::Rect::Rect(int coordX, int coordY, unsigned width, unsigned height) noexcept
	: x(coordX), y(coordY), w(width), h(height){}

sdl::Rect::Rect(SDL_Rect const& rect) noexcept
	: Rect(rect.x, rect.y, static_cast<unsigned>(rect.w), static_cast<unsigned>(rect.h)){}

sdl::Rect::operator SDL_Rect() const noexcept{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = static_cast<int>(w);
	rect.h = static_cast<int>(h);
	return rect;
}