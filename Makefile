NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LDFLAGS = -lreadline
LIBFT = libft/libft.a

RAEDPATH=$(shell brew  --prefix readline)
# READLINE = -L/Users/mayache-/.brew/opt/readline/lib -I/Users/mayache-/.brew/opt/readline/include
READLINE = -L $(RAEDPATH)/lib -I $(RAEDPATH)/include

SRCS = main.c\
	./execution/pipe.c\
		./execution/execSimpleCommand.c\
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
		./execution/redirection_utils.c	\
		./execution/heredoc.c\
		./execution/before_heredoc.c\
		./execution/heredoc_utils.c\
		./execution/redirection.c\
		./execution/pipe_utils.c\
		./execution/exec_utils.c\
		./execution/combine.c\
		./execution/error_files.c\
		./execution/utils/free.c\
		./execution/utils/exit_utils.c\
		./execution/builtins/echo.c\
		./execution/builtins/env.c\
		./execution/builtins/ft_cd.c\
		./execution/builtins/ft_pwd.c\
		./execution/builtins/ft_exit.c\
		./execution/builtins/ft_unset.c\
		./execution/builtins/export.c\
		./execution/builtins/echo_utils.c\
		./execution/builtins/builtInUtils.c\
		./execution/builtins/export_utils.c\

RANDOM_UTILS = ./execution/utils/randomUtils.c

all: $(NAME)



OBJS = $(SRCS:.c=.o) $(RANDOM_UTILS:.c=.o)

$(RANDOM_UTILS).o: $(RANDOM_UTILS).c 
	$(CC) -o $@ -c $< $(CFLAGS) $(READLINE)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME)  $(OBJS) $(LIBFT) $(LDFLAGS) $(READLINE)
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
