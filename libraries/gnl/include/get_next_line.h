/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:24:26 by mnie              #+#    #+#             */
/*   Updated: 2024/02/05 11:17:59 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct d_list
{
	char			*content;
	struct d_list	*next;
}					t_klist;
char	*get_next_line(int fd);
void	ft_read_file(t_klist **lst, int fd);
void	ft_add_buf(char *buf, t_klist **lst, int was_read);
char	*ft_generate_line(int len, t_klist *lst);
void	ft_clean(t_klist **lst);
int		ft_found_newline(t_klist *lst);
t_klist	*ft_klstlast(t_klist *lst);
int		ft_len_line(t_klist	*lst);
void	ft_free_stock(t_klist *stash);
int		ft_strlen2(const char *str);
#endif
