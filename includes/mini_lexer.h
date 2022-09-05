#ifndef MINI_LEXER
# define MINI_LEXER


typedef struct s_cmd_loop
{
    int     i;
    char    *dst;
    char    *tmp;
}   t_cmd_loop;

/* mini_lexer.c */
void    get_cmd(void);

/* mini_lexer_split_1.c - pipe split */
char	**pipe_split(char const *s, char c);

/* mini_lexer_split_2.c - split command */
char	**cmd_split(char const *s, char c);

/* mini_cleaner_cmd.c - main cleaner */
char    **cmd_cleaner(char **arr);
void    *cmd_cleaner_loop(char *src, int flag);

/* mini_cleaner_quotes.c - quote cleaner */
char    *cmd_cleaner_quotes(char *src);

/* mini_cleaner_var.c - var cleaner */
char    *cmd_cleaner_var(char *src);

/* mini_lexer_move.c - mover */
int     get_var_skip(char c);
int     get_cmd_move(char *s, int flag);

/* mini_utils_2.c - quote handling helper ---> to move to minishell.h */
int 	ft_loop_until(const char *s, char c, int flag);
int		ft_isvalid_quotes(void);

#endif