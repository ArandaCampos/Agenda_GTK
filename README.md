## Banco de Dados com GTK+3.0

![Badge de licença](http://img.shields.io/static/v1?label=LICENÇA&message=GNU&color=sucess&style=for-the-badge)   ![Badge em Desenvolvimento](http://img.shields.io/static/v1?label=STATUS&message=CONCLUÍDO&color=sucess&style=for-the-badge)   ![Badge versionamento](http://img.shields.io/static/v1?label=VERSAO&message=1.0&color=sucess&style=for-the-badge)


## Sobre

<div align="justify"> &emsp; O projeto tem como objetivo por em prática conhecimentos adquiridos durante as aulas de <strong>Lógica de Programação</strong> ,  <strong>Estrutura de dados I</strong> e utilizar o GTK+3.0 com a ferramenta <strong>Glade</strong>.<br/> &emsp; Para isso, escolhi programar um pequeno banco de dados. Por necessitar de estruturas complexas (struct); leitura e escrita de arquivos; e precisar de algumas páginas de interface gráfica, o projeto apresentou-se como uma boa alternativa.<br/> &emsp; A aplicação na sua <strong>versão 1.0</strong> conta funcionalidades de Cadastrar novos dados, Consultar e Alterar dados já cadastrados e Excluir dados armazenados. Toda as funcionalidades estão acessíveis por interfaces gráficas. Nela, o usuário poderá armazenar o Nome, Idade, E-mail e Cidade de algum indivíduo.  
</p>

![menu_principal](https://user-images.githubusercontent.com/87876734/148624277-c6ec92cb-b4d8-41f7-ad5c-3dd63735ca24.png)
![cadastro](https://user-images.githubusercontent.com/87876734/148624280-7ccb7516-6e84-4583-89ae-d51c6252281f.png) ![busca](https://user-images.githubusercontent.com/87876734/148624283-8d838bba-8cc5-45b2-977a-0ad8290fe52d.png)

## Instalação e execução

    $ git clone https://github.com/ArandaCampos/Banco_de_dados_GTK.git 
    
    $ cd Banco_de_dados_GTK/src
    
    $ gcc main.c -o main.out `pkg-config --cflags --libs gtk+-3.0`
        
    $ ./main.out

## Ferramentas Utilizadas

- `C`
- `Glade`
