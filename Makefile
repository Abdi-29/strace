NAME = ft_strace
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj
INCLUDE = -I includes
SRC_DIR = src
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILES = main.c
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(SRC:.c=.o))
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)	

clean:
	$(MAKE) -C $(LIBFT_DIR)/ fclean
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re	