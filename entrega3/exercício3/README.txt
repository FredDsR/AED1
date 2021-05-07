Autor: Frederico Dal Soglio Reckziegel | fdsreckziegel@inf.ufpel.edu.br


- Enunciado:
    1. Monte figuras da sequência de passos da montagem de uma árvore avl
        1. Essa sequencia deve ter as 4 rotações
        2. https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
    2. É possível que uma inserção/remoção gere mais do que um rotação dupla? Explique
    3. Implemente uma árvore avl. O programa só pergunta 1 número para o usuário item 3.1.1
        1. Primeiro cenário
            1. O programa pergunta quantos nós (n)
            2. O programa automaticamente gera n nós em sequência com valor aleatório e vai adicionando na árvore
                1. Use srand (time(0));
            3. Ao final, use um código de verificação (slide anterior) para validar a árvore e dar ok
        2. Segundo cenário
            1. Após a execução do primeiro cenário deve testar a árvore com os casos mostrado no seguinte link: https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct


- Estrutura do diretório:
    |_ exercício3-1.c               - Arquivo fonte do programa.
    |_ README.txt                   - Documentação do programa.
    |_ Makefile                     - Arquivo com comandos úteis para a execução do comando.
    |_ questoes_dissertativas.pdf   - Arquivo PDF contendo as respostas para as questões que não envolvem código.


- Como rodar:
    Para rodar o programa desenvolvido basta compilar com o comando "make compile" e, em seguida, rodar o comando "make run".


- Comentários:
    Video de demonstração: O vídeos pode ser acessado pelo link: <Inserir video aqui>

    Segundo cenário: Escolhi utilizar essa sugestão https://stackoverflow.com/a/3958672 para o segundo cenário por recomendação do monitor da diciplina. Porém, também adicionei uma verificação utilizando o terceiro tópico compartilhado no post do StackOverflow citado no exercício, que consiste em um calculo disponibilizado pelos criadores do AVL.