NAME	= tiny_shell
SRCS	= srcs/test.c
OBJS	= $(SRCS:.c=.o)

INCS	= ../includes/
CFLAGS	= gcc -Wall -Werror -Wextra -g
RLLIB	= readline

# consider to make changes
RLDIR	= /usr/local/

all: $(NAME)

$(NAME):
	@$(CFLAGS) -l$(RLLIB) -L$(RLDIR)lib -I$(RLDIR)include -I $(INCS) $(SRCS) -o $(NAME)
	@echo "/// ----- tik tak boom ------ ///"

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re