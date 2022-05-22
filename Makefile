# *--------- SOURCES ---------*

SRCS_DIR	= ./srcs/

SRCS		=	\
				builtin/cd.c					\
				builtin/cd_utils.c				\
				builtin/display.c				\
				builtin/echo.c					\
				builtin/env_utils.c				\
				builtin/env.c					\
				builtin/exit.c					\
				builtin/export.c				\
				builtin/export_add.c			\
				builtin/export_no_args.c		\
				builtin/export_sort.c			\
				builtin/export_utils.c			\
				builtin/pwd.c					\
				builtin/unset.c					\
				builtin/utils_b.c				\
				builtin/builtin.c				\
				expand/expand.c					\
				expand/env_expand.c				\
				expand/utils_expand.c			\
				expand/expand_ret.c				\
				parsing/display.c				\
				parsing/parsing.c				\
				parsing/piper.c					\
				parsing/syntax_errors.c			\
				parsing/syntax_errors_utils.c	\
				parsing/struct_manager.c		\
				parsing/tokenizer.c				\
				parsing/token_definer.c			\
				parsing/token_definer_utils.c	\
				parsing/token_assigner.c		\
				parsing/tokenizer_utils.c		\
				parsing/utils_parser.c			\
				redir/redir.c					\
				redir/redirin.c					\
				redir/redirout.c				\
				redir/heredoc.c					\
				redir/expand_heredoc.c			\
				pipex/pipex.c					\
				pipex/pipex_path.c				\
				pipex/pipex_args.c				\
				pipex/display_pipex.c			\
				pipex/initclose_pipex.c			\
				pipex/utils_pipex.c				\
				pipex/pipex_clean.c				\
				exec/exec_solo.c				\
				exec/exec_solo_utils.c 			\
				main.c							\
				utils_main.c					\
				main_utils.c					\

# *--------- OBJECTS ---------*

OBJS = $(addprefix $(OBJS_DIR), $(addprefix $(SRCS_DIR), $(SRCS:.c=.o)))

$(OBJS_DIR)%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# *--------- LIBFT ---------*

LIBFT_PATH	= ./libft
LIBFT		= libft/libft.a
# LIBFT_FLAGS	= -L$(LIBFT_PATH)

# *-------- INCLUDE --------*

INCLUDE_DIR = -I ./includes
INC = ./includes/minishell.h

# *-------- GENERALS --------*

NAME	= 	minishell

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -g3

RM		=	rm -rf

# *-------- COMPILE --------*

all	:		$(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE_DIR)

$(NAME):	$(OBJS) $(LIBFT) $(INC)
			$(CC) $(CFLAGS) $(OBJS) $(INCLUDE_DIR) -lreadline -o $(NAME) $(LIBFT)
			@echo "$(NAME) created"

$(LIBFT):
			make -s -C $(LIBFT_PATH)

# *======== RULES ========*

leak:
			valgrind --leak-check=full --trace-children=yes --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell

clean:
			make clean -C $(LIBFT_PATH)
			$(RM) $(OBJS)
			@echo ".o deleted"

fclean:		clean
			make fclean -C $(LIBFT_PATH)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean flcean re%
