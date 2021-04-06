Autor: Frederico Dal Soglio Reckziegel | fdsreckziegel@inf.ufpel.edu.br


- Enunciado:
    - Faça um programa que armazene a informação de várias pessoas.
        - typedef struct {
            char nome[30];
            int idade;
            int altura;
        }Pessoa;
    - O programa só deve sair quando o usuário disser que não deseja mais entrar com os dados de outra pessoa.
    - Antes de sair o programa deve apresentar, de forma organizada, os dados de todas as pessoas.
    

- Estrutura do diretório:
    |_ exercício5.c - Arquivo fonte do programa.
    |_ README.txt   - Documentação do programa.
    |_ Makefile     - Arquivo com comandos úteis para a execução do comando.
    |_ test.txt     - Arquivo com entradas pré definidas para teste automatizado.


- Como rodar:
    Para rodar o programa desenvolvido basta compilar com o comando "make compile" e, em seguida, rodar o comando "make run". Ou, se preferir, o comando "make test" irá rodar o programa já com as estradas especificadas em "test.txt".


- Comentários:
    Video de demonstração: O vídeos pode ser acessado pelo link: https://drive.google.com/file/d/15BMeHBodAwAdqfb3uBdohZETZEQOjf_F/view?usp=sharing