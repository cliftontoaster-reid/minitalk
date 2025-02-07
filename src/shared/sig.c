/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:19:02 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 15:46:12 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	char_to_binary(unsigned char c, int *binary)
{
	size_t	i;

	i = 0;
	while (i < 8)
	{
		binary[i] = (c >> (7 - i)) & 1;
		i++;
	}
}

void	send_bit(pid_t pid, int bit)
{
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
}

/*
 * Convert a character to its binary representation
 * and return a dynamically allocated array of 8 ints.
 */
int	*char_to_binary_arr(char c)
{
	int	i;
	int	*binary;

	binary = malloc(sizeof(int) * 8);
	if (!binary)
		return (NULL);
	i = 0;
	while (i < 8)
	{
		binary[i] = (c >> (7 - i)) & 1;
		i++;
	}
	return (binary);
}
