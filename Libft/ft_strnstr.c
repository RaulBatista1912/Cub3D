/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:04:17 by rabatist          #+#    #+#             */
/*   Updated: 2024/10/03 17:17:01 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			while (needle[j] && (i + j) < len && haystack[i + j] == needle[j])
			{
				j++;
			}
		}
		if (needle[j] == '\0')
		{
			return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	printf("%s\n", ft_strnstr("bbbbbbbbbcacabbbbbbbbbbbb", "caca", 30));
	return (0);
}
*/
