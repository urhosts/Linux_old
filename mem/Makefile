cli=client
ser=server
cc=gcc
serSrc=comm.c server.c
cliSrc=comm.c client.c

.PHONY:all
all:$(cli) $(ser)

$(cli):$(cliSrc)
	$(cc) -o $@ $^
$(ser):$(serSrc)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -rf $(cli) $(ser)

