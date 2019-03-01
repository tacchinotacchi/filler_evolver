/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 09:52:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/01 22:46:28 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "array.h"
#include "libft.h"

#define FIRST_CONV_SIZE
#define SECOND_CONV_SIZE

typedef struct s_coord
{
	int	x;
	int y;
}				t_coord;


typedef struct s_box
{
	t_coord	coord;
	t_coord	size;
}				t_box;

int     not_case_sensitive(char a, char b)
{
    if (a >= 'A' && a <= 'Z')
        a -= 'A' - 'a';
    if (b >= 'A' && b <= 'Z')
        b -= 'A' - 'a';
    return (a == b);
}

void		propagate_wallmap(t_filler *pc)
{
	int		update;
	t_coord coords;
	const float base = 0.6f;

	update = 1;
	while (update)
	{
		update = 0;
		coords.y = 0;
		while (coords.y < pc->map_h)
		{
			coords.x = 0;
			while (coords.x < pc->map_w)
			{
				if (coords.y + 1 < pc->map_h
					&& !not_case_sensitive(pc->map[coords.y + 1][coords.x], pc->me)
					&& pc->wall_map[coords.y + 1][coords.x] * base > pc->wall_map[coords.y][coords.x])
				{
					pc->wall_map[coords.y][coords.x] = pc->wall_map[coords.y + 1][coords.x] * base;
					update = 1;
				}
				if (coords.y - 1 >= 0
					&& !not_case_sensitive(pc->map[coords.y - 1][coords.x], pc->me)
					&& pc->wall_map[coords.y - 1][coords.x] * base > pc->wall_map[coords.y][coords.x])
				{
					pc->wall_map[coords.y][coords.x] = pc->wall_map[coords.y - 1][coords.x] * base;
					update = 1;
				}
				if (coords.x + 1 < pc->map_w
					&& !not_case_sensitive(pc->map[coords.y][coords.x + 1], pc->me)
					&& pc->wall_map[coords.y][coords.x + 1] * base > pc->wall_map[coords.y][coords.x])
				{
					pc->wall_map[coords.y][coords.x] = pc->wall_map[coords.y][coords.x + 1] * base;
					update = 1;
				}
				if (coords.x - 1 >= 0
					&& !not_case_sensitive(pc->map[coords.y][coords.x - 1], pc->me)
					&& pc->wall_map[coords.y][coords.x - 1] * base > pc->wall_map[coords.y][coords.x])
				{
					pc->wall_map[coords.y][coords.x] = pc->wall_map[coords.y][coords.x - 1] * base;
					update = 1;
				}
				coords.x++;
			}
			coords.y++;
		}
	}
}

void		propagate_nmap(t_filler *pc)
{
	int		update;
	t_coord coords;

	update = 1;
	while (update)
	{
		update = 0;
		coords.y = 0;
		while (coords.y < pc->map_h)
		{
			coords.x = 0;
			while (coords.x < pc->map_w)
			{
				if (coords.y + 1 < pc->map_h
					&& !not_case_sensitive(pc->map[coords.y + 1][coords.x], pc->me)
					&& pc->nmap[coords.y + 1][coords.x] - 1 > pc->nmap[coords.y][coords.x])
				{
					pc->nmap[coords.y][coords.x] = pc->nmap[coords.y + 1][coords.x] - 1;
					update = 1;
				}
				if (coords.y - 1 >= 0
					&& !not_case_sensitive(pc->map[coords.y - 1][coords.x], pc->me)
					&& pc->nmap[coords.y - 1][coords.x] - 1 > pc->nmap[coords.y][coords.x])
				{
					pc->nmap[coords.y][coords.x] = pc->nmap[coords.y - 1][coords.x] - 1;
					update = 1;
				}
				if (coords.x + 1 < pc->map_w
					&& !not_case_sensitive(pc->map[coords.y][coords.x + 1], pc->me)
					&& pc->nmap[coords.y][coords.x + 1] - 1 > pc->nmap[coords.y][coords.x])
				{
					pc->nmap[coords.y][coords.x] = pc->nmap[coords.y][coords.x + 1] - 1;
					update = 1;
				}
				if (coords.x - 1 >= 0
					&& !not_case_sensitive(pc->map[coords.y][coords.x - 1], pc->me)
					&& pc->nmap[coords.y][coords.x - 1] - 1 > pc->nmap[coords.y][coords.x])
				{
					pc->nmap[coords.y][coords.x] = pc->nmap[coords.y][coords.x - 1] - 1;
					update = 1;
				}
				coords.x++;
			}
			coords.y++;
		}
	}
}

struct	s_walls {
	char	top;
	char	bottom;
	char	left;
	char	right;
};

int			wall_condition(t_filler *pc, const struct s_walls *walls, t_coord coords)
{
	if (walls->top && coords.y == 0)
		return (1);
	if (walls->bottom && coords.y == pc->map_h - 1)
		return (1);
	if (walls->left && coords.x == 0)
		return (1);
	if (walls->right && coords.x == pc->map_w - 1)
		return (1);
	return (0);
}

void		disable_wall(t_filler *pc, struct s_walls *walls, t_coord coords)
{
	if (coords.y == 0)
		walls->top = 0;
	if (coords.y == pc->map_h - 1)
		walls->bottom = 0;
	if (coords.x == 0)
		walls->left = 0;
	if (coords.x == pc->map_w - 1)
		walls->right = 0;
}

void		update_nmap(t_filler *pc)
{
	t_coord	coords;
	struct s_walls walls;
	const float	learnable = 1.5f;

	walls = (struct s_walls){1, 1, 1, 1};
	coords.y = 0;
	while (coords.y < pc->map_h)
	{
		coords.x = 0;
		while (coords.x < pc->map_w)
		{
			if (wall_condition(pc, &walls, coords))
			{
				if (not_case_sensitive(pc->map[coords.y][coords.x], pc->me))
					disable_wall(pc, &walls, coords);
			}
			if (not_case_sensitive(pc->map[coords.y][coords.x], pc->op))
				pc->nmap[coords.y][coords.x] = OPEN;
			coords.x++;
		}
		coords.y++;
	}
	coords.y = 0;
	while (coords.y < pc->map_h)
	{
		coords.x = 0;
		while (coords.x < pc->map_w)
		{
			if (wall_condition(pc, &walls, coords))
				pc->wall_map[coords.y][coords.x] = OPEN * learnable;
			coords.x++;
		}
		coords.y++;
	}
}

float	check_move(t_filler *pc, t_coord base_coords)
{
	t_coord	coords;
	int		possible;
	float	score;

	if (base_coords.x + pc->pc_w > pc->map_w || base_coords.y + pc->pc_h > pc->map_h)
		return (-1);
	possible = 0;
	score = 0;
	coords = base_coords;
	while (coords.y < base_coords.y + pc->pc_h)
	{
		coords.x = base_coords.x;
		while (coords.x < base_coords.x + pc->pc_w)
		{
			if (coords.y < pc->map_h && coords.x < pc->map_w
				&& pc->piece[coords.y - base_coords.y][coords.x - base_coords.x] == '*')
			{
				if (not_case_sensitive(pc->map[coords.y][coords.x], pc->op))
					return (-1);
				if (not_case_sensitive(pc->map[coords.y][coords.x], pc->me))
				{
					if (possible)
						return (-1);
					possible = 1;
				}
				score += pc->nmap[coords.y][coords.x] + pc->wall_map[coords.y][coords.x];
			}
			coords.x++;
		}
		coords.y++;
	}
	return (possible ? score : -1.f);
}

int			best_move(t_filler *pc)
{
	t_coord	coords;
	t_coord	best_pos;
	float	best_pos_value;
	float	heuristic;

	coords.y = 0;
	best_pos_value = -1.f;
	best_pos = (t_coord){0, 0};
	while (coords.y < pc->map_h)
	{
		coords.x = 0;
		while (coords.x < pc->map_w)
		{
			heuristic = check_move(pc, coords);
			if (heuristic > best_pos_value)
			{
				best_pos = coords;
				best_pos_value = heuristic;
			}
			coords.x++;
		}
		coords.y++;
	}
	pc->put_x = best_pos.x;
	pc->put_y = best_pos.y;
	return (best_pos_value);
}

int			filler(t_filler *pc)
{
	update_nmap(pc);
	propagate_nmap(pc);
	propagate_wallmap(pc);
	if (best_move(pc) < 0)
		return (-1);
	return (1);
}