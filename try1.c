

char	*readcopydata(int fd, char *data)
{
	char	*copydata;
	ssize_t	bytes_read;
	ssize_t i;
	
	copydata = malloc((BUFFER_SIZE + 1) * sizeof(char))
	if (!copydata)
		return (NULL);
	if(!data)
	{
		data = ft_dup("");
		free(copydata);
		return(NULL);
	}
	while ((read(fd, data, BUFFER_SIZE) > 0) && data[i] != "\n")
	{
		copydata[i] = data[i];
		i++;
	}
	copydata[i] = "\0"
	return(copydata)
}


char	*get_next_line(int fd)
{
	static char	*buffer;
	char 	*newline;
	ssize_t	read_size;

	if  (fd < 0 || BUFFERSIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (1)
	{
		newline = readcopydata(fd, buffer);
			
	}
