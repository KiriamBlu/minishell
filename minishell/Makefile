NAME := minishell
LIBFT_NAME = libft.a

SRCS =  ./sources/minishell.c \
		./sources/utils/utils0.c \
		./sources/builtins/builtins0.c \
		./sources/lexer/lexer1.c  \
		./sources/builtins/builtins1.c \
		./sources/utils/utils1.c \
		./sources/utils/utils2.c \
		./sources/lexer/lexer0.c \
		./sources/builtins/builtins2.c \
		./sources/utils/utils3.c \
		./sources/lexer/lexer3.c \

OBJS = ${SRCS:.c=.o}

LIBFT_DIR := ./libft/
INC_DIR := ./minishell.h
EXE_DIR = ./

CC := cc
GCC := gcc
CFLAGS := -Wall -Wextra -g #-Werror
MV := mv -f
RM := rm -f

%.o: %.c
	$(GCC)  $(CFLAGS) -c $< -I $(INC_DIR) -o $@ 

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(GCC) -lreadline -o $(NAME)  $^ -I $(INC_DIR)

$(LIBFT_DIR)$(LIBFT_NAME): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re

