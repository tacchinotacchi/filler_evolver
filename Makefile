# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/04 00:44:52 by jaelee            #+#    #+#              #
#    Updated: 2019/03/03 19:15:02 by aamadori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = jaelee.filler
SRCS = main.c \
	   learnable_params.c \
	   parser.c \
	   parser_util.c \
	   filler.c \
	   populate_maps.c \
	   free_and_error.c
INCLUDES = ./includes/filler.h \
		./libft/includes/libft.h
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))
CC = gcc
ifndef CFLAGS_WARNING
export CFLAGS_WARNING = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror 
endif
INCLUDE_FOLDERS = -I./includes -I./libft/includes
LIBRARY_PATH = -Llibft

.PHONY: clean fclean re
.SUFFIXES: .c .o

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATH) -lft $(OBJS) -o $@

obj:
	mkdir -p obj

obj/%.o : src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -c $< -o $@

libft/libft.a: libft/includes/libft.h
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS)
	rm -rf obj

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean
	make all
