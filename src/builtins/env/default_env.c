/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:12:23 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/14 14:15:40 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void set_pwd_if_not_defined(char ***env)
{
    int i = 0;
    int pwd_assigned = 0;

    while ((*env)[i] != NULL)
    {
        if (strncmp((*env)[i], "PWD=", 4) == 0)
        {
            pwd_assigned = 1;
            break;
        }
        i++;
    }
    if (!pwd_assigned)
    {
        char *cwd = getcwd(NULL, 0);
        if (cwd != NULL)
        {
            char *pwd_str = ft_strjoin("PWD=", cwd);
            free(cwd); 
            if (pwd_str != NULL)
            {
                int env_size = 0;
                while ((*env)[env_size] != NULL)
                    env_size++;
                char **new_env = realloc(*env, (env_size + 2) * sizeof(char *));
                if (new_env != NULL)
                {
                    new_env[env_size] = pwd_str;
                    new_env[env_size + 1] = NULL;
                    *env = new_env;
                }
                else
                    free(pwd_str);
            }
        }
    }
}

void increment_shlvl(char ***env)
{
    int i = 0;
    int shlvl;
    char *shlvl_str;
    char *new_shlvl_str;
    char *shlvl_itoa;
    int new_shlvl_assigned;

    new_shlvl_assigned = 0;
    while ((*env)[i] != NULL)
    {
        if (strncmp((*env)[i], "SHLVL=", 6) == 0)
        {
            shlvl_str = (*env)[i] + 6;
            shlvl = ft_atoi(shlvl_str);
            shlvl++;
            shlvl_itoa = ft_itoa(shlvl);
            new_shlvl_str = ft_strjoin("SHLVL=", shlvl_itoa);
            free(shlvl_itoa); 
            if (new_shlvl_str != NULL)
            {
                free((*env)[i]);
                (*env)[i] = new_shlvl_str;
                new_shlvl_assigned = 1;
                break;
            }
        }
        i++;
    }
    if (!new_shlvl_assigned)
    {
        new_shlvl_str = ft_strdup("SHLVL=1");
        if (new_shlvl_str != NULL)
        {
            int env_size = 0;
            while ((*env)[env_size] != NULL)
                env_size++;
            char **new_env = realloc(*env, (env_size + 2) * sizeof(char *));
            if (new_env != NULL)
            {
                new_env[env_size] = new_shlvl_str;
                new_env[env_size + 1] = NULL;
                *env = new_env;
            }
            else
                free(new_shlvl_str);
        }
    }
}
