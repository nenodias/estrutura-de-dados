### Compilando a biblioteca em objeto
gcc -c soma.c -o soma.o

### Compilando biblioteca de funções de cabeçalho pelo arquivo objeto
ar rc libsoma.a soma.o

### Compilando o arquivo executável
gcc main.c -o executavel -L. -lsoma