/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 14:26:35 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/02/03 14:26:36 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF

# define FT_PRINTF

# include <stdarg.h>
# include "wchar.h"
# include <locale.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdio.h>
# include <inttypes.h>
# include <stdint.h>

# define A(x) x == 'c' || x == 'C' || x == 's' || x == 'S' || x == 'p' || x == 'd' || x == 'D' || x == 'i' || x == 'o' || x == 'O' || x == 'u' || x == 'U' || x == 'x' || x == 'X' || x == '%'
# define B(x) x == '#' || x == '.' || x == '-' || x == '+' || x == 'l' || x == 'h' || x == 'j' || x == 'z' || x == ' ' || x == 39
# define C(x) x == 'C' || x == 'S' || x == 'c' || x == 's' || x == '%'

typedef	struct	s_p
{
	va_list				ap;
	int					i;
	int					j;
	char				*buf;
	char				*fmt;
	char				*spec;
	char				*without_spec;
	size_t				buf_size;
	size_t				spec_size;
	size_t				ret;
	char				temp_c;
	char				*temp_s;
	wint_t				temp_wc;
	int					wd;
	int					awd;
	wchar_t				*temp_ws;
	int					temp_d;
	long				temp_ld;
	intmax_t			temp_im;
	uintmax_t			temp_um;
	size_t				temp_st;
	unsigned long		temp_ul;
	unsigned long long	temp_ull;
	unsigned int		temp_ui;
	size_t				fmt_len;
	int					sl_on;
	int					l_on;
	int					h_on;
	int					j_on;
	int					z_on;
	int					plus_on;
	int					minus_on;
	int					sharp_on;
	int					spaces;
	int					zero_on;
	int					width;
	int					precision;
	int					error;
	int					found;
	int					sharp_undef;
	int					minus_undef;
	int					cut;
	int					prec_found;
	int					minus_del;
	int					stop;
	int					dotnull;
	int					kostyl;

}				t_p;

int				ft_printf(const char *format, ...);
int				ft_abs(int nb);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
void			look_for_specificators(t_p *p);
char			*ft_itoa_base(int value, int base);
size_t			check_the_buf(t_p *p, size_t len);
void			check_the_flags(t_p *p);
int				check_the_width(t_p *p);
char			*ft_ulxtoa_base(uintmax_t value, int base);
char			*ft_uixtoa_base(uintmax_t value, int base);
char			*ft_litoa_base(intmax_t value, int base);
void			funct_for_percent(t_p *p);
void			funct_for_p(t_p *p);
void			funct_for_d(t_p *p);
void			funct_for_s(t_p *p);
void			funct_for_c(t_p *p);
void			funct_for_wc(t_p *p);
void			funct_for_ws(t_p *p);
void			funct_for_u(t_p *p);
void			funct_for_o(t_p *p);
void			funct_for_x(t_p *p);
void			funct_for_big_x(t_p *p);
void			prefunct_for_big_d(t_p *p);
void			prefunct_for_d(t_p *p);
void			prefunct_for_big_u(t_p *p);
void			prefunct_for_u(t_p *p);
void			prefunct_for_wc(t_p *p);
void			prefunct_for_big_o(t_p *p);
void			prefunct_for_o(t_p *p);
void			prefunct_for_big_x(t_p *p);
void			prefunct_for_x(t_p *p);

#endif
