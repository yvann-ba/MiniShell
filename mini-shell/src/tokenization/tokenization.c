#include "../minishell.h"

t_token	*init_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

void	add_token_based_on_char(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	identify_double_char_tokens(input, head);
	if (**input == '>')
		add_token(head, init_token(TOKEN_REDIRECT_OUT, ">"));
	else if (**input == '<')
		add_token(head, init_token(TOKEN_REDIRECT_IN, "<"));
	else if (**input == '|')
		add_token(head, init_token(TOKEN_PIPE, "|"));
	else
		add_word_token(input, head, env, shell);
}

void	identify_and_add_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	if (is_special_char(**input))
		add_token_based_on_char(input, head, env, shell);
	else if (!ft_isspace(**input))
		add_word_token(input, head, env, shell);
}

t_token	*tokenize(const char *input, char **env, t_minishell *shell)
{
	t_token	*head;

	head = NULL;
	if (input)
	{
		while (*input)
		{
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '\0')
				break ;
			identify_and_add_token(&input, &head, env, shell);
			if (*input)
				input++;
		}
	}
	return (head);
}
