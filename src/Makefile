.PHONY: all clean

CC := g++
CFLAGS := -std=c++11 -O2 -Wall
BINARIES := main tiempos tiempos_pd tiempos_bt tiempos_mitm generador_entradas generador_entradas_n_fijo_w_variable

all: $(BINARIES)

main: main.cpp mochila.cpp
	$(CC) $(CFLAGS) -o main main.cpp mochila.cpp

tiempos: tiempos.cpp mochila.cpp
	$(CC) $(CFLAGS) -o tiempos tiempos.cpp mochila.cpp

tiempos_pd: tiempos_pd.cpp mochila.cpp
	$(CC) $(CFLAGS) -o tiempos_pd tiempos_pd.cpp mochila.cpp

tiempos_bt: tiempos_bt.cpp mochila.cpp
	$(CC) $(CFLAGS) -o tiempos_bt tiempos_bt.cpp mochila.cpp

tiempos_mitm: tiempos_mitm.cpp mochila.cpp
	$(CC) $(CFLAGS) -o tiempos_mitm tiempos_mitm.cpp mochila.cpp

generador_entradas: generador_entradas.cpp
	$(CC) $(CFLAGS) -o generador_entradas generador_entradas.cpp

generador_entradas_n_fijo_w_variable: generador_entradas_n_fijo_w_variable.cpp
	$(CC) $(CFLAGS) -o generador_entradas_n_fijo_w_variable generador_entradas_n_fijo_w_variable.cpp

clean:
	rm -f $(BINARIES) *.o
