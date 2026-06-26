

int	valid_extension(char *file, char *extension)
{
	size_t	len_file;
	size_t	len_ext;
	char	*ptr_dot;

	len_file = ft_strlen(file);
	len_ext = ft_strlen(extension);
    if (len_ext > len_file)
        return (0);
	ptr_dot = &file[len_file - len_ext];
	while (*extension && *ptr_dot == *extension)
	{
		ptr_dot++;
		extension++;
	}
	if (*ptr_dot)
		return (0);
	return (1);
}