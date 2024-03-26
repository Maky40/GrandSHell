// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset_backup.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/13 11:20:39 by mnie              #+#    #+#             */
// /*   Updated: 2024/03/25 22:41:40 by mnie             ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"


// char	**remove_variable(char **env, int j)
// {
// 	int		len;
// 	char	**new_env;

// 	len = 0;
// 	while (env[len])
// 		len++;
// 	new_env = malloc(sizeof(char *) * len);
// 	new_env[len - 1] = NULL;
// 	len = 0;
// 	while (len < j)
// 	{
// 		new_env[len] = ft_strdup(env[len]);
// 		len++;
// 	}
// 	j++;
// 	while (env[j])
// 	{
// 		new_env[len] = ft_strdup(env[j]);
// 		j++;
// 		len++;
// 	}
// 	free_dup_env(env);
// 	env = dup_env(new_env);
// 	return (env);
// }
// void	do_unset3(char **env, char *arguments)
// {
// 	int	j;

// 	j = 0;
// 	while (env[j])
// 	{
// 		if (ft_strncmp(arguments, env[j], ft_strlen(arguments)) == 0 \
// 		&& arguments[0] != '_')
// 		{
// 			env = remove_variable(env, j);
// 			j = j - 1;
// 		}
// 		j++;
// 	}
// }
// void	do_unset2(t_env *env, char *arguments, int i)
// {
// 	char	*str;

// 	ft_printf("DANS UNSER ARGS = %s\n", arguments);
// 	str = variable_without_equal(arguments);
// 	ft_printf("DANS UNSET STR WITHOUT = %s\n", str);
// 	if (i == 1)
// 		do_unset3(env -> modified_env, str);
// 	if (i == 2)
// 		do_unset3(env -> vars_add, str);
// 	free (str);
// }
// void	do_unset(t_env **env, t_command *cmd)
// {
// 	int	i;
// 	t_env *lst;

// 	lst = last_env(env);
// 	i = 1;
// 	while (cmd -> arguments[i])
// 	{
// 		ft_printf ("search_variable = %d\n", search_variable(lst, cmd -> arguments[i]));
// 		if (search_variable(lst, cmd -> arguments[i]) == 0)
// 			ft_printf("ERROR for %s, variable not found\n", cmd -> arguments[i]);
// 		else if (search_variable(lst, cmd -> arguments[i]) == 1)
// 			do_unset2(lst, cmd -> arguments[i], 1);
// 		else
// 			do_unset2(lst, cmd -> arguments[i], 2);
// 		i++;
// 	}
// }