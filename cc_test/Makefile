NAME	= tiny_shell
SRCS	= srcs/test.c \
			srcs/utils.c \
			srcs/ft_split.c
OBJS	= $(SRCS:.c=.o)
INCS	= ../includes/

LIBRL	= readline
# consider to make changes
DIRRL	= /usr/local/
BINRL	= -l$(LIBRL) -L$(DIRRL)lib -I$(DIRRL)include

CFLAGS	= gcc -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME):
	@$(CFLAGS) $(BINRL) -I $(INCS) $(SRCS) -o $(NAME)
	@echo "/// ----- tik tak boom ------ ///"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re