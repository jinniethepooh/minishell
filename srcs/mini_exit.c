#include "minishell.h"

void    mini_exit(void)
{
        printf("... exiting hell, "BRED"to a deeper!\n"RES);
        free(g_var.prompt);
        free(g_var.from_rl);
        mini_free(&g_var);
        exit(EXIT_SUCCESS);
}
