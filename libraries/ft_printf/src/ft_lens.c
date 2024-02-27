/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:15:22 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 15:00:50 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_len_hexa(unsigned long num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / 16;
		i++;
	}
	return (i);
}

int	ft_len_putnbr(int num)
{
	long long int	n;
	int				i;

	n = num;
	i = 0;
	if (num == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_len_unsigned_putnbr(unsigned int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}
