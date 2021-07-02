NAME = Fdf

SRC = src/main.c

CC = clang

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

INC = includes

LDFLAGS = -L libs/minilibx-linux -L libs/libft
LDLIBS = -lmlx -lft -lXext -lX11 -lm
OFLAGS = $(CFLAGS_L) -O2 -flto -funroll-loops -ftree-vectorize

CFLAGS = -Wall -Wextra -g3 -I include -isystem libs

all : $(NAME)

.PHONY : libft minilibx

libft :
	$(MAKE) -C libs/libft bonus

minilibx :
	$(MAKE) -C libs/minilibx-linux

$(NAME) : libft minilibx $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)


debug : libft minilibx $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS) 

sanitize : libft minilibx $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)


opti : libft minilibx
	$(CC) -o $(NAME) $(SRC) $(OFLAGS)

clean :
	rm -f $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C libs/libft $@
	$(MAKE) -C libs/minilibx-linux $@

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME)-debug
	rm -f $(NAME)-opti
	rm -rf *.dSYM
	rm -rf *.bmp
	$(MAKE) -C libs/libft $@

re : fclean all
