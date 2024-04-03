/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:52:36 by mnie              #+#    #+#             */
/*   Updated: 2024/04/02 18:51:25 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	g_func;

// void	handler_heredoc(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 	}
// }
int	ft_strchr_heredoc(char *str, char *cmp)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (cmp[y] == '\0' && str[i] == '\0')
		return (1);
	while (str[i])
	{
		while (str[i + y] == cmp[y] && str[i + y] && cmp[y])
			y++;
		if (cmp[y] == '\0' && str[i + y] == '\n')
			return (1);
		else
			y = 0;
		i++;
	}
	return (0);
}

size_t	len_heredoc_line(char *line)
{
	size_t	len;

	len = 0;
	while (line[len] != '\0')
	{
		len++;
	}
	len--;
	return (len);
}
int	heredoc_conditions(char	*line, t_command *cmd, int i)
{
	size_t	len;

	if (line == NULL)
		{
			ft_printf("bash: avertissement : « here-document » close \n");
			return (1);
		}
	len = len_heredoc_line(line);
	if (ft_strchr_heredoc(line, cmd->fd[i].str) == 1
			&& len == ft_strlen(cmd->fd[i].str))
		{
			free(line);
			return (1) ;
		}
	return (0);
}
void	heredoc_tmp_fd(t_command *cmd, int i)
{
	char		*line;
	int			tmp_fd;

	// g_func = 0;
	tmp_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000777);
	if (tmp_fd < 0)
		ft_printf("ERROR HEREDOC");
	// signal(SIGINT, SIG_DFL);
	while (1)
	{
		ft_printf("heredoc> ");
		// if (g_func == 1)
		// 	break ;
		line = get_next_line(STDIN_FILENO);
		if (heredoc_conditions(line, cmd, i) == 1)
			break ;
		else
			ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	close (tmp_fd);
	if (cmd->fd->heredoc_last == 1)
		cmd->input_file = ".heredoc_tmp";
}
