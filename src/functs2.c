#include "../include/ft_printf.h"

static void		cut(t_p *p)
{
	char	*temp;
	int		i;

	if (!(temp = (char*)ft_memalloc(sizeof(char) * (p->precision + 1))))
		p->error = 1;
	i = -1;
	while (++i < p->precision)
		temp[i] = p->temp_s[i];
	p->temp_s = temp;
	p->cut = 1;
}

static void		funct_for_s2(t_p *p)
{
	if (p->sharp_undef || p->minus_undef)
		p->temp_s = "";
	if (p->precision >= 0 && ft_strlen(p->temp_s) > (size_t)p->precision)
		cut(p);
	check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ?
		ft_strlen(p->temp_s) : p->width);
	while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && !p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
	while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && p->minus_on)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	while (p->precision < 0 && p->prec_found)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
	// if (p->cut)
		// ft_strdel(&p->temp_s);
}

void			funct_for_s(t_p *p)
{
	p->temp_s = va_arg(p->ap, char*);
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (!p->temp_s)
	{
		p->temp_s = ft_strdup("(null)");
		if (p->precision >= 0 && ft_strlen(p->temp_s) > (size_t)p->precision)
			p->temp_s[p->precision] = 0;
		check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ?
			ft_strlen(p->temp_s) : p->width);
		while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && !p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
		while ((p->width - (int)ft_strlen(p->temp_s)) > 0 && p->minus_on)
		{
			p->buf[p->ret++] = p->zero_on ? 48 : 32;
			p->width--;
		}
		// ft_strdel(&p->temp_s);
	}
	else
		funct_for_s2(p);
}
