CC=cc
NAME=philo

CFLAGS=-Wall -Werror -Wextra -O0 -g3 -lpthread

SRCS=main.c parse.c init.c init2.c start.c routine.c monitor.c \
	 actions.c cleanup.c state.c time.c ft_aux.c

OBJS=main.o parse.o init.o init2.o start.o routine.o monitor.o \
	 actions.o cleanup.o state.o time.o ft_aux.o

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

main.o : main.c philo.h
	$(CC) $(CFLAGS) -c main.c

parse.o : parse.c philo.h
	$(CC) $(CFLAGS) -c parse.c

init.o : init.c philo.h
	$(CC) $(CFLAGS) -c init.c

init2.o : init2.c philo.h
	$(CC) $(CFLAGS) -c init2.c

start.o : start.c philo.h
	$(CC) $(CFLAGS) -c start.c

routine.o : routine.c philo.h
	$(CC) $(CFLAGS) -c routine.c

monitor.o : monitor.c philo.h
	$(CC) $(CFLAGS) -c monitor.c

actions.o : actions.c philo.h
	$(CC) $(CFLAGS) -c actions.c

cleanup.o : cleanup.c philo.h
	$(CC) $(CFLAGS) -c cleanup.c

state.o : state.c philo.h
	$(CC) $(CFLAGS) -c state.c
	
time.o : time.c philo.h
	$(CC) $(CFLAGS) -c time.c

ft_aux.o : ft_aux.c philo.h
	$(CC) $(CFLAGS) -c ft_aux.c

.PHONY: all clean fclean re
