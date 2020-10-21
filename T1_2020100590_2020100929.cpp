#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * Aluno 1: André Mury de Carvalho                - 2020100590
 * Aluno 2: Jonathan de Oliveira Teodoro de Souza - 2020100929
 */

struct NoDupla
{
    int Info;
    char Nome[100];
    int Nota;
    NoDupla * Ant[3];                       //Vetores que informam as ligações de um node, 0 - Nível 1, 1 - Nível 2, 2 - Nível 3
    NoDupla * Pos[3];
};

typedef NoDupla *NoPtrDupla;

struct Descritor{
    NoDupla* inicio[3];                     //0 - Nível 1, 1 - Nível 2, 2 - Nível 3
    NoDupla* fim[3];
    int tam;
};


/**
 * Função para alocar nó e setar ligações
 * @param valor é um inteiro - representa a matrícula
 * @param nome é um char[100]
 * @param nota é um inteiro
 * @return NoPtrDupla
 */
NoPtrDupla alocaNO(int valor, char nome[100], int nota){

    NoPtrDupla no = new NoDupla;

    for(int i = 0; i <3; i++){
        no->Ant[i] = NULL;
        no->Pos[i] = NULL;
    }

    no->Info = valor;
    strcpy(no->Nome, nome);
    no->Nota = nota;

    return no;
}

/**
 * Função para inserir um nó na lista
 * @param L é um Descritor
 * @param Novo é um inteiro - representa a matrícula
 * @param Nome é um char[100]
 * @param Nota é um inteiro
 */
void InsereListaDupla (Descritor &L, int Novo, char Nome[100], int Nota){
    if (L.inicio[0] == NULL) {
        NoPtrDupla no = alocaNO(Novo, Nome, Nota);
        L.inicio[0] = no;
        L.fim[0] = no;

        if(Novo % 5 == 0){
            L.inicio[1] = no;
            L.fim[1] = no;
        }
        if(Novo % 20 == 0){
            L.inicio[2] = no;
            L.fim[2] = no;
        }
    }
    else {
        NoPtrDupla Aux = L.inicio[0];
        NoPtrDupla Ant = NULL;
        NoPtrDupla Ant5 = NULL;
        NoPtrDupla Ant20 = NULL;

        while ((Aux != NULL) && (Aux->Info < Novo)) {
            if(Aux->Info % 5 == 0)
                Ant5 = Aux;
            if(Aux->Info % 20 == 0)
                Ant20 = Aux;
            Ant = Aux;
            Aux = Aux->Pos[0];
        }

        Aux = alocaNO(Novo, Nome, Nota);

        /****************Inserção Nível 1****************/

        if(Ant == NULL){
            Aux->Pos[0] = L.inicio[0];
            L.inicio[0]->Ant[0] = Aux;
            L.inicio[0] = Aux;
        }else{

            if(Ant->Pos[0] != NULL){
                Ant->Pos[0]->Ant[0] = Aux;
                Aux->Pos[0] = Ant->Pos[0];
            }
            else
                L.fim[0] = Aux;

            Ant->Pos[0] = Aux;
            Aux->Ant[0] = Ant;
        }

        /****************Inserção Nível 2****************/
        if(Novo % 5 == 0){
            if(Ant5 != NULL){
                if(Ant5->Pos[1] == NULL){
                    L.fim[1] = Aux;
                }else{
                    Ant5->Pos[1]->Ant[1] = Aux;
                    Aux->Pos[1] = Ant5->Pos[1];
                }
                Ant5->Pos[1] = Aux;
                Aux->Ant[1] = Ant5;

            }else{
                if(L.inicio[1] == NULL){
                    L.inicio[1] = Aux;
                    L.fim[1] = Aux;
                }else{
                    L.inicio[1]->Ant[1] = Aux;
                    Aux->Pos[1] = L.inicio[1];
                    L.inicio[1] = Aux;
                }
            }
        }

        /****************Inserção Nível 3****************/
        if(Novo % 20 == 0){
            if(Ant20 != NULL){
                if(Ant20->Pos[2] == NULL){
                    L.fim[2] = Aux;
                }else{
                    Ant20->Pos[2]->Ant[2] = Aux;
                    Aux->Pos[2] = Ant20->Pos[2];
                }
                Ant20->Pos[2] = Aux;
                Aux->Ant[2] = Ant20;

            }else{
                if(L.inicio[2] == NULL){
                    L.inicio[2] = Aux;
                    L.fim[2] = Aux;
                }else{
                    L.inicio[2]->Ant[2] = Aux;
                    Aux->Pos[2] = L.inicio[2];
                    L.inicio[2] = Aux;
                }
            }
        }

        L.tam += 1;
    }
}


/**
 * Função para printar a lista
 * @param D é um Descritor
 * Dica: Caso deseje visualizar os níveis 2 e 3, basta descomentar o código.
 */
void printList(Descritor D){

    NoPtrDupla aux = D.inicio[0];

    printf("\n\nNivel1\n");
    printf("\n\n--------------------------------ALUNOS--------------------------------");

    while( aux != NULL ){
        printf("\n\t Matricula: %d \t\n \t Nome: %s \t\n\t Nota: %d \t\t\t\t", aux->Info, aux->Nome, aux->Nota);
        printf("\n----------------------------------------------------------------------\n");
        aux = aux->Pos[0];

    }

    /*
    printf("\n\nNivel2\n");
    printf("\n\t**********************************************");
    aux = D.inicio[1];
    while( aux != NULL ){
        printf("\n\t|Matricula: %d Nome: %s Nota: %d |", aux->Info, aux->Nome, aux->Nota);
        aux = aux->Pos[1];
    }
    printf("\n\t**********************************************");
    */

    /*
    printf("\n\nNivel3\n");
    printf("\n\t**********************************************");
    aux = D.inicio[2];
    while( aux != NULL ){
        printf("\n\t|Matricula: %d Nome: %s Nota: %d |", aux->Info, aux->Nome, aux->Nota);
        aux = aux->Pos[2];
    }
    printf("\n\t**********************************************");
    */
}

/**
 * Função para consultar uma matrícula na lista
 * @param D é um Descritor
 * @param valor é inteiro, que vai ser buscado na lista
 * @return NoPtrDupla
 */
NoPtrDupla consulta(Descritor D, int valor){

    NoPtrDupla ultimo = NULL;
    int index = D.inicio[2] != NULL ? 2 : D.inicio[1] != NULL ? 1 : 0;
    NoPtrDupla aux = D.inicio[index];

    while(aux != NULL && aux->Info != valor){
        //printf("\n\tTrace while: %d", aux->Info);

        if(aux->Info < valor){
            if(aux->Pos[index] != NULL && ultimo != aux->Pos[index]){
                //printf("\n\tTrace 1++: %d", aux->Info);
                ultimo = aux;
                aux = aux->Pos[index];
            }else{
                index--;
                if(aux->Pos[index] != NULL && ultimo != aux->Ant[index]){
                    //printf("\n\tTrace 2++: %d", aux->Info);
                    ultimo = aux;
                    aux = aux->Pos[index];
                }else{
                    index--;
                    if(aux->Pos[index] != NULL && ultimo != aux->Ant[index]){
                        //printf("\n\tTrace 3++: %d", aux->Info);
                        ultimo = aux;
                        aux = aux->Pos[index];
                    }else
                        return NULL;
                }
            }
        }else{
            if(aux->Ant[index] != NULL && ultimo != aux->Ant[index]){
                //printf("\n\tTrace 1 --: %d", aux->Info);
                ultimo = aux;
                aux = aux->Ant[index];
            }else{
                index--;
                if(aux->Ant[index] != NULL && ultimo != aux->Ant[index]){
                    //printf("\n\tTrace 2 --: %d", aux->Info);
                    ultimo = aux;
                    aux = aux->Ant[index];
                }else{
                    index--;
                    if(aux->Ant[index] != NULL && ultimo != aux->Ant[index]){
                        //printf("\n\tTrace 3 --: %d", aux->Info);
                        ultimo = aux;
                        aux = aux->Ant[index];
                    }else
                        return NULL;
                }
            }
        }
    }

    return aux;
}

/**
 * @param D é um Descritor
 * @param no é um NoPtrDupla, que vai ser removido
 * @return booleano
 */
bool removerNo(Descritor &D, NoPtrDupla no){

    for(int i = 2; i >=0; i--){



        if(D.inicio[i] == no){
            D.inicio[i] = no->Pos[i];
        }

        if(D.fim[i] == no)
            D.fim[i] = no->Ant[i];

        if(no->Ant[i])
            no->Ant[i]->Pos[i] = no->Pos[i];

        if(no->Pos[i])
            no->Pos[i]->Ant[i] = no->Ant[i];
    }

    delete no;
    D.tam--;
}

/**
 * Função para iniacializar lista
 * @param D é um Descritor
 */
void iniciaLista(Descritor &D){

    for(int i = 0; i <3; i++){
        D.inicio[i] = NULL;
        D.fim[i] = NULL;
    }

    D.tam = 0;

}


void choice(int opt, Descritor &D)
{
    int
        matricula = 0,
        nota = 0;
    char nome[100], remover;
    NoPtrDupla no;

    switch (opt)
    {
    case 1:
        while (matricula != -1)
        {
            printf("\n\t Digite a matricula para inserir: ");
            scanf("%d", &matricula);
            if(matricula == -1)
                break;
            printf("\n\t Digite o nome do aluno: ");
            scanf(" %s", &nome);
            printf("\n\t Digite a nota (int): ");
            scanf("%d", &nota);
            printf("\n");
            InsereListaDupla(D, matricula, nome, nota);

        }
        break;
    case 2:
        while (matricula != -1)
        {
            printList(D);
            printf("\n\t Digite a matricula para buscar: ");
            scanf("%d", &matricula);
            if(matricula == -1)
                break;

            no = consulta(D, matricula);

            if(no){
                printf("\n\t Deseja remover o aluno %s (s/n)", no->Nome);
                scanf(" %c", &remover);
                if(remover == 's' && removerNo(D, no))
                    printf("\n Aluno removido.\n");
            }else
            printf("\n\tMatricula pesquisada nao existe!");

        }
        break;

    default:
        printf("\n\tValor invalido. \n");
        system("./main");
    }
}

void interface(Descritor &d){

    int opt = 0;
    system("cls");

    printf("\n-------------------------TRABALHO PCO001-------------------------\n");
    printf("|\t Selecione uma opcao abaixo para executar a questao:     |\n");
    printf("|\t (1) Adicionar um aluno na lista                         |\n");
    printf("|\t (2) consultar/remover um aluno na lista                 |\n");
    printf("|\t Digite -1 para sair das opcoes                          |");
    printf("\n-----------------------------------------------------------------\n");

    while (opt < 1)
    {
        printf("\nOpcao: ");
        scanf("%d", &opt);
        if(opt == -1)
            exit(1);
        printf("\n");
    }
    choice(opt, d);
}

int main(){

    Descritor d;
    char go = 'S';

    iniciaLista(d);

    while(go == 'S'){
        interface(d);
        printf("\nTecle <S> para voltar ao menu ou <N> para sair. \n");
        scanf(" %c", &go);
    }

    return 0;
}
