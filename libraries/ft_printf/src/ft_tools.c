/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnie <mnie@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:04:21 by mnie              #+#    #+#             */
/*   Updated: 2024/01/19 15:00:55 by mnie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	if (str == NULL)
		return (ft_putstr("(null)"));
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	long long int	num;

	num = n;
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num > 9)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	if (num >= 0 && num <= 9)
		ft_putchar((num + '0'));
	return (ft_len_putnbr(n));
}

int	ft_putnbr_unsigned(unsigned int n)
{
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	if (n <= 9)
		ft_putchar(n + '0');
	return (ft_len_unsigned_putnbr(n));
}

int	ft_puthex(unsigned long n, const char *base)
{
	if (n > 15)
	{
		ft_puthex(n / 16, base);
		ft_puthex(n % 16, base);
	}
	if (n <= 15)
		ft_putchar(base[n]);
	return (ft_len_hexa(n));
}
