/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 21:23:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/13 12:08:43 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"

static int	parse_piece(t_filler *pc, char **split, int fd)
{
	int		index;
	int		cnt;

	pc->pc_h = ft_atoi(split[1]);
	pc->pc_w = ft_atoi(split[2]);
	if (!(pc->pc_h > 0 && pc->pc_w > 0))
		return (FT_FAIL);
	index = 0;
	cnt = 0;
	if (!(pc->piece = ft_memalloc(sizeof(char*) * (pc->pc_h + 1))))
		return (FT_FAIL);
	while (index < pc->pc_h)
	{
		if ((get_next_line(fd, &(pc->piece[index]))) < 1)
			return (FT_FAIL);
		if (pc->pc_w != (int)ft_strlen(pc->piece[index]))
			return (FT_FAIL);
		if (ft_strchr(pc->piece[index], '*'))
			cnt++;
		index++;
	}
	if (cnt < 1)
		return (FT_FAIL);
	return (FT_SUCCESS);
}

static int	store_map(t_filler *pc, int index, int fd)
{
	char	*line;

	if (get_next_line(fd, &line) < 1)
		return (FT_FAIL);
	if (ft_strlen(line) < 5)
	{
		free(line);
		return (FT_FAIL);
	}
	if (!(pc->map[index] = ft_strdup(line + 4)))
	{
		free(line);
		return (FT_FAIL);
	}
	if (pc->map_w != (int)ft_strlen(pc->map[index]))
	{
		free(line);
		return (FT_FAIL);
	}
	free(line);
	return (FT_SUCCESS);
}

static int	parse_map(t_filler *pc, char **split, int fd)
{
	int		index;
	char	*line;

	pc->map_h = ft_atoi(split[1]);
	pc->map_w = ft_atoi(split[2]);
	if (pc->map_h < 1 && pc->map_w < 1)
	{
		ft_splitdel(split);
		return (FT_FAIL);
	}
	index = 0;
	if (!(pc->map = ft_memalloc(sizeof(char*) * (pc->map_h + 1))))
		return (FT_FAIL);
	if (get_next_line(fd, &line) < 1)
		return (FT_FAIL);
	free(line);
	while (index < pc->map_h)
	{
		if (store_map(pc, index, fd) == FT_FAIL)
			return (FT_FAIL);
		index++;
	}
	return (FT_SUCCESS);
}

int			parse_input2(t_filler *pc, int fd)
{
	char	*line;
	char	**split;

	if (get_next_line(fd, &line) < 1)
		return (FT_FAIL);
	if (!(split = ft_strsplit(line, ' ')))
	{
		free(line);
		return (FT_FAIL);
	}
	free(line);
	if (verify_split(split) == FT_FAIL)
		return (FT_FAIL);
	if (parse_piece(pc, split, fd) == FT_FAIL)
		return (FT_FAIL);
	ft_splitdel(split);
	return (FT_SUCCESS);
}

int			parse_input(t_filler *pc, int fd)
{
	char	*line;
	char	**split;

	if (get_next_line(fd, &line) < 1)
	{
		free(line);
		return (FT_FAIL);
	}
	if (!(split = ft_strsplit(line, ' ')))
	{
		free(line);
		return (FT_FAIL);
	}
	free(line);
	if (verify_split(split) == FT_FAIL)
	{
		ft_splitdel(split);
		return (FT_FAIL);
	}
	if (parse_map(pc, split, fd) == FT_FAIL)
	{
		ft_splitdel(split);
		return (FT_FAIL);
	}
	ft_splitdel(split);
	if (pc->start_pos == 0)
		if (get_start_pos(pc) == FT_FAIL)
			return (FT_FAIL);
	return (parse_input2(pc, 0));
}
