#include "minishell.h"

static void    echo_off(void)
{
        struct termios  tio;

        tcgetattr(STDIN_FILENO, &tio);
        tio.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

static void     respond_sig_child(int signum, siginfo_t *info, void *context)
{
        (void) context;
        (void) info;

        if (signum == SIGINT)
                g_var.exit_status = EXIT_SIGINT;
}

void     signal_settings_child(void)
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = respond_sig_child;
	sigaction(SIGINT, &sact, NULL);
}

static void     respond_sig(int signum, siginfo_t *info, void *context)
{
        (void) context;
        (void) info;

        if (signum == SIGINT)
        {
                g_var.exit_status = EXIT_SIGINT;
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

void    signal_settings(void)
{
        struct sigaction	sact;

        sigemptyset(&sact.sa_mask);
        sact.sa_flags = SA_SIGINFO;
        sact.sa_sigaction = respond_sig;
        sigaction(SIGINT, &sact, NULL);
        sigaction(SIGQUIT, &sact, NULL);
        echo_off();
}