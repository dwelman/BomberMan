#include <UIElement.hpp>

bool UIElement::enableSelection = true;

UIElement::UIElement() :  mouseLeft(true), visible(false), active(false), selected(false), layer(0),
						  texture(nullptr)
{
	memset(&rect, 0, sizeof(SDL_Rect));
	memset(&text, 0, sizeof(SDL_Rect));
	memset(&mouseDown, 0, sizeof(MouseEvent));
	memset(&mouseUp, 0, sizeof(MouseEvent));
	memset(&mouseMove, 0, sizeof(MouseEvent));
	memset(&mouseLeave, 0, sizeof(MouseEvent));
	memset(&color, 0, sizeof(SDL_Color));
}

UIElement::UIElement(int _x, int _y, int _w, int _h)
	: mouseLeft(true), visible(true), active(true), selected(false), layer(0),
	  texture(nullptr)
{
	rect.x = _x;
	rect.y = _y;
	rect.w = _w;
	rect.h = _h;

	memset(vertices, 0, 18 * sizeof(float));

	//Top Left -- T1
	vertices[0] = _x;
	vertices[1] = _y;

	//Bottom Left
	vertices[3] = static_cast<float> (_x);
	vertices[4] = static_cast<float> (_y + _h);

	//Bottom Right
	vertices[6] = static_cast<float> (_x + _w);
	vertices[7] = static_cast<float> (_y + _h);


	//Bottom Right -- T2
	vertices[9] = static_cast<float> (_x + _w);
	vertices[10] = static_cast<float> (_y + _h);

	//Top Right -- T2
	vertices[12] = static_cast<float> (_x + _w);
	vertices[13] = static_cast<float> (_y);

	//Bottom Right --T2
	vertices[15] = _x;
	vertices[16] = _y;

	memcpy (&text , &rect, sizeof(SDL_Rect));
	memset(&mouseDown, 0, sizeof(MouseEvent));
	memset(&mouseUp, 0, sizeof(MouseEvent));
	memset(&mouseMove, 0, sizeof(MouseEvent));
	memset(&mouseLeave, 0, sizeof(MouseEvent));
}

UIElement::UIElement(const UIElement & src)
{
	*this = src;
}

UIElement::~UIElement()
{
	if (texture)
		SDL_DestroyTexture(texture);
}

UIElement & UIElement::operator=(const UIElement & src)
{
	rect = src.rect;
	visible = src.visible;
	active = src.active;
	mouseDown = src.mouseDown;
	mouseUp = src.mouseUp;
	mouseMove = src.mouseMove;
	mouseLeft = src.mouseLeft;
	return (*this);
}

bool UIElement::checkEvent(const SDL_Event & e, bool exec)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	{
		if (inRange(e.button.x, e.button.y))
		{
			if (exec)
				onMouseDown();
			mouseX = e.button.x;
			mouseY = e.button.y;
			if (enableSelection)
			{
				selected = true;
				enableSelection = false;
			}
			return (true);
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		selected = false;
		if (inRange(e.button.x, e.button.y))
		{
			if (exec)
				onMouseUp();
			mouseX = e.button.x;
			mouseY = e.button.y;
			enableSelection = true;
			return (true);
		}
		break;
	}
	case SDL_MOUSEMOTION:
	{
		if (inRange(e.motion.x, e.motion.y) || selected)
		{
			mouseX = e.button.x;
			mouseY = e.button.y;
			if (exec)
				onMouseMove();
			mouseLeft = false;
			return (true);
		}
		else
		{
			if (mouseLeft == false && exec)
			{
				onMouseLeave();
			}
			mouseLeft = true;
		}
		break;
	}
	default:
		break;
	}
	return false;
}

bool UIElement::inRange(int x, int y)
{
	return (   x > rect.x 
			&& x < rect.x + rect.w
			&& y > rect.y
			&& y < rect.y + rect.h
			&& active);
}

void UIElement::draw(SDL_Renderer *ren)
{
	if (visible)
	{

		if (texture != nullptr)
		{
			SDL_RenderCopy(ren, texture, NULL, &rect);
			if (textTexture != nullptr)
			{
				SDL_RenderCopy(ren, textTexture, NULL, &rect);
			}
		}
		else
		{
			SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(ren, &rect);
			if (textTexture != nullptr)
			{
				SDL_RenderCopy(ren, textTexture, NULL, &rect);
			}
			SDL_SetRenderDrawColor(ren, 42, 42, 42, 42);
		}
	}
}

void UIElement::drawGL()
{
	if (visible)
	{
	}
}

void UIElement::show()
{
	visible = true;
}

void UIElement::hide()
{
	visible = false;
}

void UIElement::enable()
{
	this->active = true;
}

void UIElement::disable()
{
	this->active = false;
}

void UIElement::move(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void UIElement::resize(int w, int h)
{
	rect.w = w;
	rect.h = h;
}

int UIElement::width()
{
	return rect.w;
}

int UIElement::height()
{
	return rect.h;
}

int UIElement::posX()
{
	return rect.x;
}

int UIElement::posY()
{
	return rect.y;
}

void UIElement::setColor(SDL_Color & col)
{
	memcpy(&color, &col, sizeof(SDL_Color));
}

void UIElement::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	color.a = a;
	color.b = b;
	color.g = g;
	color.r = r;
}

void			UIElement::setTexture(SDL_Texture *_texture)
{
	texture = _texture;
	int texW, texH;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

}

void				UIElement::setText(SDL_Renderer * ren, const char *text, TTF_Font *font, SDL_Color col)
{
	SDL_Surface *text_surface = TTF_RenderText_Solid(font ,text, col);
	textTexture = SDL_CreateTextureFromSurface(ren, text_surface);
	SDL_FreeSurface(text_surface);
}

float * UIElement::getVertices()
{
	return (this->vertices);
}

void UIElement::onMouseDown()
{
	if (mouseDown.set)
	{
		mouseDown(this);
	}
}

void UIElement::onMouseUp()
{
	if (mouseUp.set)
	{
		mouseUp(this);
	}
}

void UIElement::onMouseMove()
{
	if (mouseMove.set)
	{
		mouseMove(this);
	}
}

void UIElement::onMouseLeave()
{
	if (mouseLeave.set)
	{
		mouseLeave(this);
	}
}

MouseEvent & MouseEvent::operator=(const MouseEvent & src)
{
	memcpy(this, &src, sizeof(MouseEvent));
	return (*this);
}

void MouseEvent::operator()(UIElement *elem)
{
	e(param, elem);
}
