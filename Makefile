TARGET=./bin/tcpip.a

VPATH=src/
SRCS=$(shell find ./src/ipv4/ ./src/utils/ -name *.c)
OBJS=$(subst src,obj,$(subst .c,.o,$(SRCS)))
INCLUDES=includes
FLAGS=-Wall -Wextra -Werror -I $(INCLUDES)
PROD_FLAGS=$(FLAGS)
CC=gcc


all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $(TARGET) $(OBJS)

$(OBJS): obj/%.o: %.c build
	$(CC) -c $< -o $@ $(PROD_FLAGS)

build:
	mkdir -p obj/ipv4
	mkdir -p obj/utils

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f obj/*.o
	rm -f obj/ipv4/*.o
	rm -f obj/utils/*.o

re: fclean all
