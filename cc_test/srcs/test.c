#include "minishell.h"

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int     ft_wcount(const char *s, char c);

void    echo_off(void)
{
        struct termios termio;

        tcgetattr(STDIN_FILENO, &termio);
        termio.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &termio);
}

static void respond_sig(int signum, siginfo_t *info, void *context)
{
        (void) context;
        (void) info;
        if (signum == SIGINT)
        {
            ioctl(STDIN_FILENO, TIOCSTI, "\n");
            rl_on_new_line();
            rl_replace_line("", 0);
        }
        else if (signum == SIGQUIT)
        {
            rl_on_new_line();
            rl_redisplay();
        }
}

int     main(int argc, char **argv)
{
        struct sigaction	sact;
        char    test[PATH_MAX];
        char    **dir;
        char    *prompt;
        char    *command;
        int     cwd;

        command = NULL;
        (void)argc;
        (void)argv;

        
        sigemptyset(&sact.sa_mask);
        sact.sa_flags = SA_SIGINFO;
        sact.sa_sigaction = respond_sig;
        sigaction(SIGINT, &sact, NULL);
        sigaction(SIGQUIT, &sact, NULL);

        while (1)
        {
            echo_off();
            // to have prompt (and separate fn)
            dir = ft_split(getcwd(test, sizeof(test)), '/');
            cwd = ft_wcount(test, '/') - 1;
            prompt = ft_strjoin(ft_strjoin(BCYN"tinyshell "CRESET, dir[cwd]), YEL" $ "CRESET);
            
            command = readline(prompt);
            // printf("command = |%s|\n", command);
            if (command == NULL)
            {
                // to have free + exit function
                printf("bye\n");
                free(prompt);
                free(command);
                exit(EXIT_SUCCESS);
            }
        }
        free(prompt);
        return (EXIT_SUCCESS);
}