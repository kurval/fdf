/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:33:48 by asolopov          #+#    #+#             */
/*   Updated: 2019/11/18 11:36:43 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fdf.h"

static int		count_width(t_mprop *mprop, char **newline)
{
	while (newline[mprop->width] != NULL)
		mprop->width++;
	return (mprop->width);
}

static void		count_lines(char *argv, t_mprop *mprop)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		mprop->nlines++;
	ft_strdel(&line);
	close(fd);
}

static void		store_line(t_mprop *mprop, char *line, int cy)
{
	char	**newline;
	int		arrlen;
	int		cx;

	cx = 0;
	newline = ft_strsplit(line, SPACE);
	arrlen = count_width(mprop, newline);
	mprop->map[cy] = (t_pmap **)malloc(arrlen * sizeof(t_pmap *));
	while (newline[cx] != NULL)
	{
		mprop->map[cy][cx] = (t_pmap *)malloc(sizeof(t_pmap));
		mprop->map[cy][cx]->y = cy;
		mprop->map[cy][cx]->x = cx;
		mprop->map[cy][cx]->z = ft_atoi(newline[cx]);
		cx++;
	}
	free(newline);
}

static void		get_maxminz(t_mprop *mprop)
{
	int	cx;
	int	cy;

	cy = 0;
	cx = 0;
	mprop->zmin = mprop->map[cy][cx]->z;
	mprop->zmax = mprop->map[cy][cx]->z;
	while (cy < mprop->nlines)
	{
		cx = 0;
		while (cx < mprop->width)
		{
			if (mprop->map[cy][cx]->z > mprop->zmax)
				mprop->zmax = mprop->map[cy][cx]->z;
			else if ((mprop->map[cy][cx]->z < mprop->zmin))
				mprop->zmin = mprop->map[cy][cx]->z;
			cx++;
		}
		cy++;
	}
}

void			get_input(char **argv, t_mprop *mprop)
{
	int		fd;
	char	*line;
	int		cnt;

	cnt = 0;
	line = ft_strnew(1);
	count_lines(argv[1], mprop);
	mprop->map = (t_pmap ***)malloc(mprop->nlines * sizeof(t_pmap **));
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		//validate_line
		store_line(mprop, line, cnt);
		cnt++;
	}
	get_maxminz(mprop);
	ft_strdel(&line);
	close(fd);
}
