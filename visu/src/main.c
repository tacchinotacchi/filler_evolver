/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 00:19:46 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/08 23:44:45 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	draw_grid(t_visu *v)
{
	draw_grid_verti(v);
	draw_grid_horiz(v);
}

static void	update_visualizer(t_visu *v)
{
	int	quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&v->event) != 0)
		{
			if (v->event.type == SDL_QUIT)
				quit = 1;
			else if (v->event.type == SDL_KEYDOWN)
				key_event(v);
		}
		draw_grid(v);
		check_piece(v);
		SDL_UpdateWindowSurface(v->window);
	}
}

static void	get_map_window(t_visu *v)
{
	get_mapsize(v);
	get_windowsize(v);
}

static void	parse_filler(t_visu *v)
{
	init_parse(v);
	continue_parse(v);
}

int			main(void)
{
	t_visu		v;
	int			quit;

	ft_bzero(&v, sizeof(v));
	quit = 0;
	get_map_window(&v);
	parse_filler(&v);
	if (!(init_sdl(&v)))
		ft_exit(&v);
	else
		update_visualizer(&v);
	ft_close(&v);
	list_del(&(v.page), free_content);
	return (0);
}
