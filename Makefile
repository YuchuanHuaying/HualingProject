SrcFiles=$(wildcard *.c)

TargetFile=$(patsubst %.c,%,$(SrcFiles))

all:$(TargetFile)

%:%.c
	gcc -o $@ $^ -g

clean:
	rm -f $(TargetFile)

