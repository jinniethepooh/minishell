#include "minishell.h"

static void     get_history(t_shell *shell)
{
        int     i;

        i = 0;
        while (shell->command[i])
        {
                if (!ft_isspace(shell->command[i]))
                {
                        add_history(shell->command);
                        return ;
                }
                ++i;
        }
}

static void     get_prompt(t_shell *shell)
{
        int     cwd_count;
        int     i;

        shell->dir = ft_split(getcwd(shell->cwd, sizeof(shell->cwd)), '/');
        cwd_count = ft_wcount(shell->cwd, '/') - 1;
        shell->prompt = ft_strjoin(ft_strjoin(BCYN"tinyshell "RES, shell->dir[cwd_count]), YEL" $ "RES);
        i = -1;
        while (shell->dir[++i])
                free(shell->dir[i]);
        free(shell->dir);
}

static void    shell_init(t_shell *shell)
{
        signal_settings();
        // shell->fd_in = 0;    shall be added
        // shell->fd_out = 0;   shall be added
        shell->prompt = NULL;
        shell->command = NULL;
        shell->dir = NULL;
}

int     main(void)
{
        t_shell shell;

        shell_init(&shell);
        while (1)
        {
            get_prompt(&shell);
            shell.command = readline(shell.prompt);
            if (shell.command == NULL)
                mini_exit(&shell);
            get_history(&shell);
        }
        free(shell.prompt);
        return (EXIT_SUCCESS);
}