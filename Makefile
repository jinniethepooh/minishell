NAME = minishell

SRC_DIR = srcs/
OBJ_DIR = objs/

SRC_FILE = mini_cmd_utils mini_exec mini_exec_utils mini_free mini_env \
	mini_builtin mini_builtin_func mini_redir main \
	mini_lexer mini_signal mini_exit utils
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

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm
NORM = Norminette

all: compile $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIB_BINARY)

bonus: all

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(HDR_INC) $(LIB_INC) -c $< -o $@

compile: lib
	@mkdir -p $(OBJ_DIR)

lib:
	$(foreach f, $(LIB_DIR), make -C $f;)

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
	$(foreach f, $(LIB_DIR), make fclean -C $f;)

re: fclean all

.PHONY: all clean fclean re compile lib norm bonus
