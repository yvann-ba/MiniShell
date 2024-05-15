#include "../minishell.h"

void	debug_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		ft_printf("Type de Token: %d, quote: %d, Valeur: %s\n",
			current->type, current->quote_type, current->value);
		current = current->next;
	}
}

static	void	execute_input_commands(t_minishell *shell)
{
	if (is_token_redirection(shell->tokens) == 0)
	{
		fill_t_redirect(shell);
		if (check_builtins(shell->redirect_array[0].argv[0]) == 1)
			execute_builtins(ft_strlen_map(shell->redirect_array->argv),
				shell->redirect_array->argv, shell);
		else
		{
			shell->redirect_array->argv[0] = check_command_existence(
					shell->redirect_array[0].argv[0], shell->env);
			if (shell->redirect_array->argv[0] == NULL)
			{
				ft_putstr_fd("minishell: command not found\n", 2);
				shell->exit_status = 127;
				return ;
			}
			execute_command_shell(shell);
		}
	}
	else
	{
		fill_t_redirect(shell);
		execute_command_shell(shell);
	}
}

void	process_input(t_minishell *shell)
{
	add_history(shell->input);
	if (shell->history[shell->history_index] != NULL)
		free(shell->history[shell->history_index]);
	shell->history[shell->history_index] = ft_strdup(shell->input);
	shell->history_index = (shell->history_index + 1) % MAX_HISTORY_SIZE;
	shell->tokens = tokenize(shell->input, shell->env, shell);
	debug_print_tokens(shell->tokens);
	if (shell->tokens)
		execute_input_commands(shell);
}

int	execute_builtins(int argc, char **argv, t_minishell *shell)
{
	t_token	*tokens;

	if (!argv || !argv[0])
		return (1);
	tokens = convert_argv_to_list(argc, argv);
	if (ft_strncmp(tokens->value, "exit", 4) == 0)
		ft_exit(tokens, shell);
	else if (ft_strncmp(tokens->value, "echo", 4) == 0)
		ft_echo(tokens, &shell->exit_status, shell);
	else if (ft_strncmp(tokens->value, "cd", 2) == 0)
		ft_cd(tokens, shell->env, &shell->exit_status);
	else if (ft_strncmp(tokens->value, "pwd", 3) == 0)
		ft_pwd(&shell->exit_status);
	else if (ft_strncmp(tokens->value, "export", 6) == 0)
		ft_export(tokens, &(shell->env), &shell->exit_status, shell);
	else if (ft_strncmp(tokens->value, "unset", 5) == 0)
		ft_unset(tokens, &shell->env, &shell->exit_status);
	else if (ft_strncmp(tokens->value, "env", 3) == 0
		&& tokens->value[3] == '\0')
		ft_env(shell->env, &shell->exit_status);
	return (1);
}

void	handle_input(t_minishell *shell)
{
	if (ft_strcmp(shell->input, "") == 0)
		return ;
	process_input(shell);
	if (ft_strcmp(shell->input, "exit") == 0)
	{
		free_minishell(shell);
		exit(shell->exit_status);
	}
}
