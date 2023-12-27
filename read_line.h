/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:17:16 by youchen           #+#    #+#             */
/*   Updated: 2023/12/26 22:18:33 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_H
# define READ_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*rl_strjoin(char *s1, char *buff);
char	*rl_substr(char *s, unsigned int start, size_t len);
size_t	rl_strlen(char *s1);
char	*read_line(int fd);
int		rl_strchr(char *s, int c);
#endif
