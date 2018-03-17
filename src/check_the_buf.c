/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:22:59 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/04 19:23:00 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

size_t		check_the_buf(t_p *p, size_t len)
{
	char	*tmp;

	if ((p->ret + len) >= p->buf_size)
	{
		tmp = p->buf;
		while ((p->ret + len) >= p->buf_size)
			p->buf_size += 10000;
		if (!(p->buf = (char*)ft_memalloc(sizeof(char) * (p->buf_size + 1))))
			p->error = 1;
		if (!p->error && &p->buf != &tmp)
		{
			ft_memcpy(p->buf, tmp, p->ret);
			// free(tmp);
		}
	}
	return (len);
}
