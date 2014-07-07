##
## Makefile for bomberman in /home/tang_j/bomberman
## 
## Made by Jean Luc TANG
## Login   <tang_j@epitech.net>
## 
## Started on  Sun Jun 15 02:37:28 2014 Jean Luc TANG
## Last update Sun Jun 15 14:11:41 2014 Jean Luc TANG
##


CC	=	g++

RM	=	rm -f

NAME	=	bomberman

CPPFLAGS  +=	-I./includes/
CPPFLAGS  +=	-Wall -Wextra -Werror

LDFLAGS	+=	-L./libs/ -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread

SRCS	= 	main.cpp \
		Menu.cpp \
		Core.cpp \
		CoreMap.cpp

OBJS	=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
