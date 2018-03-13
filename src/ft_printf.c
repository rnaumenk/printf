/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 14:26:47 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/03 14:26:48 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void		default_flags(t_p *p)
{
	p->j = 0;
	p->l_on = 0;
	p->h_on = 0;
	p->plus_on = 0;
	p->minus_on = 0;
	p->sharp_on = 0;
	p->spaces = 0;
	p->zero_on = 0;
	p->width = 0;
	p->awd = 0;
	p->precision = -1;
	p->found = 1;
	p->sharp_undef = 0;
	p->minus_undef = 0;
	p->cut = 0;
	p->prec_found = 0;
	p->minus_del = 0;
	p->j_on = 0;
	p->z_on = 0;
	p->stop = 0;
	p->dotnull = 0;
}

static void		default_values(t_p *p)
{
	p->i = 0;
	p->ret = 0;
	p->error = 0;
	p->sl_on = 0;
}

static void		leaks_delete(t_p *p)
{
	ft_strdel(&p->buf);
	ft_strdel(&p->fmt);
	ft_strdel(&p->spec);
	free(p);
}

static void		move(t_p *p)
{
	while (p->fmt[p->i])
	{
		default_flags(p);
		if (p->fmt[p->i] == '%')
		{
			check_the_flags(p);
			ft_bzero(p->spec, p->spec_size);
		}
		else if (p->fmt[p->i] != '%' && check_the_buf(p, 1))
			p->buf[p->ret++] = p->fmt[p->i];
		if (p->error == 1)
			return ;
		p->i++;
	}
}

int				ft_printf(const char *format, ...)
{
	t_p			*p;

	if (!(p = (t_p*)malloc(sizeof(t_p))))
		return (-1);
	if (!(p->buf = (char*)ft_memalloc(sizeof(char) *
		((p->buf_size = 100000) + 1))))
		return (-1);
	if (!(p->spec = (char*)ft_memalloc(sizeof(char) *
		((p->spec_size = 20) + 1))))
		return (-1);
	if (!(p->fmt = (char*)ft_memalloc(sizeof(char) *
		((p->fmt_len = ft_strlen(format)) + 1))))
		return (-1);
	ft_memcpy(p->fmt, format, p->fmt_len);
	default_values(p);
	va_start(p->ap, format);
	move(p);
	va_end(p->ap);
	if (!p->error)
		write(1, p->buf, p->ret);
	leaks_delete(p);
	return (p->error ? -1 : p->ret);
}
