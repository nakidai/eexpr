OBJS += eexpr.o
OBJS += evaluator.o
OBJS += main.o
OBJS += parser.o
OBJS += tokenizer.o

RM ?= rm -f

all: eexpr

eexpr: ${OBJS}
	cc ${LDFLAGS} -o eexpr ${OBJS} ${LDLIBS}

README: README.7
	mandoc -Tascii README.7 | col -b > README

clean:
	${RM} eexpr ${OBJS}
