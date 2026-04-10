/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:25:07 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/15 12:05:20 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

/*	
	__token_struct__
	content	= string of the command
	type	= type of the token according to the e_token_type enum
	next	= next token in the list
*/
typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}	t_token;

/*	
	__lexer_struct__
	token_list	= list of tokens to be created
	num_token	= number of tokens
*/
typedef struct s_lexer
{
	t_token	*token_list;
	int		num_token;
}	t_lexer;

/*	
	__suplex_struct__
	tokens		= list of tokens pointing to the same token as token_list of t_lexer
	input		= command line being examined
	length		= strlen of the input
	state		= flag to signa if default, in quotes, double quotes, or curly brackets
	type		= token type as per the e_token_type enum
	i			= iterator for the input
	j			= iterator for the contents of the tokens

	Support struct for the lexing process
*/
typedef struct s_suplex
{
	t_token	*tokens;
	char	*input;
	int		length;
	int		state;
	int		type;
	int		i;
	int		j;
}	t_suplex;

/*	
	__suptok_struct__
	curr		= current token being processed
	prev		= previous token on the list
	count		= counter
	here		= heredoc flag
	semaphore	= semaphore

	Support struct for the tokenization process
*/
typedef struct s_suptok
{
	t_token	*curr;
	t_token	*prev;
	int		count;
	int		here;
	int		semaphore;
}	t_suptok;

typedef struct s_supexp
{
	t_token	*curr;
	char	*var_name;
	char	*new_cont;
	int		start;
	int		end;
}	t_supexp;

typedef struct s_suptrim
{
	int	i;
	int	j;
	int	state;
}	t_suptrim;

/*	
	__Builtin_struct__
	cmd 	= command
	f 		= function to be mapped according to the command
	next	= next builtin
*/
typedef struct s_built
{
	char			*cmd;
	int				(*f)(char **str);
	struct s_built	*next;
}	t_built;

//////////////////////////////
/********** AST *************/
//////////////////////////////

typedef struct s_ast
{
	int				type;
	char			*content;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

//////////////////////////////
/********* GLOBAL ***********/
//////////////////////////////

/*	
	__global_struct__
	status 		= integer exit code
	default_fd	= default file descriptors for I/O
	env			= linked list for the copy of the environment variables
	builtins	= builtin linked list
	child		= flag to signal if a process is a child process
	expanded	= flag to signal if the environment variables have been expanded
*/
typedef struct s_data
{
	int		status;
	int		default_fd[2];

	t_list	**env;
	t_built	*builtins;

	bool	child;
	bool	expanded;

	t_ast	**ast_root;
	t_ast	*ast_temp;
	t_token	*token;
}	t_data;

#endif