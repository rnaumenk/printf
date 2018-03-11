/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:39:00 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/05 13:39:01 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		create_res(unsigned long value, unsigned int base, char *res,
	int len)
{
	while (len >= 0)
	{
		if (value % base > 9)
			res[len] = (value % base) + 87;
		else
			res[len] = (value % base) + 48;
		len--;
		value /= base;
	}
}

static int		base_count(unsigned long value, unsigned int base, int len)
{
	while (value > base - 1)
	{
		len++;
		value /= base;
	}
	return (len + 1);
}

char			*ft_ultoa_base(unsigned long value, int base)
{
	char			*res;
	int				len;

	if (!(base > 1 && base < 17))
		return (0);
	len = 0;
	len = base_count(value, base, len);
	if (!(res = ft_strnew((size_t)len)))
		return (0);
	create_res(value, base, res, (len - 1));
	return (res);
}
