/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:04:27 by lfiorell          #+#    #+#             */
/*   Updated: 2024/11/19 08:34:13 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_send_signal(int pid, char c)
{
	int	arr[8];
	int	n;
	int	i;

	n = c;
	i = 7;
	while (i >= 0)
	{
		if (n == 0 || (n & 1) == 0)
			arr[i] = 0;
		else if ((n & 1) == 1)
			arr[i] = 1;
		if (n > 0)
			n >>= 1;
		i--;
	}
	while (++i < 8)
	{
		if (arr[i] == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		write(1, "Args error", 10);
	else
	{
		pid = ft_atoi(argv[1]);
		while (argv[2] && *argv[2])
			ft_send_signal(pid, *argv[2]++);
		ft_send_signal(pid, '\n');
	}
	return (0);
}
