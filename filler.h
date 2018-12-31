/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 23:03:21 by jaelee            #+#    #+#             */
/*   Updated: 2018/12/30 00:06:27 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# define OPEN 0
# define ME -1
# define OP -2
typedef struct	s_filler
{
	int		pc_h;
	int		pc_w;
	int		map_h;
	int		map_w;
	int		put_y;
	int		put_x;
	int		sum; //TODO set sum to INT_MAX
	char	**piece;
	char	**map;
	int		**nmap;
	char	me;
	char	op;
}				t_filler;

void			parse_input(t_filler *pc, int fd);
void			parse_map(t_filler *pc, char *info, int fd);
void			parse_piece(t_filler *pc, char *info, int fd);
void			get_player(t_filler *pc, int fd);
void			error(t_filler *pc);
void			free_struct(t_filler *pc);
void			process_map(t_filler *pc);
int				ft_atoi_ptr(char **str);
void			print_coord(int y, int x);
void			sum(t_filler *pc, int map_y, int map_x);
void			check_piece(t_filler *pc, int map_y, int map_x);
int				filler(t_filler *pc);
void			create_nmap(t_filler *pc);
#endif
