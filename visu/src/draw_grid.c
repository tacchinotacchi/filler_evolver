/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 08:23:03 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/05 00:13:01 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	draw_grid_horiz(t_visu *v)
{
	int			nb_y;
	SDL_Rect	info;
	SDL_Surface *grid;

	nb_y = v->nb_y;
	info.x = (v->w_width - v->width_line) / 2;
	info.y = (v->w_height - v->height_line) / 2;
	info.h = 1;
	info.w = v->width_line + 2;
	if (!(grid = SDL_CreateRGBSurface(0, info.w, info.h, 32, 0, 0, 0, 0)))
		ft_exit(v);
	while (nb_y-- >= 0)
	{
		if (SDL_FillRect(grid, NULL,
		SDL_MapRGB(grid->format, 242, 237, 215)) < 0)
			ft_exit(v);
		if (SDL_BlitSurface(grid, NULL, v->surf, &info) < 0)
			ft_exit(v);
		info.y += v->square + 1;
	}
	SDL_FreeSurface(grid);
}

void	draw_grid_verti(t_visu *v)
{
	int			nb_x;
	SDL_Rect	info;
	SDL_Surface	*grid;

	nb_x = v->nb_x;
	v->width_line = v->nb_x * v->square + (v->nb_x - 1);
	v->height_line = v->nb_y * v->square + (v->nb_y - 1);
	info.x = (v->w_width - v->width_line) / 2;
	info.y = (v->w_height - v->height_line) / 2;
	v->origin_x = info.x;
	v->origin_y = info.y;
	info.h = v->height_line + 2;
	info.w = 1;
	if (!(grid = SDL_CreateRGBSurface(0, info.w, info.h, 32, 0, 0, 0, 0)))
		ft_exit(v);
	while (nb_x-- >= 0)
	{
		if (SDL_FillRect(grid, NULL,
		SDL_MapRGB(grid->format, 242, 237, 215)) < 0)
			ft_exit(v);
		if (SDL_BlitSurface(grid, NULL, v->surf, &info) < 0)
			ft_exit(v);
		info.x += v->square + 1;
	}
	SDL_FreeSurface(grid);
}
