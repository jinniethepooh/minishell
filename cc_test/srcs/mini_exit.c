#include "minishell.h"

void    mini_exit(t_shell *shell)
{
        printf("... exiting hell, "BRED"to a deeper!\n"RES);
        free(shell->prompt);
        free(shell->command);
        exit(EXIT_SUCCESS);
}
