#include "../minishell.h"

void	print_data(t_redirect *data_array, int nb_cmds)
{
	int	i;

	i = 0;
	while (i < nb_cmds)
	{
		ft_printf("\n\n-------\n");
		ft_printf("Commande %d\n", i);
		ft_printf("Infile : %s\n", data_array[i].infile.name);
		ft_printf("Outfile : %s\n", data_array[i].outfile.name);
		ft_printf("Infile fd : %d\n", data_array[i].infile.fd);
		ft_printf("Outfile fd : %d\n", data_array[i].outfile.fd);
		print_argv(data_array[i].argv);
		ft_printf("-------\n\n");
		i++;
	}
}

int	is_token_redirection(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT
			|| tmp->type == TOKEN_DOUBLE_REDIRECT_OUT
			|| tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*shell;

	shell = (t_minishell *)ft_calloc(sizeof(t_minishell), 1);
	if (!shell)
		return (NULL);
	shell->env = ft_copy_tab(envp);
	if (!shell->env)
		return (NULL);
	shell->tokens = NULL;
	shell->input = NULL;
	shell->history_index = 0;
	shell->nb_cmds = 0;
	shell->redirect_array = NULL;
	shell->exit_status = 0;
	shell->is_single_quote = 0;
	shell->is_plus_equal = 0;
	shell->env_size = 0;
	shell->syntax_error = 0;
	init_history(shell->history);
	return (shell);
}
