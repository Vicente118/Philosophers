#include "../includes/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strdup(const char *source)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *) malloc(ft_strlen((char *) source) * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	while (source[i])
	{
		*(dest + i) = *(char *)(source + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = len;
	if (ft_strlen(s) - start < len)
		slen = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (slen + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*(s + start) && i < len && start < ft_strlen(s))
	{
		str[i] = *(char *)(s + start);
		i++;
		s++;
	}
	str[i] = '\0';
	return (str);
}
