NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LIBFT = libft/libft.a
SRCS = main.c\
		./parsing/aft_dollar.c\
		./parsing/free_all.c\
		./parsing/lexer_utils.c\
		./parsing/lexer.c\
		./parsing/parse_utils.c\
		./parsing/parse.c\
		./parsing/str_collect.c\
		./parsing/unquoted_str.c\
		./parsing/utils1.c\
		./parsing/utils2.c\
		./execution/randomUtils.c\
		./execution/redirection_utils.c	\
		./execution/cd.c\
		./execution/builtInUtils.c\
		./execution/heredoc.c\
		./execution/before_heredoc.c\
		./execution/export_utils.c\
		./execution/heredoc_utils.c\
		./execution/redirection.c\
		./execution/pipe_utils.c\
		./execution/exec_utils.c\
		./execution/builtins/env.c\
		./execution/builtins/ft_nset.c\
		./execution/builtins/ft_pwd.c\
		./execution/echo.c\
		./execution/free.c\
		./execution/pipe.c\
		./execution/execSimpleCommand.c	\
		./execution/export.c\
		./execution/ft_exit.c\
		./execution/combine.c\
		./execution/error_files.c\
		./execution/echo_utils.c\
		./execution/exit_utils.c\

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@echo "make minishell"

$(LIBFT):
	@make -C libft
	@make -C libft bonus

clean:
	@rm -f $(OBJS)
	@make -C libft clean
	@echo "clean minishell"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "fclean minishell"

re: fclean all
	@echo "re minishell"

.PHONY: clean fclean re all
