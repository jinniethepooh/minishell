#ifndef MINI_LEXER
# define MINI_LEXER


/* mini_lexer_utils_1 - pipe split */
char	**pipe_split(char const *s, char c);

/* mini_lexer_utils_2 - quote handler */
int 	ft_loop_until(const char *s, char c, int flag);
int		ft_isvalid_quotes(void);

/* mini_lexer_utils_3 - clean output from cmd_split */
char	**cmd_split(char const *s, char c);
char    **cmd_cleaner(char **arr);

/* mini_lexer_utils_5 - quote cleaner */
char    *cmd_cleaner_quotes(char *src);

/* mini_lexer_utils_6 - var cleaner */
char    *cmd_cleaner_var(char *src);

/* mini_lexer_utils_7 - redir cleaner */
char    *cmd_cleaner_redir(char *src);

/* mini_lexer */
void    get_cmd(void);


#endif