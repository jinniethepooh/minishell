/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lexer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:39:49 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/13 19:39:51 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_LEXER_H
# define MINI_LEXER_H

/* mini_lexer.c */
void	get_cmd(void);

/* mini_lexer_split_1.c - pipe split */
char	**pipe_split(char *cpy, char c);

/* mini_lexer_split_2.c - split command */
char	**cmd_split(char *cpy, char c);

/* mini_cleaner.c - main cleaner */
char	**cmd_cleaner(char **arr);

/* mini_lexer_move.c - mover */
int		get_var_skip(char c);
int		get_cmd_move(char *s, int flag);

#endif
