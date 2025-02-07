/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:12:50 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 15:43:38 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <signal.h>
# include <sys/types.h>

typedef struct s_sig
{
	int		binary[8];
	char	*str;
	int		i;
	int		j;
	int		pid;
}			t_sig;

void		char_to_binary(unsigned char c, int *binary);
void		send_bit(pid_t pid, int bit);

void		handler(int signum, siginfo_t *info, void *ucontext);

#endif
