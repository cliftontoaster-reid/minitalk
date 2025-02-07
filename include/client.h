/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:52:07 by lfiorell          #+#    #+#             */
/*   Updated: 2025/02/07 15:53:50 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	syntax_error(char *message, char **argv, int argc, int code);
void	fatal_error(char *message);

int		is_valid_pid(char *pid);
int		is_valid_cmd(int argc, char **argv);
