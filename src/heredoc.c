/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:52:36 by mnie              #+#    #+#             */
/*   Updated: 2024/03/14 11:10:11 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	heredoc_tmp_fd(t_command *cmd)
{
	char	*line;
	int		tmp_fd;
	// int		stdin_fd;

	tmp_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	// stdin_fd = dup(STDIN_FILENO);
	if (tmp_fd < 0)
		ft_printf("ERROR HEREDOC");
	while (1)
	{
		ft_printf("\nheredoc tchatcheur > ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strchr(line, cmd -> fd -> str) == 1 && ft_strlen(line) == ft_strlen(cmd -> fd -> str))
			break ;
		else
			ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	close (tmp_fd);
	if (cmd -> heredoc_last == 1)
		cmd -> input_file = tmp_fd;
	else
		unlink(tmp_fd);
}
