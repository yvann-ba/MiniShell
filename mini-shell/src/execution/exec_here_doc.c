#include "../minishell.h"

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
			(strlen(filename) + strlen("/tmp/") + 1));
	if (final_path == NULL)
	{
		perror("Error:\n during write_here_doc_in_file\n");
		free(filename);
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	final_path = ft_strncpy
		(final_path, "/tmp/", ft_strlen("/tmp/"));
	final_path = ft_strcat
		(final_path, filename);
	free(filename);
	return (final_path);
}

static t_file	fork_here_doc(char *delimiter, t_minishell *shell, int replace_env, t_file **tab_here_doc)
{
	pid_t	pid;
	int		status;
	t_file	*here_doc_cpy;

	here_doc_cpy = ft_calloc(sizeof(t_file), 1);
	if (here_doc_cpy == NULL)
		error_exit("Error:\nduring fork_here_doc\n", shell);
	if (here_doc_cpy == NULL)
	{
		perror("Error:\nduring fork_here_doc\n");
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	here_doc_cpy->name = generate_and_assign_filename(shell);
	here_doc_cpy->fd = open_file_and_handle_errors(shell, *here_doc_cpy);
	pid = fork();
	if (pid == 0)
	{
		handle_here_doc(shell, *here_doc_cpy, delimiter, replace_env, tab_here_doc);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("Error:\nduring fork_here_doc");
		free(here_doc_cpy);
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	return (*here_doc_cpy);
}

t_file	here_doc(t_token *current, t_minishell *shell, int replace_env, t_file **tab_here_doc)
{
	t_file	here_doc;

	if (current->next == NULL)
	{
		ft_printf("Error:\nNo delimiter for here_doc\n");
		free_minishell(shell);
		shell->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	current = current->next;
	here_doc = fork_here_doc(current->value, shell, replace_env, tab_here_doc);
	return (here_doc);
}
