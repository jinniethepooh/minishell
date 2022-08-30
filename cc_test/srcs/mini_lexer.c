#include "minishell.h"

void    get_cmd(t_shell *shell)
{
        int i;
        // char *test;

        i = 0;
        if (shell->from_rl)
        {
            // to be split pipe first
            // then lexer from each part
            // shell->command = malloc(sizeof(t_command));
            // shell->command->cmd_args = (char **)malloc(sizeof(char *));
            while (shell->from_rl[i])
            {
                while (ft_isspecial(shell->from_rl[i]) && shell->from_rl[i])
                    ++i;
                while (!ft_isspecial(shell->from_rl[i]) && shell->from_rl[i])
                {
                    printf("%c", shell->from_rl[i]);
                    ++i;
                }
                printf("\n");
            }
        }
}