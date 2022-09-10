#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131
# define CHILD_PROC 0

void    signal_settings_child(void);
void    signal_settings(void);

#endif