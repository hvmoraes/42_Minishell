/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:31:23 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/09 16:53:50 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_built	*init_builtins(void)
{
	t_built	*head;

	head = NULL;
	add_builtin(&head, "echo", ft_echo);
	add_builtin(&head, "cd", ft_cd);
	add_builtin(&head, "pwd", ft_pwd);
	add_builtin(&head, "export", ft_export);
	add_builtin(&head, "unset", ft_unset);
	add_builtin(&head, "env", ft_env);
	add_builtin(&head, "exit", ft_exit);
	return (head);
}

static void	init_global(void)
{
	g_data.status = EXIT_SUCCESS;
	g_data.child = false;
	g_data.expanded = false;
	g_data.default_fd[READ] = dup(STDIN_FILENO);
	g_data.default_fd[WRITE] = dup(STDOUT_FILENO);
	g_data.builtins = init_builtins();
}

static void	duplicate_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(g_data.env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
}

static void	init_env(char **envp)
{
	int		level;
	char	*prev;
	char	*shlvl;

	g_data.env = (t_list **)ft_calloc(1, sizeof(t_list *));
	if (!g_data.env)
		return ;
	duplicate_env(envp);
	if (list_has_value("SHLVL=", g_data.env))
	{
		level = ft_atoi(get_env_value("SHLVL=") + 1);
		prev = ft_itoa(level);
		shlvl = ft_strjoin("SHLVL=", prev);
		free(prev);
		modify_value(g_data.env, "SHLVL=", shlvl);
	}
	else
		ft_lstadd_back(g_data.env, ft_lstnew(ft_strdup("SHLVL=1")));
}

void	init_shell(char **envp)
{
	init_global();
	init_env(envp);
}