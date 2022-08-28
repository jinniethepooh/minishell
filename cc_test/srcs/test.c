#include "minishell.h"

/*
#include <termios.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
*/

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
        
        (void)argc;
        (void)argv;
        getcwd(test, sizeof(test));
        
        sigemptyset(&sact.sa_mask);
        sact.sa_flags = SA_SIGINFO;
        sact.sa_sigaction = respond_sig;
        sigaction(SIGINT, &sact, NULL);
        sigaction(SIGQUIT, &sact, NULL);

        while (1)
        {
            echo_off();
            if (readline(test) == NULL)        // to handle having sth in the line & suddenly ctrl+D
            {
                printf("bye\n");
                exit(EXIT_SUCCESS);
            }
        }
        return (EXIT_SUCCESS);
}