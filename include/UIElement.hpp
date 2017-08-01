#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class UIElement;

typedef void (onEvent)(void *param, UIElement *elem);

struct MouseEvent
{
	bool	set;
	onEvent	*e;
	void	*param;
	MouseEvent	&operator=(const MouseEvent &src);
	void		operator()(UIElement *elem);
};


class UIElement
{
private:
	SDL_Rect					rect;
	SDL_Rect					text;
	float 						vertices[18];
	MouseEvent					mouseDown,
								mouseUp,
								mouseMove,
								mouseLeave;
	bool						mouseLeft;

public:
	static bool					enableSelection;
	SDL_Color					color;
	int							mouseX, mouseY;
	bool						visible;
	bool						active;
	bool						selected;
	int							layer;
	SDL_Texture					*texture;
	SDL_Texture					*textTexture;

	UIElement();
	UIElement(int _x, int _y, int w, int h);
	UIElement(const UIElement &src);
	~UIElement();

	UIElement	&operator=(const UIElement &src);
	bool		checkEvent(const SDL_Event &e, bool exec = true);
	bool		inRange(int x, int y);
	void		draw(SDL_Renderer *ren);
	void		drawGL();
	void		show();
	void		hide();
	void		enable();
	void		disable();
	void		move(int x, int y);
	void		resize(int w, int h);
	int			width();
	int			height();
	int			posX();
	int			posY();

	template<typename T>
	void		setMouseDown(onEvent *func, T &param)
	{
		mouseDown.e = func;
		mouseDown.param = &param;
		mouseDown.set = true;
	}

	template<typename T>
	void		setMouseUp(onEvent *func, T &param)
	{
		mouseUp.e = func;
		mouseUp.param = &param;
		mouseUp.set = true;
	}

	template<typename T>
	void		setMouseMove(onEvent *func, T &param)
	{
		mouseMove.e = func;
		mouseMove.param = &param;
		mouseMove.set = true;
	}

	template<typename T>
	void		setMouseLeave(onEvent *func, T &param)
	{
		mouseLeave.e = func;
		mouseLeave.param = &param;
		mouseLeave.set = true;
	}

	void				setColor(SDL_Color &col);
	void				setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void				setTexture(SDL_Texture *_texture);
	void				setText(SDL_Renderer * ren, const char *text, TTF_Font *font, SDL_Color col);
	virtual void		onMouseDown();
	virtual void		onMouseUp();
	virtual void		onMouseMove();
	virtual void		onMouseLeave();
};

