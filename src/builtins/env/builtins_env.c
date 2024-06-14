/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:30:21 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/14 12:02:57 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	remove_env_var(char *var, char ***env)
{
	int		i;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(var);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, var_len) \
		== 0)
		{
			free((*env)[i]);
			while ((*env)[i + 1])
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_unset(t_token *tokens, char ***env, int *exit_status)
{
	t_token	*current;
	int		found;
	t_token	*tokens_copy;

	found = 0;
	tokens_copy = tokens->next;
	current = tokens->next;
	while (current)
	{
		found |= remove_env_var(current->value, env);
		current = current->next;
	}
	if (found)
		*exit_status = 0;
	if (tokens_copy && tokens_copy->value[0] == '-')
		*exit_status = 2;
}

static int	check_and_print_error(t_token *arg_lst, int *exit_status)
{
	if (arg_lst->next && arg_lst->next->value)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		*exit_status = 127;
		return (1);
	}
	return (0);
}

static void	print_environment(char **env, int *exit_status)
{
    int		i;
    char	*current_pwd;
    char	*new_pwd;
    int		new_pwd_assigned;

    current_pwd = getcwd(NULL, 0);
    if (current_pwd != NULL)
    {
        new_pwd = ft_strjoin("PWD=", current_pwd);
        if (new_pwd != NULL)
        {
            i = 0;
            new_pwd_assigned = 0;
            while (env[i] != NULL)
            {
                if (strncmp(env[i], "PWD=", 4) == 0)
                {
                    free(env[i]);
                    env[i] = new_pwd;
                    new_pwd_assigned = 1;
                    break ;
                }
                i++;
            }
            if (!new_pwd_assigned)
                free(new_pwd);
        }
        free(current_pwd);
    }
    environment_trail(env, exit_status);
}

void	ft_env(t_token *arg_lst, char **env, int *exit_status)
{
	if (check_and_print_error(arg_lst, exit_status))
		return ;
	print_environment(env, exit_status);
}
