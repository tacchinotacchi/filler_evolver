/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 08:18:23 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/02 05:52:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	draw_curr_x(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 4, 45, 249)) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
}

void	draw_prev_x(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 4, 236, 230)) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
}

void	draw_curr_o(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 249, 4, 4)) < 0)
	{
		SDL_FreeSurface(piece);
		ft_exit(v);
	}
}

void	draw_prev_o(SDL_Surface *piece, t_visu *v)
{
	if (SDL_FillRect(piece, NULL, SDL_MapRGB(piece->format, 249, 189, 4)) < 0)
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
