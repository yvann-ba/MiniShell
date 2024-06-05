/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_redirect2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:58:15 by ybarbot           #+#    #+#             */
/*   Updated: 2024/06/05 12:15:51 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_redirect_array(t_minishell *shell)
{
	t_minishell						cpy;
	t_index_and_available_here_doc	*index_and_available_here;
	static int						id_here_doc;

	shell->tab_here_doc = run_here_doc(shell);
	cpy = *shell;
	index_and_available_here = ft_calloc(1, sizeof(t_index_and_available_here_doc));
	index_and_available_here->here_doc_available = 0;
	index_and_available_here->i = 0;
	while (cpy.tokens != NULL)
	{
		handle_input_output(cpy, index_and_available_here, shell, &id_here_doc);
		if (cpy.tokens->type == TOKEN_WORD
			&& (cpy.tokens->value != cpy.redirect_array[index_and_available_here->i].infile.name
				&& cpy.tokens->value != cpy.redirect_array[index_and_available_here->i].outfile.name))
			handle_word(&cpy, &cpy.tokens, &index_and_available_here->i);
		else
		{
			if (cpy.tokens->type != TOKEN_PIPE && cpy.tokens->next != NULL)
				cpy.tokens = cpy.tokens->next;
			cpy.tokens = cpy.tokens->next;
		}
	}
	id_here_doc = 0;
	free(index_and_available_here);
}

void	fill_t_redirect(t_minishell *shell)
{
	if (!init_redirect_array(shell))
		return ;
	shell->redirect_array[0].infile.name = NULL;
	shell->redirect_array[0].infile.fd = -1;
	shell->redirect_array[0].infile.is_allocated = 0;
	shell->redirect_array[0].outfile.name = NULL;
	shell->redirect_array[0].outfile.fd = -1;
	shell->redirect_array[0].argv = NULL;
	fill_redirect_array(shell);
	//print_data(shell->redirect_array, shell->nb_cmds);
}
