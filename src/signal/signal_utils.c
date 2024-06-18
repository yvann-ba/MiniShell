/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:12:59 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/18 09:31:39 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_without_prefix(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_signal = 130;
}

void	handle_sigint_here_doc(int sig)
{
	(void)sig;
	g_exit_signal = 1;
	remember_fd_here_doc(NULL, NULL);
	exit(130);
}
