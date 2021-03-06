/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:16:31 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/17 17:28:56 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

int		ft_isdigit(int c)
{
	if (c == '-')
		return (1);
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	err(char *s)
{
	int		i;
	char	*e;

	i = -1;
	ft_lstclear(&g_mylist);
	e = "ERROR !!!";
	write(2, e, ft_strlen(e));
	while (s[++i] != '\0')
		write(2, s + i, 1);
	write(2, "\n", 2);
	exit(EXIT_FAILURE);
}

t_list	*ft_lstnew(void *content)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list *tmp;

	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}
