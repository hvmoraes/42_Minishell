/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:37:18 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/03/11 19:09:44 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_tilda_dir(char *home, char *full_path)
{
	char	*dir;
	char	*temp;

	dir = ft_substr(full_path, ft_strlen(home), ft_strlen(full_path));
	temp = dir;
	dir = ft_strjoin("\033[1;34m~", temp);
	free(temp);
	temp = dir;
	dir = ft_strjoin(temp, "\033[0m$ ");
	free(temp);
	return (dir);
}

char	*get_root_dir(char *full_path)
{
	char	*dir;
	char	*temp;

	temp = ft_strjoin("\033[1;34m", full_path);
	dir = ft_strjoin(temp, "\033[0m$ ");
	free(temp);
	return (dir);
}

char	*get_prompt_dir(void)
{
	char	*full_path;
	char	*home;

	full_path = get_env_value("PWD=");
	home = get_env_value("HOME=");
	if (!full_path[0] || !home[0])
		return (NULL);
	if (!ft_strncmp(full_path, home, ft_strlen(home) + 1))
		return (ft_strdup("\033[1;34m~\033[0m$ "));
	else if (!ft_strncmp(full_path, home, ft_strlen(home)) 
			&& ft_strlen(full_path) > ft_strlen(home))
		return (get_tilda_dir(home, full_path));
	else
		return (get_root_dir(full_path));
}

char	*get_prompt(void)
{
	char	*user;
	char	*left_part;
	char	*dir;
	char	*prompt;
	char	*temp;

	user = get_env_value("USER=");
	if (!user[0])
		left_part = ft_strdup("\033[1;32mminishell\033[0m:");
	else
	{
		temp = ft_strjoin(user, "@minishell");
		left_part = ft_strjoin("\033[1;32m", temp);
		free(temp);
		temp = left_part;
		left_part = ft_strjoin(temp, "\033[0m:");
		free(temp);
	}
	dir = get_prompt_dir();
	if (!dir)
	{
		free(left_part);
		return (NULL);
	}
	prompt = ft_strjoin(left_part, dir);
	free(left_part);
	free(dir);
	return (prompt);
}
	
char	*read_input(void)
{
	char	*prompt;
	char	*line;
	int		alloc_prompt;

	prompt = get_prompt();
	alloc_prompt = (prompt != NULL);
	if (!prompt)
		prompt = "\033[1;34mminishell\033[0m$ ";
	line = readline(prompt);
	if (alloc_prompt)
		free(prompt);
	if (!line)
		return (NULL);
	prompt = line;
	line = trim_input(line);
	free(prompt);
	return (line);
}