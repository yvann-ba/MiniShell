/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:00:09 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/14 12:42:26 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_signal = 0;

void increment_shlvl(char **env)
{
    int i = 0;
    int shlvl;
    char *shlvl_str;
    char *new_shlvl_str;
    char *shlvl_itoa;
    int new_shlvl_assigned;

    new_shlvl_assigned = 0;
    while (env[i] != NULL)
    {
        if (strncmp(env[i], "SHLVL=", 6) == 0)
        {
            shlvl_str = env[i] + 6; // Skip "SHLVL="
            shlvl = ft_atoi(shlvl_str);
            shlvl++;
            shlvl_itoa = ft_itoa(shlvl);
            new_shlvl_str = ft_strjoin("SHLVL=", shlvl_itoa);
            free(shlvl_itoa); // Free the memory allocated by ft_itoa
            if (new_shlvl_str != NULL)
            {
                free(env[i]);
                env[i] = new_shlvl_str;
                new_shlvl_assigned = 1;
                break;
            }
        }
        i++;
    }
    if (!new_shlvl_assigned)
        free(new_shlvl_str);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;
	int			exit_status;

	rl_catch_signals = 0;
	exit_status = 0;
	(void)argc;
	(void)argv;
	shell = init_minishell(envp);
	if (!shell)
		return (1);
	init_signal_handlers();
	increment_shlvl(shell->env);
	read_input(shell);
	exit_status = shell->exit_status;
	free_minishell(shell);
	return (exit_status);
}
