Autor: Frederico Dal Soglio Reckziegel | fdsreckziegel@inf.ufpel.edu.br


- Enunciado:

    - Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte.
    - Nenhuma variável pode ser declarado em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
        Exemplo do que não pode: int c; char a; int v[10]; Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
    - Imprimir de forma ordenada usando uma fila ordenada
    - O usuário escolhe um parâmetro de ordenação e uma fila ordenada é criada
    - Depois o programa imprime na tela o conteúdo da fila
    - Implementar a base de dados da agenda usando lista duplamente ligada
    - Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.


- Estrutura do diretório:
    |_ trabalho.c               - Arquivo fonte do programa.
    |_ README.txt               - Documentação do programa.
    |_ Makefile                 - Arquivo com comandos úteis para a execução do comando.
    |_ tests/                   - Diretório com arquivos de teste
      |_ test_phone_sort.txt    - Arquivo com entradas pré definidas para teste da ordenação por número de telefone.
      |_ test_age_sort.txt      - Arquivo com entradas pré definidas para teste da ordenação por idade.
      |_ test_name_sort.txt     - Arquivo com entradas pré definidas para teste da ordenação por nome.
      |_ test_general.txt       - Arquivo com entradas pré definidas para este das funcionalidades gerais do código.


- Como rodar:
    Para rodar o programa desenvolvido basta compilar com o comando "make compile" e, em seguida, rodar o comando "make run". Ou, se preferir, o comando "make test" irá rodar o programa já com as estradas especificadas em "test.txt".


- Comentários:
    Video de demonstração: O vídeos pode ser acessado pelo link: <inserir link para o video>
