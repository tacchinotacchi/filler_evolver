/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mapsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 04:12:04 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/01 19:49:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "get_next_line.h"

static void	verify_header(t_visu *v)
{
	char	*line;

	if (get_next_line(0, &line) < 1)
		ft_exit_parsing(v, line);
	if (ft_strcmp("# -------------- VM  version 1.1 ------------- #", line))
		ft_exit_parsing(v, line);
	if (get_next_line(0, &line) < 1)
		ft_exit_parsing(v, line);
	if (ft_strcmp("#                                              #", line))
		ft_exit_parsing(v, line);
	if (get_next_line(0, &line) < 1)
		ft_exit_parsing(v, line);
	if (ft_strcmp("# 42 / filler VM Developped by: Hcao - Abanlin #", line))
		ft_exit_parsing(v, line);
	if (get_next_line(0, &line) < 1)
		ft_exit_parsing(v, line);
	if (ft_strcmp("#                                              #", line))
		ft_exit_parsing(v, line);
	if (get_next_line(0, &line) < 1)
		ft_exit_parsing(v, line);
	if (ft_strcmp("# -------------------------------------------- #", line))
		ft_exit_parsing(v, line);
}

void		get_mapsize(t_visu *v)
{
	char	*line;
	char	**temp;
	int		index;

	line = NULL;
	index = -1;
	verify_header(v);
	while (++index < 4)
	{
		(get_next_line(0, &line) < 1) ? ft_exit_parsing(v, line) : 0;
		free(line);
	}
	(get_next_line(0, &line) < 1) ? ft_exit_parsing(v, line) : 0;
	if (ft_strstr(line, "Plateau"))
	{
		if (!(temp = ft_strsplit(line, ' ')))
			ft_exit(v);
		v->nb_y = ft_atoi(temp[1]);
		v->nb_x = ft_atoi(temp[2]);
		free(line);
	}
	(v->nb_y <= 0 || v->nb_x <= 0) ? ft_exit(v) : 0;
}
