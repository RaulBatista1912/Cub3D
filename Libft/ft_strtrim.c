/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:38:40 by rabatist          #+#    #+#             */
/*   Updated: 2024/10/07 18:20:17 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	while (is_set(s1[i], set))
		i++;
	if (i == j)
		return (ft_strdup(""));
	while (is_set(s1[j - 1], set))
		j--;
	return (ft_substr(s1, i, j - i));
}
/*
#include <stdio.h>

int	main()
{
	printf("%s\n", ft_strtrim("123caca312", "231"));
	return (0);
}
*/
