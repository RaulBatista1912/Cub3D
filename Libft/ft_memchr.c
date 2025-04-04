/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:36:33 by rabatist          #+#    #+#             */
/*   Updated: 2024/10/11 17:15:32 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	const char str[] = "Hello Wrold";
	char i = 'r';

	char *total = ft_memchr(str, i, 30);
	if (total == NULL)
		printf("pas trouve connard\n");
	else
		printf("%c,%ld\n", i, total - str);
	return (0);
}
*/
