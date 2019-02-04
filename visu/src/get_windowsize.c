/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_windowsize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 04:29:48 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/28 08:14:24 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	set_windowsize(t_visu *v, int width, int height, int square)
{
	v->w_width = width;
	v->w_height = height;
	v->square = square;
}

static void	taller_window(t_visu *v)
{
	if (v->nb_y <= 20)
		set_windowsize(v, 100 + 100 + (v->nb_y * 25) + v->nb_y, 120 + 100 +
				(v->nb_y * 25) + v->nb_y, 25);
	else if (v->nb_y <= 50)
		set_windowsize(v, 100 + 100 + (v->nb_y * 15) + v->nb_y, 120 + 100 +
				(v->nb_y * 15) + v->nb_y, 15);
	else if (v->nb_y <= 100)
		set_windowsize(v, 100 + 100 + (v->nb_y * 6) + v->nb_y, 120 + 100 +
				(v->nb_y * 6) + v->nb_y, 6);
	else
		ft_exit(v);
}

void		get_windowsize(t_visu *v)
{
	if (v->nb_x >= v->nb_y)
	{
		if (v->nb_x <= 20)
			set_windowsize(v, 120 + 100 + (v->nb_x * 25) + v->nb_x, 100 + 100 +
					(v->nb_x * 25) + v->nb_x, 25);
		else if (v->nb_x <= 50)
			set_windowsize(v, 120 + 100 + (v->nb_x * 15) + v->nb_x, 100 + 100 +
					(v->nb_x * 15) + v->nb_x, 15);
		else if (v->nb_x <= 100)
			set_windowsize(v, 120 + 100 + (v->nb_x * 6) + v->nb_x, 100 + 100 +
					(v->nb_x * 6) + v->nb_x, 6);
		else
			ft_exit(v);
	}
	else
		taller_window(v);
}
