#ifndef MINI_LEXER_H
# define MINI_LEXER_H

/* mini_lexer.c */
void	get_cmd(void);

/* mini_lexer_split_1.c - pipe split */
char	**pipe_split(char const *s, char c);

/* mini_lexer_split_2.c - split command */
char	**cmd_split(char const *s, char c);

/* mini_cleaner.c - main cleaner */
char	**cmd_cleaner(char **arr);

/* mini_lexer_move.c - mover */
int		get_var_skip(char c);
int		get_cmd_move(char *s, int flag);

#endif
