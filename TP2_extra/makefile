CC     = gcc
CFLAGS = -g
OBJS = funcoes_auxiliares.o operacoes_imagem.o tad.o seam_carving.o operacoes_grafos.o
TARGET = seam_carving

all: $(TARGET)

seam_carving: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -lm -o tp2
	
seam_carving.o: seam_carving.c tad.h operacoes_imagem.h funcoes_auxiliares.h operacoes_grafos.h
		$(CC) $(CFLAGS) -c seam_carving.c
	
funcoes_auxiliares.o: funcoes_auxiliares.c funcoes_auxiliares.h tad.c tad.h
	$(CC) $(CFLAGS) -c funcoes_auxiliares.c
	
operacoes_grafos.o: operacoes_grafos.c operacoes_grafos.h tad.c tad.h
	$(CC) $(CFLAGS) -c operacoes_grafos.c
	
operacoes_imagem.o: operacoes_imagem.c operacoes_imagem.h funcoes_auxiliares.c funcoes_auxiliares.h tad.c tad.h
	$(CC) $(CFLAGS) -lm -c operacoes_imagem.c
	
tad.o: tad.c tad.h  
	$(CC) $(CFLAGS) -c tad.c
	
clean: 
	rm -rf *.o ./$(TARGET)
