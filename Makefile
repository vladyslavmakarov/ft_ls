NAME = ft_ls

SRC = 	btree_helpers_1.c btree_helpers_2.c dir_info_1.c\
		dir_info_2.c display_1.c display_2.c display_3.c helpers_1.c\
		helpers_2.c main.c options_init_1.c options_init_2.c recursion_1.c\
		recursion_2.c user_directories.c user_errors.c user_inputs.c

FLAG = gcc -c -g -Wall -Werror -Wextra

OBJ = ${SRC:.c=.o}

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME):
	cd ./libft && make && cd ..
	$(FLAG) $(SRC)
	gcc $(OBJ) -o $(NAME) $(LIBFT)

clean:
	/bin/rm -f $(OBJ)
	cd libft && make clean

fclean: clean
	/bin/rm -f $(NAME)
	cd libft && make fclean
	
re: fclean all
	cd libft && make re