CC = cc
CFLAGS = -Wall -Wextra -Werror
COMMON = builtin ft_echo ft_cd ft_pwd ft_export ft_env ft_unset
NAME = test
LIBDIR = ./libft

#COMOBJ = $(addprefix $(COMDIR)/, $(addsuffix .o, $(COMMON)))
OBJ = $(addsuffix .o, $(COMMON))
AR = ar -rcs

all : $(NAME)

# -I means that headerfile is located at current directory
%.o : %.c minishell.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME) : $(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)


# Make lib
# @ : target
# < : first dependency
# -L : lib file is located at current DIR
clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

libclean :
	$(MAKE) -C $(LIBDIR)/ clean

libfclean :
	$(MAKE) -C $(LIBDIR)/ fclean

.PHONY : all clean fclean re