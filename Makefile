NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -fsanitize=address -g3 -O0 -Iinc
# CFLAGS  = -Wall -Wextra -Werror -g3 -O0 -Iinc

SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = inc/
LIB_DIR     = lib/
LIBFT_DIR   = $(LIB_DIR)/libft

LIBFT_A     = $(LIBFT_DIR)/libft.a
LIBFT_LIB   = -L$(LIBFT_DIR) -lft

SRC    = main.c \
		  built_in/cd.c \
		  built_in/cd_utils.c \
		  built_in/cleanup.c \
		  built_in/echo.c \
		  built_in/exit.c \
		  built_in/export.c \
		  built_in/export_utils.c \
		  built_in/print_env.c \
		  built_in/pwd.c \
		  built_in/unset.c \
		  env/parse_env.c \
		  env/find_env.c \
		  execution/check_built_in.c \
		  execution/child_process.c \
		  execution/multiple_commands.c \
		  execution/single_command.c \
		  execution/reaping_children.c \
		  expansion/expand.c \
		  expansion/expand_env.c \
		  expansion/expand_quote.c \
		  expansion/word_splitting.c \
		  expansion/expand_heredoc.c \
		  input/get_input.c \
		  lexer/create_tokens.c \
		  lexer/is_operator.c \
		  lexer/tokenise.c \
		  lexer/token_list_utils.c \
		  lexer/validate_tokens.c \
		  parser/create_exe.c \
		  parser/create_processes.c \
		  parser/here_doc.c \
		  parser/make_argv.c \
		  parser/open_infiles.c \
		  parser/open_outfiles.c \
		  parser/assign_process.c \
		  parser/create_command.c \
		  signals/signal_handlers.c \
		  signals/ms_rl_hooks.c \

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
