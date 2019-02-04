/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 03:20:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/02 04:27:48 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		init_sdl(t_visu *v)
{
	int	success;

	success = 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		success = 0;
	else
	{
		v->window = SDL_CreateWindow("THE FILLER", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, v->w_width, v->w_height,
				SDL_WINDOW_SHOWN);
		if (v->window == NULL)
			success = 0;
		else
			v->surf = SDL_GetWindowSurface(v->window);
	}
	return (success);
}
