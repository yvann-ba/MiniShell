#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <unistd.h>
# include <errno.h>

extern char **environ;

typedef enum e_token_type
{
	TOKEN_WORD,// 0
	TOKEN_REDIRECT_IN,// 1 <
	TOKEN_REDIRECT_OUT,// 2 >
	TOKEN_PIPE,// 3 |
	TOKEN_DOUBLE_REDIRECT_OUT,// 4 >>
	TOKEN_HEREDOC,// 5 <<
	TOKEN_SINGLE_QUOTE,// 6 '
	TOKEN_DOUBLE_QUOTE,// 7 "
	TOKEN_ENV_VAR,// 8 $
	TOKEN_EXIT_STATUS,// 9 $?
	TOKEN_TILDE,// 10 ~
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char			*name;
	t_token_type	type;
	int				fd[2];
}	t_file;

typedef struct s_data
{
	t_token		*h_tokens;
	t_file		infile;
	t_file		outfile;
	char		**argv;
	int			argc;
}	t_data;

//PARSING
t_token		*init_token(t_token_type type, char *value);
void		add_token(t_token **head, t_token *new_token);
int			is_special_char(char c);
void		identify_and_add_token(const char **input, t_token **head);
void		add_special_token(const char **input, t_token **head, \
			t_token_type type);
void		add_word_token(const char **input, t_token **head);
void		free_tokens(t_token **tokens);
t_token		*tokenize(const char *input);
void		add_quoted_token(const char **input, t_token **head,\
			char quoteType);
t_token		*read_input(void);
void		identify_double_char_tokens(const char **input, t_token **head);
void		add_token_based_on_char(const char **input, t_token **head);
void		init_signal_handlers(void);



//BUILTINS
void		ft_echo(t_token *tokens);
char		*ft_getenv(const char *name, char **env);
void		ft_cd(t_token *tokens, char **env);

void		syntax_analys(t_token *tokens);
#endif
