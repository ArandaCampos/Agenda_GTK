/***********************************************
 *
 * Autor: RENAN ARANDA CAMPOS
 *
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

typedef struct{
    char Nome[30];
    int Idade;
    char Email[50];
    char Cidade[25];
} Cadastro;
typedef Cadastro *pCadastro;

GtkBuilder *construtor;
GtkWidget *wJanela, *wInserir, *wAlterar, *wConsultar, *wApagar,
          *wAlterar1, *wPopUpConcluido, *wPopUpConfirmacao,
          *wPopUpAlerta;
int linha;

int Localizar(const char *nome, int pagina){
    int i = 0, linha  = 0, c = 0, tamanho = 0;
    char *chave = (char *)malloc(50 * sizeof(char));
    char idade[3];

    // Atribui o nome a var chave
    // Atribui o tamanho de chave à var tamanho
    strcpy(chave, nome);
    tamanho = strlen(chave);

    // Abre o arquivo dados.txt
    FILE *arq = fopen("dados.txt", "w");
    fclose(arq);
    arq = fopen("dados.txt", "r");

    //if (arq == NULL) printf("NULL");

    // Aloca memória
    pCadastro pdados = (pCadastro)malloc(sizeof(Cadastro));

    // Busca pelo nome no dados.txt
    do  {
	    linha++;
	    fscanf(arq, "%s %d %s %s", pdados->Nome, &pdados->Idade, pdados->Email, pdados->Cidade);
	    for (i = 0; i < tamanho; i ++){
	        if (pdados->Nome[i] != chave[i]) break;
	        else if (i == tamanho - 1 && pdados->Nome[i + 1] == 0) {
		        sprintf(idade,"%d", pdados->Idade);
                if (pagina == 1){
                    // Imprime os dados encontrados
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdade1")), idade);
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmail1")), pdados->Email);
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidade1")), pdados->Cidade);
                } else if (pagina == 0){
                    // Imprime os dados encontrados
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdadeA")), idade);
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmailA")), pdados->Email);
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidadeA")), pdados->Cidade);
                } else if (pagina == 2){
                    // Imprime os dados encontrados
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdade2")), idade);
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmail2")), pdados->Email);
	    	        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidade2")), pdados->Cidade);
                }
                // Desalocar a memoria e fechar o arquivo
                free(pdados);
                free(chave);
                fclose(arq);
                return linha;
	        }
	    }
    } while ((c = fgetc(arq)) != EOF);

    // ALTERAR!!!!! adicionar um alert com o texto abaixo
    gtk_widget_show_all(wPopUpAlerta);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lMsgPopUpAlerta")), "Dado não existente!");

    // Desaloca a memoria e fecha o arquivo
    free(pdados);
    free(chave);
    fclose(arq);

    return 0;
}

void ExibirDados(int l){
    int i = 0;
    char idade[3];
    FILE *arq = NULL;
    pCadastro pdados = (pCadastro)malloc(sizeof(Cadastro));

    arq = fopen("dados.txt", "r");

    for(; i < l; i++) fscanf(arq, "%s %d %s %s", pdados->Nome, &pdados->Idade, pdados->Email, pdados->Cidade);

	sprintf(idade,"%d", pdados->Idade);
	gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eNome1")), pdados->Nome);
	gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eIdade1")), idade);
	gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eEmail1")), pdados->Email);
	gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eCidade1")), pdados->Cidade);

    free(pdados);
    fclose(arq);
}

void Alterar(int l, int identificador){
    int i = 0, c = 0, dado = 0, copiar = 1;
    FILE *temp = NULL, *arq = NULL;
    const char *nome, *idade, *email, *cidade;
    // Cria, caso não exista, o arquivo temp.txt e abre dados.txt
    arq = fopen("dados.txt", "r");
    temp = fopen("temp.txt", "w");

    // Aloca memória
    pCadastro pdados = (pCadastro)malloc(sizeof(Cadastro));

    fscanf(arq, "%s %d %s %s", pdados->Nome, &pdados->Idade, pdados->Email, pdados->Cidade);
    // Transcreve do dados.txt para o temp.txt
    do {
        copiar = 1;
        i++;
        // Localiza os dados a serem alterados
	    if (i == l && identificador){
		    nome = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eNome1")));
	    	idade = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eIdade1")));
	    	email = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eEmail1")));
	    	cidade = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eCidade1")));
		    pdados->Idade = atoi(idade);
		    sprintf(pdados->Nome,"%s", nome);
		    sprintf(pdados->Email,"%s", email);
		    sprintf(pdados->Cidade,"%s", cidade);
        } else if (i == l && !identificador){
            copiar = 0;
        }
        if (copiar){
            fprintf(temp, "%s %d %s %s\n", pdados->Nome, pdados->Idade, pdados->Email, pdados->Cidade);
        }
        fscanf(arq, "%s %d %s %s", pdados->Nome, &pdados->Idade, pdados->Email, pdados->Cidade);
    } while ((c = fgetc(arq)) != EOF);	// Percorre o arquivo até o fim

    // Fecha os arquivos
    fclose(arq);
    fclose(temp);

    // Abre o arquivo temp.txt e sobrescreve o carros.txt
    arq = fopen("dados.txt", "w");
    temp = fopen("temp.txt", "r");

    // Transfere do arquivo temp.txt para o carros.txt
    while (i > 0) {
        --i;
        fscanf(temp, "%s %d %s %s", pdados->Nome, &pdados->Idade, pdados->Email, pdados->Cidade);
        fprintf(arq, "%s %d %s %s\n", pdados->Nome, pdados->Idade, pdados->Email, pdados->Cidade);
    }

    // Desaloca a memória e fecha os arquivos
    free(pdados);
    fclose(arq);
    fclose(temp);

    // Apaga o arquito temporário temp.txt
    system("rm temp.txt");
}

void Inserir(const char *pNome, int pIdade, const char *pEmail, const char *pCidade){
    int i = 0;
    // Aloca memória
    pCadastro pdados = (pCadastro)malloc(sizeof(Cadastro));

    // Abre o arquivo dados.txt no modo escrita a
    FILE *arq =  fopen("dados.txt", "a");

    // Atribui as entrada à estrutura Cadastro
    strcpy(pdados->Nome, pNome);
    pdados->Idade = pIdade;
    strcpy(pdados->Email, pEmail);
    strcpy(pdados->Cidade, pCidade);

    // Registro no arquivo
    fprintf(arq, "%s %d %s %s\n", pdados->Nome, pdados->Idade, pdados->Email, pdados->Cidade);

    // Liberar memória
    free(pdados);
    fclose(arq);
}

// Funcionalidade do 'x' na aba superior dos PopUp
void on_bPopUp_destroy(GtkWidget *widget, gpointer data){
    gtk_widget_hide(data);
}

// Funcionalidade do botão Ok da Janela wPopUpAlerta
void on_bOkAlerta_clicked(GtkWidget *widget, gpointer data){
    gtk_widget_hide(data);
}

// Funcionalidade do botão Ok da Janela wPopUpConcluido
void on_bOkPopUp_clicked(GtkWidget *widget, gpointer data){
    // Oculta a janela wPopUpConcluido
    // e retorna a Janela Principal
    gtk_widget_hide(data);
    gtk_widget_show_all(wJanela);
}

// Funcionalidade do botçao Confirmar da Janela wPopUpConfirmacao
void on_bConfirmarPopUp_clicked (GtkWidget *widget, gpointer data){
    // Realiza a alteração
    Alterar(linha, 0);

    gtk_widget_hide(wPopUpConfirmacao);

    // Apagar o texto digita pelo usuário nos campos
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdade2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmail2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidade2")), "");
    gtk_widget_hide(wAlterar);

    // Retorna à Janlea principal
    //gtk_widget_hide(wPopUpConfirmacao);
    gtk_widget_hide(wApagar);
    gtk_widget_show_all(wJanela);
    gtk_widget_show_all(wPopUpConcluido);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lMsgPopUpConfirmacao")), "Exclusão concluída com sucesso");
}

// Funcionalidade do botão Cancelar da Janela wPopUpConfirmacao
void on_bCancelarPopUp_clicked (GtkWidget *widget, gpointer data){
    // Retornar à janela anterior
    gtk_widget_hide(data);
    gtk_widget_show_all(wApagar);

    // Apagar o texto digita pelo usuário nos campos
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdade2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmail2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidade2")), "");

}

// Funcionalidade do botao Apagar da Janela wApagar
void on_bApagar1_clicked(GtkWidget *widget, gpointer data){
    // Exibe PopUp de confirmação
    if(linha != 0){
        // Alterar as janelas
        gtk_widget_show_all(wPopUpConfirmacao);
    } else {
        // EXIBIR POPUP de ALERTA na tela
        gtk_widget_show_all(wPopUpAlerta);
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lMsgPopUpAlerta")), "Informe os dados a serem alterado!");
    }
}

// Funcionalidade do botao Consultar da Janela wApagar
void on_bBuscar2_clicked(GtkWidget *widget, gpointer data){
    const char *pBuscar = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar2")));

    linha = Localizar(pBuscar, 2);
}

// Funcionalidade do botão Confirmar da Janela wAlterar1
void on_bConfirmar_clicked(GtkWidget *widget, gpointer data){
    Alterar(linha, 1);

    // Retornar à janela principal
    // e exibe o PopUp de confirmação
    gtk_widget_hide(data);
    gtk_widget_show_all(wJanela);
    gtk_widget_show_all(wPopUpConcluido);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lMsgPopUpConfirmacao")), "Alteração concluída com sucesso");
}

// Funcionalidade do botão Alterar da Janela wAlterar
void on_bAlterar1_clicked(GtkWidget *widget, gpointer data){
    if(linha != 0){
        // Alterar as janelas
        gtk_widget_hide(data);
        gtk_widget_show_all(wAlterar1);

        // função que seta os dados
        ExibirDados(linha);
    } else {
        // EXIBIR POPUP de ALERTA na tela
        gtk_widget_show_all(wPopUpAlerta);
        gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lMsgPopUpAlerta")), "Informe os dados a serem alterado!");
    }
}

// Funcionalidade do botão Buscar da Janela wAlterar
void on_bBuscar_clicked(GtkWidget *widget, gpointer data){
    const char *pBuscar = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar")));

    linha = Localizar(pBuscar, 0);
}

// Funcionalidade do botão Buscar da janela wConsultar
void on_bBuscar1_clicked(GtkWidget *widget, gpointer data){
    const char *pBuscar = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar1")));

    Localizar(pBuscar, 1);
}

// Funcionalidade do botão Enviar da Janela wInserir
void on_bEnviar_clicked(GtkWidget *widget, gpointer data){

    // Pega o nome digitado nos campos
    const char *pNome = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eNome")));
    int pIdade = atoi((char *)gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eIdade"))));
    const char *pEmail = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eEmail")));
    const char *pCidade = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(construtor,"eCidade")));

    // Chamar a função que insere os dados no arquivo dados.txt
    Inserir(pNome, pIdade, pEmail, pCidade);

    // Apagar o texto digita pelo usuário nas Entries
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eNome")), "");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eIdade")), "");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eEmail")), "");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eCidade")), "");

    // Exibe a confirmação do cadastro
    // e retorna à janela principal
    gtk_widget_hide(data);
    gtk_widget_show_all(wJanela);
    gtk_widget_show_all(wPopUpConcluido);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lMsgPopUpConfirmacao")), "Cadastro concluído com sucesso");
}

// Funcionalidade do botão Cancelar da Janela wApagar
void on_bCancelar3_clicked(GtkWidget *widget, gpointer data){
    // Apagar o texto digita pelo usuário nos campos
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdade2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmail2")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidade2")), "");

    // Voltar a Janela Principal
    gtk_widget_hide(data);
    gtk_widget_show_all(wJanela);
}

// Funcionalidade do botão Cancelar da Janela wAlterar
void on_bCancelar2_clicked(GtkWidget *widget, gpointer data){
    gtk_widget_hide(data);
    gtk_widget_show_all(wJanela);

    // Apagar o texto digita pelo usuário nos campos
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdadeA")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmailA")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidadeA")), "");
}

// Funcionalidade do botão Cancelar da Janela wAlterar1
void on_bCancelar1_clicked(GtkWidget *widget, gpointer data){

    // Retorna à janela principal
    gtk_widget_hide(data);
    gtk_widget_show_all(wAlterar);

    // Apagar o texto digita pelo usuário nos campos
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdadeA")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmailA")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidadeA")), "");
}


// Funcionalidade do botão Cancelar da Janela wInserir
void on_bCancelar_clicked(GtkWidget *widget, gpointer data){

    // Apagar o texto digita pelo usuário nas Entries
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eNome")), "");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eIdade")), "");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eEmail")), "");
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eCidade")), "");

    // Retorna à janela principal
    gtk_widget_hide(data);
    gtk_widget_show_all(wJanela);
}

void on_bVoltar_clicked(GtkWidget *widget, gpointer data){
    // Apagar o texto digita pelo usuário nos campos
    gtk_entry_set_text(GTK_ENTRY(gtk_builder_get_object(construtor, "eBuscar1")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lIdade1")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lEmail1")), "");
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(construtor, "lCidade1")), "");

    // Retorna a Janela Principal
    gtk_widget_hide(data);
    gtk_widget_show_all(wJanela);
}

void on_window_destroy(GtkWidget *widget, gpointer data){
    // Encerra a aplicação
    gtk_main_quit();
}

void on_opcao_clicked(GtkWidget *widget, gpointer data){
    // Abre a próxima janela
    gtk_widget_hide(wJanela);
    gtk_widget_show_all(data);
    linha = 0;
}

int main(int argc, char *argv[]){
    // Inicia o GTK e instancia o construtor
    gtk_init(&argc, &argv);
    construtor = gtk_builder_new_from_file("front.glade");

    // Constroi a conexão entre os botões e as funções
    gtk_builder_add_callback_symbols(
            construtor,
            "on_window_destroy",            G_CALLBACK(on_window_destroy),
            "on_opcao_clicked",             G_CALLBACK(on_opcao_clicked),
            "on_bCancelar_clicked",         G_CALLBACK(on_bCancelar_clicked),
            "on_bCancelar1_clicked",        G_CALLBACK(on_bCancelar1_clicked),
            "on_bCancelar2_clicked",        G_CALLBACK(on_bCancelar2_clicked),
            "on_bCancelar3_clicked",        G_CALLBACK(on_bCancelar3_clicked),
            "on_bVoltar_clicked",           G_CALLBACK(on_bVoltar_clicked),
            "on_bEnviar_clicked",           G_CALLBACK(on_bEnviar_clicked),
            "on_bBuscar_clicked",           G_CALLBACK(on_bBuscar_clicked),
            "on_bBuscar1_clicked",          G_CALLBACK(on_bBuscar1_clicked),
            "on_bBuscar2_clicked",          G_CALLBACK(on_bBuscar2_clicked),
            "on_bAlterar1_clicked",         G_CALLBACK(on_bAlterar1_clicked),
            "on_bConfirmar_clicked",        G_CALLBACK(on_bConfirmar_clicked),
            "on_bOkPopUp_clicked",          G_CALLBACK(on_bOkPopUp_clicked),
            "on_bOkAlerta_clicked",         G_CALLBACK(on_bOkAlerta_clicked),
            "on_bCancelarPopUp_clicked",    G_CALLBACK(on_bCancelarPopUp_clicked),
            "on_bConfirmarPopUp_clicked",   G_CALLBACK(on_bConfirmarPopUp_clicked),
            "on_bApagar1_clicked",          G_CALLBACK(on_bApagar1_clicked),
            "on_bPopUp_destroy",            G_CALLBACK(on_bPopUp_destroy),
            NULL);

    // Instancia todas as janelas da aplicação
    gtk_builder_connect_signals(construtor, NULL);
    wJanela = GTK_WIDGET(gtk_builder_get_object(construtor, "wJanela"));
    wInserir = GTK_WIDGET(gtk_builder_get_object(construtor, "wInserir"));
    wConsultar = GTK_WIDGET(gtk_builder_get_object(construtor, "wConsultar"));
    wAlterar = GTK_WIDGET(gtk_builder_get_object(construtor, "wAlterar"));
    wAlterar1 = GTK_WIDGET(gtk_builder_get_object(construtor, "wAlterar1"));
    wApagar = GTK_WIDGET(gtk_builder_get_object(construtor, "wApagar"));
    wPopUpConcluido = GTK_WIDGET(gtk_builder_get_object(construtor, "wPopUpConcluido"));
    wPopUpConfirmacao = GTK_WIDGET(gtk_builder_get_object(construtor, "wPopUpConfirmacao"));
    wPopUpAlerta = GTK_WIDGET(gtk_builder_get_object(construtor, "wPopUpAlerta"));

    // Habilita mostrar a aplicação na tela do usuário
    gtk_widget_show_all(wJanela);
    gtk_main();

    return 0;
}
