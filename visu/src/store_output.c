/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 04:47:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/04 19:28:17 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "get_next_line.h"

static int	check_line(char *str)
{
	int index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] != '.' && str[index] != 'x' && str[index] != 'X' &&
			str[index] != 'o' && str[index] != 'O')
			return (0);
	}
	return (1);
}

void		add_map(t_visu *v, char ***map)
{
	char	**copy;
	int		index;
	t_list	*new;

	if (!(copy = ft_memalloc(sizeof(char*) * (v->nb_y + 1))))
		ft_exit(v);
	index = 0;
	while (index < v->nb_y)
	{
		if (!(copy[index] = ft_strdup((*map)[index])))
			ft_exit(v);
		(ft_strlen(copy[index]) != (size_t)v->nb_x) ? ft_exit(v) : 0;
		!(check_line(copy[index])) ? ft_exit(v) : 0;
		index++;
	}
	index = 0;
	while (index < v->nb_y)
	{
		free((*map)[index]);
		index++;
	}
	free(*map);
	new = list_new(&copy, sizeof(size_t));
	list_append(&v->page, new);
}

int			skip_piece(t_visu *v)
{
	char	*line;
	char	**temp;
	int		index;
	int		ret;

	(get_next_line(0, &line) < 0) ? ft_exit(v) : 0;
	(!(temp = ft_strsplit(line, ' '))) ? ft_exit(v) : 0;
	free(line);
	index = -1;
	ret = 1;
	if (!ft_str_is_digit(temp[1]))
	{
		ft_splitdel(temp);
		ft_exit(v);
	}
	while (++index < ft_atoi(temp[1]) + 3)
	{
		(get_next_line(0, &line) < 0) ? ft_exit(v) : 0;
		if (ft_strstr(line, "[0, 0]"))
		{
			ret = special_case(v);
			break ;
		}
		free(line);
	}
	ft_splitdel(temp);
	return ((ret == FINISH) ? FINISH : 1);
}

void		continue_parse(t_visu *v)
{
	int		index;
	char	**map;
	char	*line;
	int		ret;

	ret = 1;
	while (1)
	{
		if (!(map = ft_memalloc(sizeof(char*) * v->nb_y)))
			ft_exit(v);
		index = -1;
		while (++index < v->nb_y)
		{
			if (get_next_line(0, &line) < 0)
				ft_exit(v);
			(ft_strlen(line) < 5) ? ft_exit(v) : 0;
			if (!(map[index] = ft_strdup(line + 4)))
				ft_exit(v);
			free(line);
		}
		add_map(v, &map);
		ret = skip_piece(v);
		if (ret == FINISH)
			break ;
	}
}

void		init_parse(t_visu *v)
{
	int		index;
	char	**map;
	char	*line;

	if (get_next_line(0, &line) < 0)
		ft_exit(v);
	free(line);
	if (!(map = ft_memalloc(sizeof(char*) * v->nb_y)))
		ft_exit(v);
	index = 0;
	while (index < v->nb_y)
	{
		if (get_next_line(0, &line) < 0)
			ft_exit(v);
		(ft_strlen(line) < 5) ? ft_exit(v) : 0;
		if (!(map[index] = ft_strdup(line + 4)))
			ft_exit(v);
		index++;
		free(line);
	}
	add_map(v, &map);
	skip_piece(v);
}
