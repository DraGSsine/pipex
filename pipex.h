/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:31:05 by youchen           #+#    #+#             */
/*   Updated: 2023/12/27 09:26:00 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "read_line.h"

char	**ft_split(const char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strstr(char *str, char *to_find);
char	*ft_substr(char *s, size_t start, size_t len);
void	handdle_middle_commands(char **argv, int fds2[], int fds[], char **env);
void	handdle_here_doc(char *limiter);
char	**get_env_paths(char **env);
char	*validate_path(char *command, char **env);
void	middle_commnad(char *argv, int fds[], char **env, int fds2[]);
size_t	count_args(char **str);

#endif
