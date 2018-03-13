#include "../include/ft_printf.h"

static void		minus_del(t_p *p)
{
	int		i;

	if ((p->width && p->zero_on) || ((p->precision >= p->width) ||
		(p->precision < 0)))
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '-';
	}
	p->plus_on = 0;
	i = 0;
	while (p->temp_s[++i])
		p->temp_s[i - 1] = p->temp_s[i];
	p->temp_s[--i] = 0;
	p->width--;
	p->minus_del = 1;
}

static void		funct_for_d4(t_p *p)
{
	check_the_buf(p, ft_strlen(p->temp_s) > (size_t)ft_abs(p->precision) ?
		ft_strlen(p->temp_s) : ft_abs(p->precision));
	if (p->plus_on && p->temp_s[0] != '-' && !p->zero_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '+';
	}
	while (p->precision >= 0 && (p->precision -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 48;
		p->precision--;
	}
	ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
	while (p->precision < 0 && p->prec_found && (ft_abs(p->precision) -
		p->spaces - (p->minus_del ? 1 : p->plus_on) -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 32;
		p->precision++;
	}
}

static void		funct_for_d3(t_p *p)
{
	while ((p->precision - (int)ft_strlen(p->temp_s) - p->j++) > 0)
		p->buf[p->ret++] = 48;
	ft_memcpy(p->buf + p->ret, p->temp_s, (p->ret += ft_strlen(p->temp_s)));
	while (p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) -
		(int)ft_strlen(p->temp_s)) : 0) - p->spaces -
		(p->temp_s[0] == '-' ? 0 : p->plus_on) -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = 32;
		p->width--;
	}
}

static void		funct_for_d2(t_p *p)
{
	check_the_buf(p, ft_strlen(p->temp_s) > (size_t)p->width ?
		ft_strlen(p->temp_s) : p->width);
	while (!p->minus_on && (p->width - (ft_abs(p->precision) >
		(int)ft_strlen(p->temp_s) ? (ft_abs(p->precision) -
		(int)ft_strlen(p->temp_s)) : 0) - p->spaces -
		(p->temp_s[0] == '-' ? 0 : p->plus_on) -
		(int)ft_strlen(p->temp_s)) > 0)
	{
		p->buf[p->ret++] = p->zero_on ? 48 : 32;
		p->width--;
	}
	if (p->plus_on && p->temp_s[0] != '-' && !p->zero_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '+';
	}
	if (p->minus_del && p->precision <= p->width && p->precision > 0)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '-';
	}
	funct_for_d3(p);
}

void			funct_for_d(t_p *p)
{
	if (p->prec_found && p->precision < 0)
		p->width = 0;
	if (p->prec_found)
		p->zero_on = 0;
	if (p->temp_s[0] == '-' && ((p->width && p->zero_on) || p->prec_found))
		minus_del(p);
	if (p->spaces && p->minus_del)	
		p->spaces = 0;
	if (p->plus_on && p->temp_s[0] != '-' && p->zero_on)
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = '+';
	}
	if (p->spaces && !p->minus_del && p->temp_s[0] != '-')
	{
		check_the_buf(p, 1);
		p->buf[p->ret++] = 32;
	}
	if (p->temp_s[0] == 48 && !p->precision)
		p->temp_s[0] = 0;
	if (p->width >= ft_abs(p->precision))
		funct_for_d2(p);
	else
		funct_for_d4(p);
	ft_strdel(&p->temp_s);
}
