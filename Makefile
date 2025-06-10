NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -fsanitize=address -g3 -O0 -Iinc

SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = inc/
LIB_DIR     = lib/
LIBFT_DIR   = $(LIB_DIR)/libft

LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_LIB   = -L$(LIBFT_DIR) -lft

SRCS    = ./src/main.c \
		  ./src/env/parse_env.c \
		  ./src/env/utilits.c \

OBJS    = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

$(OBJ_DIR)%.o : $(SRCS)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@echo "Compiling libft..."
	$(MAKE) -sC $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -I$(LIBFT_DIR) $(LIBFT_LIB) -o $(NAME)

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS)
	$(MAKE) -sC $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning executable and libft.a..."
	rm -f $(NAME)
	$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
