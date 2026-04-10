/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:37:02 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/15 11:02:21 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Global Variable
t_data	g_data;

static void	reset_global(void)
{
	g_data.child = false;
	g_data.expanded = false;
}

static void	process_input(char *input)
{
	t_lexer	lex;
	t_ast	*root;

	if (input_is_empty(input))
		return ;
	if (lexer(input, &lex) <= 0)
		return ;
	root = NULL;
	if (parser(&lex, &root) <= 0)
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void) argc;
	(void) argv;
	init_shell(envp);
	while (1)
	{
		reset_global();
		input = read_input();
		if (!input)
			exit(EXIT_FAILURE);
		if (ft_strlen(input) <= 0)
		{
			free(input);
			continue ;
		}
		if (!input_is_empty(input))
			add_history(input);
		process_input(input);
		free(input);
	}
}