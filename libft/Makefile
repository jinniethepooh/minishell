NAME = libft.a

SRC_FILE = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen \
	ft_memset ft_bzero ft_memcpy ft_memmove ft_strlcpy ft_strlcat ft_toupper \
	ft_tolower ft_strchr ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr \
	ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim ft_split \
	ft_itoa ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd \
	ft_putnbr_fd

SRC_DIR = srcs/
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILE)))

OBJ_DIR = objs/
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILE)))

HDR_DIR = includes/
HDR_FILE = libft.h
HDRS = $(addprefix $(HDR_DIR), $(HDR_FILE))
HDR_INC = $(addprefix -I, $(HDR_DIR))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rc
RM = rm
NORM = Norminette

all: compile $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $@ $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) $(HDR_INC) -c $< -o $@

compile:
	@mkdir -p $(OBJ_DIR)

norm:
	@$(NORM) -R CheckForbiddenSourceHeader $(SRCS) | grep -v Norme -B1 || true
	@$(NORM) -R CheckDefine $(HDRS) | grep -v Norme -B1 || true

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re compile norm
