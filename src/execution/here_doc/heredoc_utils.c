/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:55:45 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/17 13:57:10 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_fork_error(t_minishell *shell)
{
	perror("Error:\nduring fork_here_doc");
	free_minishell(shell);
	shell->exit_status = 1;
	exit(EXIT_FAILURE);
}
