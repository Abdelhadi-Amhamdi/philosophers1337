# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamhamdi <aamhamdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:14:30 by aamhamdi          #+#    #+#              #
#    Updated: 2023/04/19 16:13:05 by aamhamdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = philo
BONUS_NAME = philo_b

SRCS_DIR = srcs/
B_SRCS_DIR = philo_bonus/
BUILD_DIR = build/

S_HEADER = philo.h
B_HEADER = philo_bonus.h

SRC = philo.c actions.c utils.c utils2.c time.c
SRCS = $(addprefix $(SRCS_DIR), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(BUILD_DIR), $(OBJ))

B_SRC = philo_bonus.c utils_bonus.c utils2_bonus.c time_bonus.c
B_SRCS = $(addprefix $(B_SRCS_DIR), $(B_SRC))
B_OBJ = $(B_SRC:.c=.o)
B_OBJS = $(addprefix $(BUILD_DIR), $(B_OBJ))

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR)%.o: $(SRCS_DIR)%.c $(SRCS_DIR)$(S_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILD_DIR)%.o: $(B_SRCS_DIR)%.c $(B_SRCS_DIR)$(B_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR):
	@mkdir $(BUILD_DIR)

bonus: $(BUILD_DIR) $(BONUS_NAME)

$(BONUS_NAME): $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o $(BONUS_NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
