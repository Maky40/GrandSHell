/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:25:27 by mnie              #+#    #+#             */
/*   Updated: 2024/02/05 11:17:57 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_next_line(int fd)
{
	static t_klist	*lst = NULL;
	char			*line;
	int				i;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_free_stock(lst);
		lst = NULL;
		return (NULL);
	}
	ft_read_file(&lst, fd);
	i = ft_len_line(lst);
	line = ft_generate_line(i, lst);
	line[i] = '\0';
	ft_clean(&lst);
	if (line[0] == '\0')
	{
		ft_free_stock(lst);
		lst = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	ft_read_file(t_klist **lst, int fd)
{
	char	*buf;
	int		was_read;

	was_read = 1;
	while (ft_found_newline(*lst) != 1 && was_read != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		was_read = (int)read(fd, buf, BUFFER_SIZE);
		buf[was_read] = '\0';
		ft_add_buf(buf, lst, was_read);
		free(buf);
	}
}

void	ft_add_buf(char *buf, t_klist **lst, int was_read)
{
	int		i;
	t_klist	*node;
	t_klist	*last;

	node = malloc(sizeof(t_klist));
	if (!node)
		return ;
	node -> next = NULL;
	node -> content = malloc(sizeof(char) * (was_read + 1));
	i = 0;
	while (buf[i])
	{
		node -> content[i] = buf[i];
		i++;
	}
	node -> content[i] = buf[i];
	if (*lst == NULL)
		*lst = node;
	else
	{
		last = ft_klstlast(*lst);
		last->next = node;
	}
}

char	*ft_generate_line(int len, t_klist *lst)
{
	char	*line;
	t_klist	*current;
	int		i;

	current = lst;
	line = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (current)
	{
		len = 0;
		while (current -> content[len])
		{
			line[i] = current -> content[len];
			if (line[i] == '\n')
				return (line);
			i++;
			len++;
		}
		current = current -> next;
	}
	return (line);
}

void	ft_clean(t_klist **lst)
{
	t_klist	*last;
	t_klist	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_klist));
	if (lst == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_klstlast(*lst);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * \
	((ft_strlen2(last->content) - i) + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	ft_free_stock(*lst);
	*lst = clean_node;
}
