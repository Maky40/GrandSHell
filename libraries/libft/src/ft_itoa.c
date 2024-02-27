/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:09:16 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 14:57:42 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_power_10(int n, int p)
{
	int	i;

	i = 0;
	if (p == 0)
		return (1);
	while (i < p)
	{
		n = n * 10;
		i++;
	}
	return (n);
}

int	ft_count(long int n)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (n < 0)
	{
		n = -n;
		j++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + j + 1);
}

char	ft_write(char s, long int n, int count)
{
	if (count == 0)
		return ('\0');
	n = (n / ft_power_10(1, count - 1));
	if (n < 9)
		s = n + 48;
	else
		s = (n % 10) + 48;
	return (s);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			count;
	int			i;
	long int	n2;

	i = 0;
	n2 = n;
	count = ft_count(n2);
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	while (count >= 0)
	{
		if (n2 < 0)
		{
			n2 = -n2;
			str[i] = '-';
			i++;
			count--;
		}
		str[i] = ft_write(str[i], n2, count);
		i++;
		count--;
	}
	return (str);
}
/*#include <stdio.h>
int	main()
{

	int	i;

	i = 0;
	printf("%s", ft_itoa(i));
}*/
