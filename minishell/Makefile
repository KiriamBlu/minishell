NAME := minishell
LIBFT_NAME = libft.a

SRCS =  ./sources/minishell.c \
		./sources/minishell1.c \
		./sources/minishell2.c \
		./sources/main.c \
		./sources/utils/utils0.c \
		./sources/builtins/builtins0.c \
		./sources/lexer/lexer1.c  \
		./sources/builtins/builtins1.c \
		./sources/builtins/builtins3.c \
		./sources/builtins/builtins4.c \
		./sources/utils/utils1.c \
		./sources/utils/utils2.c \
		./sources/lexer/lexer0.c \
		./sources/lexer/lexer2.c \
		./sources/lexer/lexer3.c \
		./sources/lexer/lexer4.c \
		./sources/lexer/lexer5.c \
		./sources/builtins/builtins2.c \
		./sources/utils/utils3.c \
		./sources/signals/signals0.c \
		./sources/executer/executer01.c \
		./sources/executer/executer02.c \
		./sources/utils/utils4.c \
		./sources/utils/utils5.c \

OBJS = ${SRCS:.c=.o}

LIBFT_DIR := ./libft/
INC_DIR := ./minishell.h
EXE_DIR = ./

CC := cc
GCC := gcc
CFLAGS := -Wall -Wextra -Werror #-fsanitize=address -g3
MV := mv -f
RM := rm -f
LDFLAGS	:= -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

%.o: %.c
	$(GCC)  $(CFLAGS) -c $< -I $(INC_DIR) -o $@ 

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(GCC) -lreadline $(CFLAGS) $(LDFLAGS) -o $(NAME)  $^ -I $(INC_DIR)

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

#cd minishell-tester && bash test.sh