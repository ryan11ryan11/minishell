# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 15:25:56 by jbober            #+#    #+#              #
#    Updated: 2024/10/24 14:32:39 by junhhong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS := -Wall -Werror -Wextra -g #-fsanitize=address
HEADERS = src/minishell.h
RM = rm -rf
INCLUDE = -lreadline

SRC_DIR = ./src
OBJ_DIR = ./obj

FILES = parse/parse\
		parse/parsefk1\
		parse/parsefk1b\
		parse/parsefk2\
		parse/parsefk2b\
		parse/parsefk4\
		parse/parsefk5\
		parse/parsefk5b\
		parse/parsefk5c\
		parse/ut1ls\
		parse/ut2ls\
		parse/ut3ls\
		parse/ut4ls\
		free\
		error\
		minishell\
		execution/src/ft_atoi\
		execution/src/utils\
		execution/src/builtin_control\
		execution/src/envlistclear\
		execution/src/envp_list_maker\
		execution/src/ft_cd\
		execution/src/ft_echo\
		execution/src/ft_echo2\
		execution/src/ft_env\
		execution/src/ft_export\
		execution/src/ft_export2\
		execution/src/ft_export3\
		execution/src/ft_pwd\
		execution/src/ft_unset\
		execution/src/heredoc_signal\
		execution/src/pipe_utils\
		execution/src/pipe_utils2\
		execution/src/pipe_utils3\
		execution/src/pipe_utils4\
		execution/src/pipe_utils5\
		execution/src/pipe_utils6\
		execution/src/pipe_utils7\
		execution/src/pipe_utils8\
		execution/src/pipe_utils9\
		execution/src/pipe_utils10\
		execution/src/pipe\
		execution/src/pipe2\
		execution/src/signal\
		execution/src/util\
		execution/src/ft_lib\
		execution/src/ft_lib2\
		execution/src/ft_lib3\


SRC = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(FILES)))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	