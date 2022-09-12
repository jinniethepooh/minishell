#include "minishell.h"

static void	echo_off(void)
{
	struct termios	tio;

	tcgetattr(STDIN_FILENO, &tio);
	tio.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

int	signal_exit_child(int signum)
{
	if (signum == SIGINT)
		return (EXIT_SIGINT);
	return (EXIT_SIGQUIT);
}

void	signal_settings_child(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

static void	respond_sig(int signum, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (signum == SIGINT)
	{
		g_var.sig_detect = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signum == SIGQUIT)
	{
		return ;
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}

void	signal_settings(void)
{
	struct sigaction	sact;

	if (g_var.sig_detect)
		g_var.exit_status = EXIT_SIGINT;
	g_var.sig_detect = 0;
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = respond_sig;
	sigaction(SIGINT, &sact, NULL);
	sigaction(SIGQUIT, &sact, NULL);
	echo_off();
}
