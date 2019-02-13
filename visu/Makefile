# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/02 06:44:37 by jaelee            #+#    #+#              #
#    Updated: 2019/02/09 00:10:52 by jaelee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visualizer
SRCS = check_piece.c \
	skip_piece_check.c \
	draw_grid.c \
	get_mapsize.c \
	get_windowsize.c \
	init.c \
	main.c \
	sdl_draw.c \
	special_case.c \
	store_output.c \
	visualizer_util.c
INCLUDES = ../libft/includes/libft.h \
		./includes/visu.h
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE_FOLDERS = -I./includes -I../libft/includes `pkg-config --cflags sdl2`
LIBRARY_PATH = -L ../libft
.PHONY: clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(NAME): $(OBJS) ../libft/libft.a
	$(CC) $(LIBRARY_PATH) -lft `pkg-config --libs sdl2` $^ -o $@

obj:
	mkdir -p obj

obj/%.o : src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -c $< -o $@

../libft/libft.a: ../libft/includes/libft.h
	make -C ../libft

clean:
	make -C ../libft clean
	rm -f $(OBJS)
	rm -rf obj

fclean: clean
	make -C ../libft fclean
	rm -f $(NAME)

re: fclean
	make all
