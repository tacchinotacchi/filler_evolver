/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 03:18:28 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/02 06:03:56 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ft_close(t_visu *v)
{
	SDL_FreeSurface(v->surf);
	v->surf = NULL;
	SDL_DestroyWindow(v->window);
	v->window = NULL;
	SDL_Quit();
}

void	ft_exit(t_visu *v)
{
	if (v->page != NULL)
		list_del(&(v->page), free_content);
	exit(0);
}

void	free_content(void *content, size_t content_size)
{
	int	index;

	(void)content_size;
	index = 0;
	while ((*(char***)content)[index])
	{
		free((*(char***)content)[index]);
		index++;
	}
	free((*(char***)content));
}

void	key_event(t_visu *v)
{
	if (v->event.key.keysym.sym == SDLK_LEFT)
	{
		if (v->page->prev)
			v->page = v->page->prev;
	}
	else if (v->event.key.keysym.sym == SDLK_RIGHT)
	{
		if (v->page->next)
			v->page = v->page->next;
	}
	else if (v->event.key.keysym.sym == SDLK_UP)
	{
		while (v->page->next)
			v->page = v->page->next;
	}
	else if (v->event.key.keysym.sym == SDLK_DOWN)
	{
		while (v->page->prev)
			v->page = v->page->prev;
	}
}
