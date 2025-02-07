/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:45:57 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 15:57:41 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_argv(char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 2);
		ft_putchar_fd(' ', 2);
		i++;
	}
}

void	fatal_error(char *message)
{
	ft_putstr_fd("\033[31m░░      ░░░  ░░░░  ░░░      ░░\n\033[0m", 2);
	ft_putstr_fd("\033[32m▒  ▒▒▒▒  ▒▒  ▒  ▒  ▒▒  ▒▒▒▒  ▒\n\033[0m", 2);
	ft_putstr_fd("\033[33m▓  ▓▓▓▓  ▓▓        ▓▓  ▓▓▓▓  ▓\n\033[0m", 2);
	ft_putstr_fd("\033[34m█  ████  ██   ██   ██  ████  █\n\033[0m", 2);
	ft_putstr_fd("\033[35m██      ███  ████  ███      ██\n\033[0m", 2);
	ft_printf("\nWhat's this? \033[4;36m%s\033[0m? Oh no!\n", message);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	syntax_error(char *message, char **argv, int argc, int code)
{
	(void)argc;
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("cmd: ", 2);
	print_argv(argv, argc);
	ft_putchar_fd('\n', 2);
	if (code > 0)
	{
		ft_putstr_fd("arg: ", 2);
		ft_putstr_fd(argv[code], 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putchar_fd('\n', 2);
}
