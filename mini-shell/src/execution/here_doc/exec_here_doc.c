#include "../../minishell.h"

void	write_here_doc_in_file(char *content, int fd, t_minishell *shell)
{
	if (fd < 0)
	{
		perror("Error:\nduring write_here_doc_in_file\n");
		shell->exit_status = 1;
		return ;
	}
	if (content == NULL)
	{
		shell->exit_status = 1;
		return ;
	}
	write(fd, content, ft_strlen(content));
}

static char	*generate_and_assign_filename(t_minishell *shell)
{
	char	*filename;
	char	*final_path;

	filename = generate_random_filename();
	final_path = ft_calloc(sizeof(char),
			(ft_strlen(filename) + ft_strlen("/tmp/") + 1));
	if (final_path == NULL)
	{
		perror("Error:\n during write_here_doc_in_file\n");
		free(filename);
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	final_path = ft_strncpy (final_path, "/tmp/", ft_strlen("/tmp/"));
	final_path = ft_strcat (final_path, filename);
	free(filename);
	return (final_path);
}

static t_file	fork_here_doc(char *delimiter, t_minishell *shell,
	int replace_env, t_file **tab_here_doc)
{
	pid_t	pid;
	int		status;
	t_file	here_doc;

	here_doc.name = generate_and_assign_filename(shell);
	here_doc.fd = open_file_and_handle_errors(shell, here_doc);
	shell->tab_here_doc = tab_here_doc;
	pid = fork();
	if (pid == 0)
	{
		handle_here_doc(shell, here_doc, delimiter, replace_env);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("Error:\nduring fork_here_doc");
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	return (here_doc);
}

t_file	here_doc(t_token *current, t_minishell *shell, int replace_env,
		t_file **tab_here_doc)
{
	t_file	here_doc;

	if (current->next == NULL || current->next->type != TOKEN_WORD)
	{
		ft_putstr_fd("Error:\nNo delimiter for here_doc\n", 2);
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	current = current->next;
	here_doc = fork_here_doc(current->value, shell, replace_env, tab_here_doc);
	return (here_doc);
}