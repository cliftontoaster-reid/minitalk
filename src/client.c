/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:55:25 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 16:30:12 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brand.h"
#include "client.h"
#include <libft.h>
#include <sig.h>
#include <unistd.h>

static t_sig	g_sig;

static void	chandler(int signum)
{
	if (signum == SIGUSR1 || signum == SIGUSR2)
		g_sig.i++;
	if (g_sig.i == 8)
	{
		g_sig.i = 0;
		g_sig.j++;
		if (g_sig.str[g_sig.j] == '\0')
		{
			ft_putchar_fd('\n', 1);
			exit(EXIT_SUCCESS);
		}
		char_to_binary(g_sig.str[g_sig.j], g_sig.binary);
	}
	send_bit(g_sig.pid, g_sig.binary[g_sig.i]);
}

int	main(int argc, char **argv)
{
	print_toast();
	if (!is_valid_cmd(argc, argv))
		return (1);
	g_sig.str = argv[2];
	g_sig.i = 0;
	g_sig.j = 0;
	g_sig.pid = ft_atoi(argv[1]);
	signal(SIGUSR1, chandler);
	signal(SIGUSR2, chandler);
	char_to_binary(g_sig.str[g_sig.j], g_sig.binary);
	send_bit(g_sig.pid, g_sig.binary[g_sig.i]);
	while (1)
		pause();
}
