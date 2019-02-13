/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 08:56:03 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/08 09:34:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H
# include "libft.h"
# include "list.h"
# include <SDL.h>
# include <stdlib.h>
# define FINISH 0

typedef struct	s_visu
{
	SDL_Window	*window;
	SDL_Surface	*surf;
	SDL_Event	event;
	int			nb_x;
	int			nb_y;
	int			w_width;
	int			w_height;
	int			square;
	int			origin_x;
	int			origin_y;
	int			width_line;
	int			height_line;
	t_list		*page;
}				t_visu;

void			get_mapsize(t_visu *v);
void			get_windowsize(t_visu *v);

void			init_parse(t_visu *v);
void			continue_parse(t_visu *v);
int				skip_piece(t_visu *v);
void			skip_piece_check(t_visu *v, char **temp);
int				special_case(t_visu *v);
void			add_map(t_visu *v, char ***map);

int				init_sdl(t_visu *v);
void			draw_grid_verti(t_visu *v);
void			draw_grid_horiz(t_visu *v);
void			check_piece(t_visu *v);
void			draw_piece(int y, int x, t_visu *v);
void			draw_curr_x(SDL_Surface *piece, t_visu *v);
void			draw_prev_x(SDL_Surface *piece, t_visu *v);
void			draw_curr_o(SDL_Surface *piece, t_visu *v);
void			draw_prev_o(SDL_Surface *piece, t_visu *v);
void			draw_empty(SDL_Surface *piece, t_visu *v);
void			key_event(t_visu *v);

void			free_content(void *content, size_t content_size);
void			free_pages(t_visu *v);
void			ft_exit(t_visu *v);
void			ft_exit_parsing(t_visu *v, char *line);
void			ft_close(t_visu *v);

#endif
