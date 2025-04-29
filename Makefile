# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 15:39:25 by jcurtido          #+#    #+#              #
#    Updated: 2025/03/12 16:51:58 by jcurtido         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definir colores
BLUE = \033[1;33m
GREEN = \033[1;32m
RED = \033[1;31m
RESET = \033[0m

# Nombre
NAME = philo

# Compilador y flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

# Archivos fuente
SRCS = ft_atoi.c main.c utils.c config.c philo.c philo_utils.c philo_routine.c philo_actions.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

# Reglas
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) || (echo "$(RED)❌ La compilación ha fallado.$(RESET)"; exit 1)
	@echo "$(GREEN)✅ Compilado$(RESET)"

# Ocultar la compilación de los archivos .c a .o
%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	@rm -rf $(OBJS) $(DEPS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
