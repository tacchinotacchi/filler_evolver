SRCS = filler.c \
	free_and_error.c \
	main.c \
	parser_util.c \
	parser.c \
	populate_maps.c
INCLUDES = libft/includes/libft.h \
	includes/filler.h
OBJS = $(patsubst %.c,obj/%.o,$(SRCS))

TESTS_SRCS =
TESTS = $(patsubst %.c,tests/%.test,$(TESTS_SRCS))
TESTS_DBG_FOLDERS = $(TESTS:.test=.test.dSYM)

CC = gcc
ifndef CFLAGS_WARNINGS
export CFLAGS_WARNINGS = 1
export CFLAGS := $(CFLAGS) -Wall -Wextra -Werror -std=c89
endif
INCLUDE_FOLDERS = -Iincludes/ -Ilibft/includes
LIBRARY_PATHS = -L. -Llibft

.PHONY: clean fclean re all

all: $(OBJS) | obj

LIBFT_PREFIX = libft
include libft/Makefile.mk

obj:
	mkdir -p obj
	mkdir -p pool
	mkdir -p pool/params

pool/%.filler: pool/params/%.c $(OBJS) $(LIBFT_NAME) | obj
	gcc $(CFLAGS) $(INCLUDE_FOLDERS) $(OBJS) $< -o $@ $(LIBRARY_PATHS) -lft

obj/%.o: src/%.c $(INCLUDES) | obj
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) -o $@ -c $<

tests/%.test: tests/%.c $(NAME) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(INCLUDE_FOLDERS) $(LIBRARY_PATHS) -o $@ $< -lft

clean:
	rm -rf $(TESTS_DBG_FOLDERS)
	rm -f $(TESTS)
	rm -f $(OBJS)
	rm -rf obj
	rm -f $(LIBFT_OBJS)
	rm -rf libft/obj

fclean: clean
	rm -f $(LIBFT_NAME)
	rm -f $(FTPRINTF_NAME)
	rm -rf obj
	rm -rf pool

re: fclean
	$(MAKE) all
