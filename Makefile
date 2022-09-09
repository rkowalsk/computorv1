NAME = computor 

HEADERS_DIR = headers

HEADERS =

SRCS = computor.cpp

OBJS = ${SRCS:.cpp=.o}

COMPILER = g++

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(COMPILER) $(OBJS) -o $(NAME)

$(OBJS): %.o: %.cpp $(HEADERS)
	$(COMPILER) -Wall -Wextra -Werror -g -I$(HEADERS_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

