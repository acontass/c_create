/* *************************************************************************** */
/*                                                                             */
/*                                                         :::      ::::::::   */
/*   c_create.c                                          :+:      :+:    :+:   */
/*                                                     +:+ +:+         +:+     */
/*   by: acontass <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/03 22:07:55 by acontass           #+#    #+#             */
/*   Updated: 2014/05/05 00:54:58 by acontass          ###   ########.fr       */
/*                                                                             */
/* *************************************************************************** */
#include "c_create.h"

#include <stdio.h>

static char	*ft_strcat(const char *s1, const char *s2, char c)
{
	int		count[2];
	char	*ret;

	count[0] = -1;
	while (s1[++count[0]])
		;
	count[1] = -1;
	while (s2[++count[1]])
		;
	if (!(ret = malloc(sizeof(*ret) * (count[0] + count[1] + 2))))
		return (0);
	count[0] = -1;
	count[1] = -1;
	while (s1[++count[0]])
		ret[++count[1]] = s1[count[0]];
	ret[++count[1]] = c;
	count[0] = -1;
	while (s2[++count[0]])
		ret[++count[1]] = s2[count[0]];
	ret[++count[1]] = '\0';
	return (ret);
}

static void	ft_putstr_fd(int fd, char *str)
{
	int		count;

	count = -1;
	while (str[++count])
		;
	write(fd, str, count);
}

static int	ft_strlen(const char *str)
{
	int		count;

	count = -1;
	while (str[++count])
		;
	return (count);
}

static void	write_header(int fd, char *user, char *file)
{
	int		count;

	write(fd, "/* *************************************************************************** */\n", 82);
	write(fd, "/*                                                                             */\n", 82);
	write(fd, "/*                                                         :::      ::::::::   */\n", 82);
	write(fd, "/*   ", 5);
	ft_putstr_fd(fd, file);
	count = 4 + ft_strlen(file) + 25;
	while (++count < 82)
		write(fd, " ", 1);
	write(fd, ":+:      :+:    :+:   */\n", 25);
	write(fd, "/*                                                     +:+ +:+         +:+     */\n", 82);
	write(fd, "/*   by: ", 9);
	ft_putstr_fd(fd, user);
	write(fd, " <marvin@42.fr>", 15);
	count = 8 + ft_strlen(user) + 15 + 29;
	while (++count < 82)
		write(fd, " ", 1);
	write(fd, "+#+  +:+       +#+        */\n", 29);
	write(fd, "/*                                                 +#+#+#+#+#+   +#+           */\n", 82);
	write(fd, "/*   Created: 2014/05/03 22:07:55 by ", 37);
	ft_putstr_fd(fd, user);
	count = 36 + ft_strlen(user) + 26;
	while (++count < 82)
		write(fd, " ", 1);
	write(fd, "#+#    #+#             */\n", 26);
	write(fd, "/*   Updated: 2014/05/04 02:25:09 by ", 37);
	ft_putstr_fd(fd, user);
	count = 36 + ft_strlen(user) + 27;
	while (++count < 82)
		write(fd, " ", 1);
	write(fd, "###   ########.fr       */\n", 27);
	write(fd, "/*                                                                             */\n", 82);
	write(fd, "/* *************************************************************************** */\n", 82);
}

static char	create_dirs_n_files(char **av)
{
	int		count[2];
	char	*dir_inc;
	char	*dir_src;
	char	*file_h;
	char	*file_c;
	int		fd_c;
	int		fd_h;
	char	*user;

	count[0] = 0;
	if (!(user = getenv("USER")))
		return (0);
	while (av[++count[0]])
	{
		if ((mkdir(av[count[0]], 0755)) == -1)
		{
			perror(av[count[0]]);
			return (0);
		}
		if (!(dir_inc = ft_strcat(av[count[0]], "includes", '/')))
			return (0);
		if ((mkdir(dir_inc, 0755)) == -1)
			return (0);
		if (!(file_h = ft_strcat(av[count[0]], "h", '.')))
			return (0);
		if ((fd_h = open(ft_strcat(dir_inc, file_h, '/'), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (0);
		write_header(fd_h, user, file_h);
		write(fd_h, "#ifndef ", 8);
		count[1] = -1;
		while (file_h[++count[1]])
		{
			if (file_h[count[1]] >= 'a' && file_h[count[1]] <= 'z')
				file_h[count[1]] -= 32;
			if (file_h[count[1]] != '.')
				write(fd_h, &file_h[count[1]], 1);
			else
				write(fd_h, "_", 1);
		}
		write(fd_h, "\n# define ", 10);
		count[1] = -1;
		while (file_h[++count[1]])
		{
			if (file_h[count[1]] != '.')
				write(fd_h, &file_h[count[1]], 1);
			else
				write(fd_h, "_", 1);
		}
		write(fd_h, "\n\n\n\n#endif", 10);
		if (!(dir_src = ft_strcat(av[count[0]], "srcs", '/')))
			return (0);
		if ((mkdir(dir_src, 0755)) == -1)
			return (0);		
		if (!(file_c = ft_strcat(av[count[0]], "c", '.')))
			return (0);
		if ((fd_c = open((ft_strcat(dir_src, file_c, '/')), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (0);
		write_header(fd_c, user, file_c);
		write(fd_c, "#include \"", 10);
		count[1] = -1;
		while (file_h[++count[1]])
		{
			if (file_h[count[1]] >= 'A' && file_h[count[1]] <= 'Z')
				file_h[count[1]] += 32;
		}
		write(fd_c, file_h, count[1]);
		write(fd_c, "\"\n\nint\t\tmain(int ac, char **av)\n{\n\treturn (0);\n}\n", 49);
		close(fd_c);
		close(fd_h);
	}
	return (1);
}

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		if (!(create_dirs_n_files(av)))
			return (0);
	}
	return (0);
}
