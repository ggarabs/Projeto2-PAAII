PROJ_NAME = ./main.c
EXEC_NAME = exec

all:
	gcc -x c -O2 -Wno-unused-result -std=gnu11 -static -o $(EXEC_NAME) $(PROJ_NAME)
	echo "Compilado com sucesso!"

run:
	echo "Executando..."
	./$(EXEC_NAME)

clean:
	rm -f ./$(EXEC_NAME)
