# Trabalho-de-T-picos
Repositório para o trabalho de Tópicos Especiais em Otimização

Para compilar, usar : 

gcc FILE -o m -I /path/until/trabTop -lm

Exemplo:

gcc Main.c -o Main -I /home/hosana/git/Trabalho-de-T-picos -O3 -lm

A diretiva -I fará com que o arquivo includes.h seja incluido em qualquer outro arquivo dentro de qualquer pasta.
Consulte: 
https://gcc.gnu.org/onlinedocs/cpp/Search-Path.html#Search-Path 
para mais informações.

A diretiva -O3 fará com que o código seja otimizado pelo compilador.

A diretiva -lm permitirá que funções da bibliotema math.h sejam usadas.

