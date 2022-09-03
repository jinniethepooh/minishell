#ifndef MINI_LEXER
# define MINI_LEXER

/* mini_lexer_utils_3 - clean output from cmd_split */


/* mini_lexer_utils_2 - quote handler */
int 	ft_loop_until(const char *s, char c, int flag);
int		ft_isvalid_quotes(void);
char    **cmd_cleaner(char **arr);

/* mini_lexer_utils */
char	**pipe_split(char const *s, char c);
char	**cmd_split(char const *s, char c);

/* mini_lexer */
void    get_cmd(void);


#endif