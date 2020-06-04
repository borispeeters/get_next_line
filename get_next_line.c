/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 14:25:55 by bpeeters       #+#    #+#                */
/*   Updated: 2020/01/06 12:36:28 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*lst_clear(t_list **head)
{
	t_list	*node;
	t_list	*temp;

	node = *head;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	*head = NULL;
	return (NULL);
}

t_list	*checklst_add(t_list **head, int fd)
{
	t_list	*node;
	t_list	*new;

	if (read(fd, 0, 0) < 0)
		return (NULL);
	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	new = (t_list*)malloc(sizeof(t_list));
	if (!new)
		return (lst_clear(head));
	new->fd = fd;
	new->sz = 1;
	new->buf[0] = '\0';
	new->next = *head;
	new->previous = NULL;
	if (*head != NULL)
		(*head)->previous = new;
	*head = new;
	return (new);
}

int		clear_node(t_list **head, t_list *fbuf, ssize_t ret)
{
	if (fbuf->previous == NULL && fbuf->next == NULL)
		free(fbuf);
	else if (fbuf->previous == NULL)
	{
		*head = fbuf->next;
		(*head)->previous = NULL;
		fbuf->next = NULL;
		free(fbuf);
	}
	else if (fbuf->next == NULL)
	{
		fbuf->previous->next = NULL;
		fbuf->previous = NULL;
		free(fbuf);
	}
	else
	{
		fbuf->previous->next = fbuf->next;
		fbuf->next->previous = fbuf->previous;
		fbuf->previous = NULL;
		fbuf->next = NULL;
		free(fbuf);
	}
	return (ret);
}

void	read_fd(t_list *fbuf, char **line)
{
	fbuf->sz = read(fbuf->fd, fbuf->buf, BUFFER_SIZE);
	if (fbuf->sz < 0)
	{
		free(*line);
		*line = NULL;
	}
	if (fbuf->sz <= 0)
		return ;
	fbuf->buf[fbuf->sz] = '\0';
}

int		get_next_line(int fd, char **line)
{
	static	t_list	*head;
	t_list			*fbuf;

	fbuf = checklst_add(&head, fd);
	if (!fbuf)
		return (-1);
	*line = ft_strdup("");
	if (!*line)
		return (clear_node(&head, fbuf, -1));
	while (1)
	{
		if (!*fbuf->buf)
			read_fd(fbuf, line);
		if (fbuf->sz <= 0)
			return (clear_node(&head, fbuf, fbuf->sz));
		*line = ft_strjoin(*line, fbuf->buf);
		if (!*line)
			return (clear_node(&head, fbuf, -1));
		if (eol_check(fbuf->buf))
		{
			prep_buf(fbuf->buf);
			return (1);
		}
		fbuf->buf[0] = '\0';
	}
}
