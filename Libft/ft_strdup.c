/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:46:20 by rabatist          #+#    #+#             */
/*   Updated: 2024/10/05 14:18:08 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*total;
	size_t	i;

	i = 0;
	total = (char *)malloc(ft_strlen(s1) + 1);
	if (total == NULL)
		return (NULL);
	while (s1[i])
	{
		total[i] = s1[i];
		i++;
	}
	total[i] = '\0';
	return (total);
}
/*
#include <stdio.h>

int	main()
{
	const char *original = "salut";
	char *copy = ft_strdup(original);

	printf("%s\n", copy);
	return (0);
}
*/
