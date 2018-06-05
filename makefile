OBJ = main.c jogodavelha.c
DESP = jogodavelha.h

compile:
	gcc $(OBJ) $(DESP) -o jogo -lm

clean:
	rm -r jogo