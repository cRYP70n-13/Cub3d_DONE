SRC = cub3d.c ft_strtrim.c get_next_line_utils.c main.c manage1.c mapstuff.c screenshot.c tools.c buildwall.c ft_split.c get_next_line.c helptools.c helpers.c manage.c player_manager.c raycats.c sprite.c textures.c

MAND = $(SRC)

NAME = lib.a

all:	$(NAME)

$(NAME) :
	@gcc -Wall -Werror -Wextra -c $(SRC)
	@ar -rc  lib.a $(SRC:.c=.o)
	@ranlib lib.a
	@gcc -Wall -Werror -Wextra -I /usr/local/include lib.a -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o cub3D libmlx.dylib

bonus:
	@gcc -Wall -Werror -Wextra -c $(SRC) $(MAND)
	@ar -rc  lib.a $(SRC:.c=.o)
	@ranlib lib.a

clean:
	@rm -f $(SRC:.c=.o) $(MAND:.c=.o) cub3D

fclean:	clean
	@rm -f $(NAME)

re:		fclean all