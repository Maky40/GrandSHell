/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:20:39 by mnie              #+#    #+#             */
/*   Updated: 2024/03/24 22:15:40 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t	i;

// 	if (!src && !dest)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		((unsigned char *)dest)[i] = *((unsigned char *)(src + i));
// 		i++;
// 	}
// 	return (dest);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }
// char	*ft_strdup(const char *s)
// {
// 	char	*s2;

// 	s2 = (char *)malloc((ft_strlen(s) + 1));
// 	if (!s2)
// 		return (0);
// 	ft_memcpy(s2, s, ft_strlen(s) + 1);
// 	return (s2);
// }

// int	ft_strncmp(const	char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	// printf("s1[i] = %c, s2[i] = %c\n", s1[i], s2[i]);
// 	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
// 	{
// 		// printf("s1[i] = %c, s2[i] = %c\n", s1[i], s2[i]);
// 		i++;
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }


char	**remove_variable(char **env, int j)
{
	int		len;
	char	**new_env;

	len = 0;
	while (env[len])
		len++;
	new_env = malloc(sizeof(char *) * len);
	new_env[len - 1] = NULL;
	len = 0;
	while (len < j)
	{
		new_env[len] = ft_strdup(env[len]);
		len++;
	}
	j++;
	while (env[j])
	{
		new_env[len] = ft_strdup(env[j]);
		j++;
		len++;
	}
	free_dup_env(env);
	env = dup_env(new_env);
	return (env);
}

void	do_unset2(t_env *env, char *arguments, int i)
{
	int		j;

	j = 0;
	if (i == 1)
	{
		while (env -> modified_env[j])
		{
			if (ft_strncmp(arguments, env -> modified_env[j], ft_strlen(arguments)) == 0 \
			&& arguments[0] != '_')
				env -> modified_env = remove_variable(env -> modified_env, j);
			j++;
		}
	}
	if (i == 2)
	{
		while (env -> vars_add[j])
		{
			if (ft_strncmp(arguments, env -> vars_add[j], ft_strlen(arguments)) == 0 \
			&& arguments[0] != '_')
				env -> vars_add = remove_variable(env -> vars_add, j);
			j++;
		}
	}
}
//regarde si un argument correspond a une variable env pour appliquer unset
void	do_unset(t_env **env, t_command *cmd)
{
	int	i;
	t_env *lst;

	lst = last_env(env);
	i = 1;
	while (cmd -> arguments[i])
	{
		ft_printf ("search_variable = %d\n", search_variable(lst, cmd -> arguments[i]));
		if (search_variable(lst, cmd -> arguments[i]) == 0)
			ft_printf("ERROR for %s, variable not found\n", cmd -> arguments[i]);
		else if (search_variable(lst, cmd -> arguments[i]) == 1)
			do_unset2(lst, cmd -> arguments[i], 1);
		else
			do_unset2(lst, cmd -> arguments[i], 2);
		i++;
	}
}

// int main (int argc, char **argv, char **envp)
// {
// 	t_command 	cmd;
// 	char 		**env;
// 	int			i;

// 	i = 0;
// 	env = dup_env(envp);
// 	cmd.arguments = malloc(sizeof(char *) * 3);
// 	cmd.arguments[2] = NULL;
// 	cmd.arguments[0] = ft_strdup("GDMSESSION");
// 	cmd.arguments[1] = ft_strdup("alala");
// 	while (env[i])
// 		i++;
// 	env = do_unset(env, &cmd);
// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// }