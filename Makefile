NAME = minishell

SRC_DIR = srcs/
OBJ_DIR = objs/

SRC_FILE = mini_cmd_utils mini_exec mini_exec_utils \
	mini_builtin mini_builtin_func mini_builtin_func2 \
	mini_export mini_export_utils mini_redir mini_env \
	mini_lexer mini_lexer_move mini_lexer_split_1 mini_lexer_split_2 \
	mini_cleaner mini_input_checker mini_utils \
	mini_init mini_exit mini_signal mini_main
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILE)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILE)))

HDR_DIR = includes/
HDR_FILE = minishell
HDR_INC = $(addprefix -I, $(HDR_DIR))
HDRS = $(addprefix $(HDR_DIR), $(addsuffix .h, $(HDR_FILE)))

LIB_DIR = libft/
LIB_INC = $(addprefix -I, $(addsuffix $(HDR_DIR), $(LIB_DIR)))
LIB_BINARY = -lreadline -Llibft -lft

ifeq ($(shell uname), Linux)
LIB_INC += -I/usr/include/
endif

ifeq ($(shell uname), Darwin)
LIB_INC += -I/usr/local/opt/readline/include
LIB_BINARY += -L/usr/local/opt/readline/lib
endif

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm
NORM = Norminette

all: lib $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIB_BINARY)
	@echo "/// ----- tik tak boom ------ ///"

bonus: all

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(HDR_INC) $(LIB_INC) -c $< -o $@

lib:
	@make -C $(LIB_DIR)

norm:
	$(foreach f, $(LIB_DIR), make norm -C $f;)
	@$(NORM) -R CheckForbiddenSourceHeader $(SRC_DIR) | grep -v Norme -B1 || true
	@$(NORM) -R CheckDefine $(HDRS) | grep -v Norme -B1 || true

clean:
	$(RM) -rf $(OBJ_DIR)
	$(foreach f, $(LIB_DIR), make clean -C $f;)

fclean:
	$(RM) -rf $(OBJ_DIR)
	$(RM) -f $(NAME)
	$(RM) -rf $(NAME).dSYM
	$(foreach f, $(LIB_DIR), make fclean -C $f;)

re: fclean all

.PHONY: all clean fclean re lib norm bonus
