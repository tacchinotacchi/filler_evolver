/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 08:18:23 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/05 00:12:31 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	draw_curr_x(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 252, 118, 106)) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
}

void	draw_prev_x(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 157, 55, 68)) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
}

void	draw_curr_o(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 251, 199, 72)) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
}

void	draw_prev_o(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 217, 159, 60)) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
}

void	draw_empty(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 0, 0, 0)) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
}
