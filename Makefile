NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3 -O0 -Iinc

SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = inc/
LIB_DIR     = lib/
LIBFT_DIR   = $(LIB_DIR)/libft

LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_LIB   = -L$(LIBFT_DIR) -lft

SRC    = main.c \
		  env/parse_env.c \
		  input/get_input.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJS    = $(SRC:.c=.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJS))

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@echo "Compiling libft..."
	$(MAKE) -sC $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	@echo "Compiling $(NAME)..."
	$(CC) $(CFLAGS) $(OBJECTS) -I$(INC_DIR) $(LIBFT_LIB) -lreadline -o $(NAME)

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJECTS)
	$(MAKE) -sC $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning executable and libft.a..."
	rm -f $(NAME)
	$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
