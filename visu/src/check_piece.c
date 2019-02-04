/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 07:14:30 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/02 05:52:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	draw_piece(int y, int x, t_visu *v)
{
	SDL_Rect	info;
	SDL_Surface	*piece;

	info.x = v->origin_x + 1 + x * v->square + x;
	info.y = v->origin_y + 1 + y * v->square + y;
	info.h = v->square;
	info.w = v->square;
	if (!(piece = SDL_CreateRGBSurface(0, info.w, info.h, 32, 0, 0, 0, 0)))
		ft_exit(v);
	if ((*(char***)v->page->content)[y][x] == 'O')
		draw_prev_o(piece, v);
	else if ((*(char***)v->page->content)[y][x] == 'o')
		draw_curr_o(piece, v);
	else if ((*(char***)v->page->content)[y][x] == 'X')
		draw_prev_x(piece, v);
	else if ((*(char***)v->page->content)[y][x] == 'x')
		draw_curr_x(piece, v);
	else if ((*(char***)v->page->content)[y][x] == '.')
		draw_empty(piece, v);
	if (SDL_BlitSurface(piece, NULL, v->surf, &info) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
	SDL_FreeSurface(piece);
}

void	check_piece(t_visu *v)
{
	int y;
	int x;

	y = 0;
	while (y < v->nb_y)
	{
		x = 0;
		while (x < v->nb_x)
		{
			draw_piece(y, x, v);
			x++;
		}
		y++;
	}
}
