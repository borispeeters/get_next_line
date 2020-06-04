/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 14:26:15 by bpeeters       #+#    #+#                */
/*   Updated: 2020/01/06 12:21:22 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <stdlib.h>

typedef	struct		s_list
{
	int				fd;
	char			buf[BUFFER_SIZE + 1];
	ssize_t			sz;
	struct s_list	*next;
	struct s_list	*previous;
}					t_list;

int					get_next_line(int fd, char **line);
void				prep_buf(char *buf);
size_t				line_len(const char *s);
int					eol_check(char *str);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strdup(const char *s1);

#endif
