/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:17:53 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:41:33 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void		ft_lstclr(t_list *lst, void (*del)(void *))
{
	t_list *ptr;

	while (lst)
	{
		ptr = lst->next;
		del(lst->content);
		free(lst);
		lst = ptr;
	}
}

static	void		ft_lstadd(t_list *lst, t_list *new)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	else
		lst = new;
}

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *))
{
	t_list	*beg;
	t_list	*ptr;

	beg = 0;
	while (lst)
	{
		ptr = ft_lstnew(f(lst->content));
		if (!ptr)
		{
			ft_lstclr(beg, del);
			return (0);
		}
		if (!beg)
		{
			beg = ptr;
			lst = lst->next;
			continue ;
		}
		ft_lstadd(beg, ptr);
		lst = lst->next;
	}
	return (beg);
}
