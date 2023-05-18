NAME = computor 

HEADERS_DIR = .

HEADERS = computor.hpp

SRCS =	computor.cpp \
		parsing.cpp \
		solving.cpp

OBJS = ${SRCS:.cpp=.o}

COMPILER = g++

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(COMPILER) $(OBJS) -o $(NAME)

$(OBJS): %.o: %.cpp $(HEADERS)
	$(COMPILER) -Wall -Wextra -Werror -g2 -I$(HEADERS_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

