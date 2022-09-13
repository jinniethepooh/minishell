/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:46:45 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/13 19:46:46 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131

int		signal_exit_child(int signum);
void	signal_settings_child(int mode);
void	signal_settings(void);

#endif
