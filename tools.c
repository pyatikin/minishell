#include "minishell.h"

//int	ft_strcmp(const char *s1, const char *s2)
//{
//	size_t	i;
//
//	i = 0;
//	while (s1[i] == s2[i])
//	{
//		if (s1[i] == '\0' && s2[i] == '\0')
//			return (0);
//		i++;
//	}
//	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
//}
//
//int	ft_strncmp(const char *s1, const char *s2, size_t n)
//{
//	size_t	i;
//
//	i = 0;
//	if (n == 0)
//		return (0);
//	while (s1[i] == s2[i])
//	{
//		if ((s1[i] == '\0' && s2[i] == '\0') || i == n - 1)
//			return (0);
//		i++;
//	}
//	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
//}
//
//void	ft_putstr_fd(char *s, int fd)
//{
//	int	i;
//
//	i = 0;
//	while (s[i] != '\0')
//	{
//		write(fd, &s[i], 1);
//		i++;
//	}
//}

//size_t	ft_strlen(const char *s)
//{
//	size_t	len;
//
//	len = 0;
//	if (s == NULL)
//		return (0);
//	while (s[len] != '\0')
//		len++;
//	return (len);
//}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || \
		(c >= 'a' && c <= 'z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

//char	*ft_strdup(const char *s1)
//{
//	char	*str;
//	size_t	i;
//
//	if (!s1)
//		return (NULL);
//	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
//	if (!str)
//		return (NULL);
//	i = 0;
//	while (s1[i])
//	{
//		str[i] = s1[i];
//		i++;
//	}
//	str[i] = 0;
//	return (str);
//}

