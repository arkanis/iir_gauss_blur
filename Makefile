CFLAGS = -std=c99 -O2 -Wall -Wextra -Wno-unused-but-set-variable -Wno-unused-parameter -Werror
LDLIBS = -lm

all: blur

clean:
	rm -f blur