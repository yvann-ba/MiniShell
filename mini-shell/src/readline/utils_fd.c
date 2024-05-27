#include "../minishell.h"

int	open_file_and_handle_errors(t_minishell *shell, t_file here_doc_cpy)
{
	int	fd;

	fd = open (here_doc_cpy.name, O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
	{
		perror("Error:\nduring creat_file_descriptor");
		free_minishell(shell);
		shell->exit_status = 1;
		exit (EXIT_FAILURE);
	}
	return (fd);
}
