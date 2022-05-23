/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:58:47 by nali              #+#    #+#             */
/*   Updated: 2021/11/13 16:58:47 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_list;
	t_list	*new_elem;

	if (lst == NULL)
		return (NULL);
	current = lst;
	new_list = NULL;
	while (current != NULL)
	{
		new_elem = ft_lstnew((*f)(current->content));
		if (new_elem == NULL)
			ft_lstclear(&new_elem, (*del));
		else
			ft_lstadd_back(&new_list, new_elem);
		current = current->next;
	}
	return (new_list);
}
