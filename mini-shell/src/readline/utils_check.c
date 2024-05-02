#include "../minishell.h"

int	check_builtins(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0
		&& cmd[3] == '\0')
		return (1);
	else
		return (0);
}

int	check_redirect_in_to_pipe(t_token *tokens)
{
	t_token *current;

	current = tokens;
	current = current->next;
	if (current == NULL)
		return (0);
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE)
			return (0);
		else if (current->type == TOKEN_REDIRECT_IN)
			return (1);
		current = current->next;
	}
	return (0);
}

