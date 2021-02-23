/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:41:46 by dchani            #+#    #+#             */
/*   Updated: 2020/11/02 21:30:01 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "minirt.h"

typedef	struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

void					ft_lstadd_back(t_list **lst, t_list *new);
char					**ft_split(char const *s, char c);
char					*ft_strchr(const char *s, int c);
size_t					ft_strlen(const char *s);
char					*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
size_t					ft_finddict(char const *dict, char const *buf);
double					ft_atof(const char *str);

#endif
