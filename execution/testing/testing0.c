#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_path
{
    char    **path;
    int cnt;
}	t_path;

typedef struct s_ar
{
    char    **ar;
	char	*flag;
    int cnt;
}	t_ar;

int	cnt_words(const char *str, char delimiter)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] != delimiter)
		{
			cnt++;
			while (str[i] && str[i] != delimiter)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

int	sizew(char const *s, char c, int i)
{
	int	sz;

	sz = 0;
	while (s[i] != c && s[i])
	{
		sz++;
		i++;
	}
	return (sz);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*moschi;

	i = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	moschi = (char *)malloc(len + 1);
	if (moschi == NULL)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (i < len)
		{
			moschi[i] = s[start + i];
			i++;
		}
	}
	moschi[i] = '\0';
	return (moschi);
}

char	**ft_split(char const *s, char c)
{
	char	**stck;
	int		wrds;
	int		i;
	size_t	sz;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	wrds = cnt_words(s, c);
	stck = (char **)malloc((wrds + 1) * sizeof(char *));
	if (stck == NULL)
		return (stck);
	while (i < wrds)
	{
		while (s[count] == c)
			count++;
		sz = sizew(s, c, count);
		stck[i] = ft_substr(s, count, sz);
		i++;
		count = count + sz;
	}
	stck[i] = 0;
	return (stck);
}

void    get_path(char *path, t_path *p)
{
    int i;
    i = 0;

    p->path = ft_split(path, ':');

    while (p->path[i])
    {
        p->cnt++;
        // printf("*** %s ***\n", p->path[i]);
        i++;
    }
}

char    *get_key(char *str)
{
    char    *key;
    int     j;
    int     k;
    k = 0;
    j = 0;
    while(str[j])
    {
        if (str[j] == '-')
        {
            key = malloc(sizeof(char) * j + 2);
            if (!key)
                return (NULL);
            k = 0;
            while(k <= j)
            {
                key[k] = str[k];
                k++;
            }
            key[k] = '\0';
            return (key);
        }
        j++;
    }
    return (NULL);
}

void    get_args(char **av, t_ar *ar)
{
    int i = 1;
	int k = 0;
	int j = 0;
	int flg = 0;
	size_t len = 0;
	char **ars;
	char **get_flag;
    while (av[i])
    {
		ars = ft_split(av[i], '|');
		ar->cnt++;
		i++;
    }
	// k = 0;
	// while (ars[k])
	// {
	// 	printf("---> args :%s\n", ars[k]);
	// 	k++;
	// }
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lensrc;

	i = 0;
	lensrc = ft_strlen(src);
	if (dstsize == 0)
		return (lensrc);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (lensrc);
} 

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		return (srclen + dstsize);
	while (src[i] && dstlen < dstsize && i < (dstsize - dstlen - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*reue;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (s1 && s2)
	{
		reue = (char *)malloc(lens2 + lens1 + 1);
		if (reue == NULL)
			return (NULL);
		ft_strlcpy(reue, s1, lens1 + 1);
		ft_strlcat(reue, s2, lens2 + lens1 + 1);
		return (reue);
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

#include <fcntl.h>
#include <unistd.h>


int main()
{
    char* path = getenv("PATH");
    t_path *p = malloc(sizeof(p));
    t_ar *ar = malloc(sizeof(ar));
	char *str_join;
		int j = 0;
	get_path(path, p);
	char *ddd[] = {"-ddd", "-ls", NULL};
	// get_args(av, ar);

	char *test[] = {"ls", "-l", NULL};
	char *test1[] = {"wc", "-l", NULL};
	if (ft_strcmp(test[0], "ls") == 0)
	{
		printf("------- test 1----------\n");
		int pipe_fd[2];
		// Create a pipe
		if (pipe(pipe_fd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		// First fork to create the first child process
		pid_t child_pid1 = fork();
		if (child_pid1 == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (child_pid1 == 0) {
			// Child process 1
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]); // Close the read end of the pipe
			j = 0;
			close(pipe_fd[1]); // Close the read end of the pipe
			while (j <= p->cnt)
			{
				str_join = ft_strjoin(p->path[j], "/");
				str_join = ft_strjoin(str_join, test1[0]);
				// printf(" %s\n ", str_join);
				execve(str_join, test1, NULL);
				j++;
			}
			perror("execve");
			exit(EXIT_FAILURE);
		} else
		{	// Parent process
			// Second fork to create the second child process
			pid_t child_pid2 = fork();

			if (child_pid2 == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}

			if (child_pid2 == 0)
			{
				// Child process 2

				// Redirect stdin to the read end of the pipe
				dup2(pipe_fd[1], 1);
				close(pipe_fd[1]); // Close the write end of the pipe
				close(pipe_fd[0]);
				j = 0;
				while (j <= p->cnt)
				{
					str_join = ft_strjoin(p->path[j], "/");
					str_join = ft_strjoin(str_join, test[0]);
					// printf(" %s\n ", str_join);
					execve(str_join, test, NULL);
					j++;
				}

				// This code will only run if execve fails
				perror("execve");
				exit(EXIT_FAILURE);
			} else {
				// Parent process

				// Close the pipe file descriptors
				close(pipe_fd[0]);
				close(pipe_fd[1]);

				// Wait for both child processes to complete
				wait(NULL);
			}
		}
		printf("-------end test 1----------\n");
	}
	else
	{
			while (j <= p->cnt)
			{
				str_join = ft_strjoin(p->path[j], "/");
				str_join = ft_strjoin(str_join, test[0]);
				printf("---> %s\n", str_join);
				j++;
				execve(str_join, test, NULL);
				if (j == p->cnt)
				{
					perror("---not execve---");
					exit(1);
				}
			}
		printf("---------");
	}
	exit(0);
























    printf("------- test ----------\n");
    // If the environment variable doesn't exist, it returns NULL
    // printf("PATH :%s\n", (path != NULL) ? path : "getenv returned NULL");
    // get_path(path, p);

	// exit(1);
    // int i = 0;

    // printf("cnt %d \n", p->cnt);
    // while (i <= p->cnt)
    // {
    //     printf("----> %s<-----\n", p->path[i]);
    //     i++;
    // }
    printf("---------end test---------\n");

	printf("------- test 1----------\n");
    int pipe_fd[2];  // Pipe file descriptors for communication between processes
    char *wc_args[] = {"/usr/bin/wc", "-l", NULL};
    char *ls_args[] = {"/bin/ls", "-l", NULL};

	// Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

	// First fork to create the first child process
    pid_t child_pid1 = fork();

    if (child_pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

	if (child_pid1 == 0) {
		// Child process 1
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]); // Close the read end of the pipe
		close(pipe_fd[1]); // Close the read end of the pipe
		// Execute the command "/usr/bin/wc -l"
		execve("/usr/bin/wc", wc_args, NULL);

		// This code will only run if execve fails
		perror("execve");
		exit(EXIT_FAILURE);
    } else
	{	// Parent process
        // Second fork to create the second child process
        pid_t child_pid2 = fork();

        if (child_pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

		if (child_pid2 == 0) {
            // Child process 2

            // Redirect stdin to the read end of the pipe
            dup2(pipe_fd[1], 1);
            close(pipe_fd[1]); // Close the write end of the pipe
            close(pipe_fd[0]);
            // Execute the command "/bin/ls -l"
            char *ls_args[] = {"/bin/ls", "-l", NULL};
            execve("/bin/ls", ls_args, NULL);

            // This code will only run if execve fails
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process

            // Close the pipe file descriptors
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            // Wait for both child processes to complete
            wait(NULL);
        }
	}
	printf("-------end test 1----------\n");
	exit(1);

	// struct Node_Path* head = NULL;
    // char *args[] = {"ls", "-l", NULL};
    // char *env[] = {NULL};

    // char *str_join;
    // // while (1)
    // // {
    // int j = 0;
    //     while (j <= p->cnt)
    //     {
    //         str_join = ft_strjoin(p->path[j], "/");
    //         str_join = ft_strjoin(str_join, args[0]);
    //         printf("---> %s\n", str_join);
    //         j++;
    //         execve(str_join, args, env);
    //         if (j == p->cnt)
    //         {
    //             perror("---not execve---");
    //             exit(1);
    //         }
    //     }
	// printf("---------");
        // if (execve(str_join, args, env) == -1) {
        //     perror("execve");
        //     return 1;
        // }
    // }
    // create_env(env, &head);

    return 0; // This line is not reached if execve is successful.
}

