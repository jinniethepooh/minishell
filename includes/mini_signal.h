#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131

int     signal_exit_child(int signum);
void    signal_settings_child(int mode);
void    signal_settings(void);

#endif