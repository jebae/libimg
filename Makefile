# library name
NAME = libimg.a

# dir, path
SRCDIR = srcs
INCDIR = includes
OBJDIR = objs

LIBFT_PATH = ../libft

# compiler
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I ./$(INCDIR) -I $(LIBFT_PATH)/includes
LIBS = -lpthread -L $(LIBFT_PATH) -lft

# srcs
SRCS = for_each_pixel.c\
	handle_error.c\
	buffer2img.c\
	img2buffer.c\
	rgb.c\

SRC_FILTER = gaussian_blur.c\
	sephia.c\
	negative.c\

# objs
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
OBJS += $(addprefix $(OBJDIR)/,$(SRC_FILTER:.c=.o))

# compile objs
HEADERS = ./$(INCDIR)/libimg.h

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/filter/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# build
all : $(NAME)

$(NAME) : $(OBJDIR) $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

$(OBJDIR) :
	mkdir -p $(OBJDIR)

# command
TEST_SRCS = ./__tests__/*.c
TEST_INCLUDES = $(INCLUDES) -I $(UNITY_PATH)/include
TEST_LIBS = $(LIBS) -L $(UNITY_PATH)/lib -lunity

test : $(OBJDIR) $(OBJS)
	$(CC) -D UNITY_MEMORY_OVERRIDES_H_ $(CFLAGS) $(TEST_INCLUDES) $(TEST_LIBS) $(TEST_SRCS) $(OBJS) -o test

.PHONY : test all clean fclean re