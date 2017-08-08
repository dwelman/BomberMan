#pragma once

#include <vector>
#include <UIElement.hpp>

class UIGroup
{
private:
	std::vector<UIElement*>	elem;
public:
	static int				next;
	const int				ID;
	UIGroup();
	UIGroup(const UIGroup &src);
	~UIGroup();

	UIGroup &operator=(const UIGroup &src);
	void	hide();
	void	show();
	void	enable();
	void	disable();
	void	draw(SDL_Renderer *ren);
	void	add(UIElement &elem);
	void	checkEvent(const SDL_Event & e, bool exec = true);

	template <typename F>
	void	applyAll(F func)
	{
		for (auto it = elem.begin(), end = elem.end(); it != end; it++)
		{
			func(it);
		}
	}

	template <typename F, typename B>
	void	applyAllIf(F func, B condition)
	{
		for (auto it = elem.begin(), end = elem.end(); it != end; it++)
		{
			if (condition(*it))
				func(*it);
		}
	}
};

