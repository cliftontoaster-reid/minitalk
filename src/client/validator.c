/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:51:46 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 15:53:04 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "libft.h"
#include <errno.h>
#include <signal.h>

int	is_valid_pid(char *pid)
{
	while (*pid)
	{
		if (!ft_isdigit(*pid))
			return (0);
		pid++;
	}
	return (1);
}

int	is_pid_real(int argc, char **argv)
{
	int		pid;
	char	*pid_str;

	pid_str = argv[1];
	pid = ft_atoi(pid_str);
	if (kill(pid, 0) == 0)
		return (1);
	else if (errno == ESRCH)
	{
		syntax_error("No such process", argv, argc, 1);
		return (0);
	}
	else if (errno == EPERM)
	{
		fatal_error("Permission denied");
		return (1);
	}
	return (-1);
}

int	is_valid_cmd(int argc, char **argv)
{
	if ((argc != 3))
	{
		syntax_error("Invalid number of arguments", argv, argc, 0);
		return (0);
	}
	if (!is_valid_pid(argv[1]))
	{
		syntax_error("Invalid PID", argv, argc, 1);
		return (0);
	}
	if (!is_pid_real(argc, argv))
		return (0);
	return (1);
}
