#include "minishell.h"

static void     get_history(void)
{
        int     i;

        i = 0;
        while (g_var.from_rl[i])
        {
                if (!ft_isspace(g_var.from_rl[i]))
                {
                        add_history(g_var.from_rl);
                        return ;
                }
                ++i;
        }
}

static void     get_prompt(void)
{
        int     cwd_count;
        int     i;

        g_var.dir = ft_split(getcwd(g_var.cwd, sizeof(g_var.cwd)), '/');
        cwd_count = ft_wcount(g_var.cwd, '/') - 1;
        g_var.prompt = ft_strjoin(ft_strjoin(BCYN"tinyshell "RES, g_var.dir[cwd_count]), YEL" $ "RES);
        i = -1;
        while (g_var.dir[++i])
                free(g_var.dir[i]);
        free(g_var.dir);
}

static void    shell_init(int argc, char **argv, char **env)
{
        (void) argc;
        (void) argv;
        signal_settings();
        g_var.prompt = NULL;
        g_var.from_rl = NULL;
        g_var.command = NULL;
        g_var.dir = NULL;
        g_var.env = dup_2d(env);
}

int     main(int argc, char **argv, char **env)
{
        shell_init(argc, argv, env);
        while (1)
        {
                get_prompt();
                g_var.from_rl = readline(g_var.prompt);
                if (g_var.from_rl == NULL)
                        mini_exit();
                get_history();
                if (ft_isvalid_quotes())
                {
                        get_cmd();
                        g_var.exit_status = mini_exec(&g_var);
                }
        }
        mini_exit();
        return (EXIT_SUCCESS);
}

// ----- for linked list print ----- //
// int i = 0;
// t_command *test;
// while (test)
// {
//      i = 0;
//      while (test->cmd_args[i])
//      {
//              printf("|%s|\n", test->cmd_args[i]);
//              ++i;
//      }
//      test = test->next;
// }
// ----- end linked list print ----- //