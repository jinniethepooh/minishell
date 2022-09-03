#ifndef MINI_LEXER
# define MINI_LEXER

/* mini_lexer_utils_3 - clean output from cmd_split */


/* mini_lexer_utils_2 - quote handler */
int 	ft_loop_quotes(const char *s, char q);
int		ft_isvalid_quotes(void);
void    clean_pipe_split(char **tmp);

/* mini_lexer_utils */
char	**pipe_split(char const *s, char c);

/* mini_lexer */
void    get_cmd(void);


#endif