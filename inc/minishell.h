/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:37:14 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/15 13:57:56 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/inc/libft.h"
# include "macros.h"
# include "structs.h"
# include "enums.h"

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <err.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

extern t_data	g_data;

//////////////////////////////
/********** INIT ************/
//////////////////////////////

/****** init.c ****/
void	init_shell(char **envp);

//////////////////////////////
/********** LEXER ***********/
//////////////////////////////

/***** lexer.c ****/
int		lexer(char *input, t_lexer *lex);

/**** tokens.c ****/

int		init_token(t_token *token, int length);

int		handle_default(t_suplex *suplex);
void	handle_in_state(t_suplex *t_suplex);

int		handle_expand(t_token *token);
int		process_tokens(t_lexer *lex);

//////////////////////////////
/********** PARSER **********/
//////////////////////////////

int		parser(t_lexer *lex, t_ast **root);

t_ast	*cmd_line(void);
t_ast	*cmd_line1(void);
t_ast	*cmd_line2(void);
t_ast	*cmd_line3(void);

t_ast	*and_or(void);

//////////////////////////////
/********* EXECUTOR *********/
//////////////////////////////

//////////////////////////////
/********* BUILTINS *********/
//////////////////////////////

int		ft_cd(char **path);
int		ft_echo(char **str);
int		ft_env(char **data);
int		ft_export(char **new);
int		ft_pwd(char **data);
int		ft_unset(char **unset);
int		ft_exit(char **exit);

/* builtins_utils.c */
void	add_builtin(t_built **list, char *cmd, int (*f)(char **));

//////////////////////////////
/********** UTILS ***********/
//////////////////////////////

/*** env_utils.c **/
char	*get_env_value(char *value);

/* prompt_utils.c */
char	*read_input(void);

/** list_utils.c **/
int		list_has_value(char *value, t_list **list);
void	modify_value(t_list **list, char *old_value, char *new_value);

/*** str_utils.c **/
int		is_whitespace(char c);
int		input_is_empty(char *input);
int		get_char_type(char c);
int		is_terminator(char c);
char	*trim_input(char *input);

#endif