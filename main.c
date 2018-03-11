/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:29:25 by rnaumenk          #+#    #+#             */
/*   Updated: 2018/03/01 17:29:27 by rnaumenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

int		main(int argc, char **argv)
{
	int		i = 255;
	// char	*line;
	// int		fd;

	setlocale(LC_ALL, "");
	// fd = open(argv[1], O_RDONLY);
	// while (get_next_line(fd, &line))
		// ft_printf("%s\n", line);
	// printf("(      %d      )\n", ft_printf("%s, %s", L'ÊM-^ZM-^V', L'ÿ≠'));
	printf("(      %d      )\n", ft_printf("002147483647-21474836482147483647-2147483648%d", 42));
	printf("(      %d      )\n",    printf("002147483647-21474836482147483647-2147483648%d", 42));	
	// system("leaks a.out");
	return (0);
}
