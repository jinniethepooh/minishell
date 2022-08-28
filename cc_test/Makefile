NAME	= tiny_shell
SRCS	= srcs/mini_main.c \
			srcs/mini_signal.c \
			srcs/mini_exit.c \
			srcs/utils.c
OBJS	= $(SRCS:.c=.o)
INCS	= ../includes/

LIBFT	= libft
DIRFT	= ../$(LIBFT)/
BINFT	= -lft -L$(DIRFT) -I$(DIRFT)includes

LIBRL	= readline
# consider to make changes
DIRRL	= /usr/local/
BINRL	= -l$(LIBRL) -L$(DIRRL)lib -I$(DIRRL)include

CFLAGS	= gcc -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME):
	@make -C $(DIRFT)
	@$(CFLAGS) $(BINRL) $(BINFT) -I $(INCS) $(SRCS) -o $(NAME)
	@echo "/// ----- tik tak boom ------ ///"

clean:
	@rm -rf $(OBJS)
	@make clean -C $(DIRFT)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM
	@make fclean -C $(DIRFT)

re: fclean all

.PHONY: all clean fclean re