/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:55:23 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 17:04:06 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 199506L
#include "brand.h"
#include "libft.h"
#include "sig.h"
#include <signal.h>
#include <unistd.h>

static t_sig	g_sig;

static char	binary_to_char(int *binary)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (i < 8)
	{
		c += binary[i] << (7 - i);
		i++;
	}
	return (c);
}

static void	shandler(int signum, siginfo_t *info, void *ucontext)
{
	char	c;

	(void)ucontext;
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		g_sig.binary[g_sig.i] = (signum == SIGUSR1);
		g_sig.i++;
	}
	else
		return ;
	if (g_sig.i == 8)
	{
		g_sig.i = 0;
		c = binary_to_char(g_sig.binary);
		if (c == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(c, 1);
	}
	kill(info->si_pid, signum);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	print_toast();
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = shandler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	g_sig.i = 0;
	while (1)
		pause();
}
