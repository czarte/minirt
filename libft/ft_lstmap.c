/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:37:41 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/17 22:38:49 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*add;
	void	*buf;

	if (!lst || !*f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		buf = (*f)(lst->content);
		add = ft_lstnew(buf);
		if (!add)
		{
			if (new)
				ft_lstclear(&new, del);
			return (free(buf), NULL);
		}
		ft_lstadd_back(&new, add);
		lst = lst->next;
	}
	return (new);
}
