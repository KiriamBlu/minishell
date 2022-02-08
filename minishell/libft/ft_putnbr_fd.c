/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:07:40 by jsanfeli          #+#    #+#             */
/*   Updated: 2021/09/23 09:20:22 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	char			l;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			n *= -1;
			ft_putchar_fd('-', fd);
		}
		nb = (unsigned int)n;
		if (nb > 9)
		{
			ft_putnbr_fd (nb / 10, fd);
			l = '0' + (nb % 10);
			ft_putchar_fd(l, fd);
		}
		else
		{	
			l = nb + '0';
			ft_putchar_fd(l, fd);
		}
	}
}
