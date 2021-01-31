#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct{    
    char tipoentrega;
    int pedido [25][2];
    int totalpedido;
    float total;
}Pedido;

typedef struct{
    int id;
    char nome[100];
    int numero;
}Cliente;

typedef struct{
    int cod;
    char nome[50];
    float preço;
}Produto;

FILE *f;
FILE *Lista;
FILE *catalogo;

int menu();

void cadastrapedido(int opc, char nomearquivo[]);
void Cadastracatalogo (char nomearuivo[]);

float somapreço(int pedido[][2], int x, char nomearquivo[]);

float PesquisaCatalogoP (int Codigo, char nomecompra[]);
void PesquisaCatalogoN (int Codigo, char nomecompra[], char nomeP[]);

void continuar();
void cabeçalhoabertura();
void cabeçalhoconfe();
void caixinha();

int main(){
    char nomecompra[50], sn, nomearquivo[65], nomecatalogo[100];
    char ext[5] = ".txt";    
    int opc;

    

    Lista = fopen("Clientes.txt", "wb");

    do{
        opc = menu();

        switch (opc){
            case 1:
                cabeçalhoabertura();

                do{
                    printf("Você está prestes a abrir uma nova compra. Deseja continuar? (s/n)\n");
                    getchar();
                    scanf("%c", &sn);

                }while (sn != 's' && sn != 'n' && sn != 'S' && sn != 'N');

                if (sn == 's' || sn == 'S'){
                    cabeçalhoabertura();

                    printf("Digite o nome da compra\n");
                    getchar();
                    scanf("%s", nomecompra);

                    sprintf(nomearquivo, "%s%s", nomecompra, ext);

                    f = fopen(nomearquivo, "rb");
                    if (f == NULL){
                        cabeçalhoabertura();

                        printf("Será criado um arquivo chamado %s\n", nomearquivo);

                        do{

                            printf("Deseja continuar? (s/n)\n");
                            getchar();
                            scanf("%c", &sn);

                        }while (sn != 's' && sn != 'n' && sn != 'S' && sn != 'N');

                        if (sn == 'S' || sn == 's'){
                            cabeçalhoabertura();

                            f = fopen (nomearquivo, "wb");

                            if (f == NULL)
                                printf("Houve um erro ao criar o arquivo de compra...\n");
                            else
                                printf("Arquivo criado com sucesso. \nAgora será possível cadastrar pedidos nesta compra.\n");
                        }

                    }
                    else{
                        printf("Já existe uma compra com esse nome...\n");
                    }
                }
                else 
                    printf("Cancelado\n");
                break;
            case 2:
                cabeçalhoconfe();

                printf("Digite o nome da compra:\n");
                getchar();
                scanf("%s", nomecompra);
                
                sprintf(nomearquivo, "%s%s", nomecompra, ext);

                f = fopen(nomearquivo, "rb");
                if (f == NULL)
                    printf("Não foi encontrado um arquivo com este nome...\n");
                else{
                    fclose(f);
                    printf("Quantos pedidos deseja cadastrar?\n");
                    scanf("%d", &opc);
                    f = fopen(nomearquivo,"wb");
                    cadastrapedido(opc, nomearquivo);
                    fclose(f);
                }
                opc = 2;
                break;
            case 3:
                printf("A qual compra você deseja adicionar o catálogo?\n");
                getchar();
                scanf("%s", nomecompra);

                sprintf(nomearquivo, "%s%s", nomecompra,ext);
                sprintf(nomecatalogo, "%s%s", "Catalogo", nomearquivo);

                f = fopen(nomearquivo, "rb");
                if (f == NULL){
                    printf("Compra não iniciada, inicie uma compra com este nome para adicionar um catálogo.\n");
                }
                else{
                    fclose(f);
                    sprintf(nomearquivo, "%s%s%s", "Catalogo", nomecompra, ext);

                    catalogo = fopen(nomearquivo, "wb");

                    fseek(catalogo, sizeof(Produto), SEEK_END);
                    Cadastracatalogo(nomearquivo);
                }

                break;
        }
        continuar();
        fflush(stdin);
        
    }while(opc != 4);
    fclose(Lista);
    return 0;
}

void cadastrapedido(int max, char nomearquivo[]){
    int i, id, n, x, y;
    char sn, nome[100], nomeP[100], nomecatalogo[100];
    bool sair;

    x = 0;
    y = 0;
    n = 0;

    Cliente cliente, teste;
    Pedido pedido;

    for (i = 0; i <= max; i++){
        sair = false;

        do{
            printf("Cadastrar por id ou por nome (i/n)? (não afetará o resultado final)\n");
            getchar();
            scanf ("%c", &sn);
        }while (sn != 'i' && sn != 'n');

        if(sn == 'i'){
            printf("Digite o id da cliente:\n");
            scanf("%d", &id);
        }
        else{
            printf("Digite o nome da cliente:\n");
            getchar();
            scanf("%s", nome);
        }

        switch (sn)
        {
        case 'i':
            fseek(Lista, sizeof(Cliente), SEEK_SET);
            while (sair == false && !feof)
            {
                fread(&teste, sizeof(Cliente), 1, Lista);
                if (id == teste.id){
                    sair = true;
                }
            }
            if (sair == false){

                cliente.id = id;

                printf("Digite o Nome do cliente:\n");
                getchar();                    
                scanf("%[^\n]s", cliente.nome);
            }

            break;
        case 'n':
            fseek(Lista, sizeof(Cliente), SEEK_SET);
            while (sair == false && !feof)
            {
                fread(&cliente, sizeof(Cliente), 1, Lista);
                if (strcmp(cliente.nome, nome) == 0){
                    sair = true;
                }
            }
            if (sair == false){

                strcpy(cliente.nome, nome);

                printf("Digite o ID do cliente:\n");
                scanf("%d", &cliente.id);

            }
            break;
        default:
            printf("Digite um valor válido (n ou i)\n");
            getchar();
            scanf("%c", &sn);
            break;

        }
        
        printf("Digite o número do cliente:\n");
        scanf("%d", &cliente.numero);

        printf("%s\n", cliente.nome);
        printf("%d\n", cliente.id);
        printf("%d\n", cliente.numero);   

        printf("Qual o tipo de entrega?\n");
        caixinha();
        getchar();
        scanf("%c", &sn);
        do{
            if (sn != 'g' && sn != 's' && sn != 'x' && sn != 'c'){
                printf("Digite um valor válido (g/s/x/c)\n");
                getchar();
                scanf("%c", &sn);
            }
        }while(sn != 'g' && sn != 's' && sn != 'x' && sn != 'c');
        pedido.tipoentrega = sn;
        sn = 's';

        do{
            y = 0;
            printf("Quantidade de unidades: ");
            scanf("%d", &pedido.pedido[x][y]);
            y++;
            printf("Código do Produto: ");
            scanf("%d", &pedido.pedido[x][y]);
            x = x + 1;

            printf("Deseja cadastrar mais um?\n");
            printf("Digite s para sim ou n para para não.\n");
            getchar();
            scanf("%c", &sn);
            while (sn != 's' && sn != 'n'){
                printf("Valor inválido. Escolha sim ou não (s/n)\n");
                getchar();
                scanf("%c", &sn);
            }
        }while(sn == 's');

        pedido.totalpedido = (float) x;
        pedido.total =(float) somapreço(pedido.pedido, x, nomearquivo);

        printf("%.2f\n", pedido.total);
        printf("%d", pedido.pedido[0][0]);

        printf("Novo Pedido:\n");
        printf("ID: %d /Nome: %s /Número: %d\n", cliente.id, cliente.nome, cliente.numero);
        for (n = 0; n <= x; n++){
            PesquisaCatalogoN(pedido.pedido[n][0], nomearquivo, nomeP);
            printf("%d - %d - %s - %.2f\n", pedido.pedido[n][0], pedido.pedido[n][i], nomeP, PesquisaCatalogoP(pedido.pedido[n][0], nomearquivo));
        }
        printf("Confirme (s/n)\n");
        getchar();
        scanf("%c", &sn);
        while (sn != 's' && sn != 'n'){
            printf("Insira um valor válido (s = sim ou n = não)\n");
            getchar();
            scanf("%c", &sn);
        }
        if (sn == 's'){
            fseek(f, sizeof(Cliente)+sizeof(Pedido), SEEK_END);

            fwrite (&cliente, sizeof(Cliente),1, f);
            fwrite (&pedido, sizeof(Pedido), 1, f);

            if (sair = false){
                fseek(Lista, sizeof(Cliente), SEEK_END);
                fwrite(&cliente, sizeof(Cliente), 1, Lista);
            }
        }
        else
            printf("Pedido cancelado.\n");
    }
}

void Cadastracatalogo (char nomearquivo[]){
    bool sair;
    char sn;
    Produto produto;

    sair = false;

    while(sair == false){
        printf("Código do produto: ");
        scanf("%d" , &produto.cod);

        printf("Nome do produto: ");
        getchar();
        scanf("%[^\n]s", produto.nome);

        printf("Preço do produto: ");
        scanf("%f", &produto.preço);

        printf("Será adicionado: ");
        printf("%d - %s - %.2f\n", produto.cod, produto.nome, produto.preço);
        printf("Deseja continuar? (s/n)\n");  
        getchar(); 
        scanf("%c", &sn);

        while (sn != 's' && sn != 'n'){
            printf("Valor inválido, insira s = sim ou n = não");
            getchar();
            scanf("%c", &sn);
        }

        if (sn == 's'){
            fwrite(&produto, sizeof(Produto), 1, catalogo);
            printf("Produto adicionado ao catálogo.\n");
            getchar();
            scanf("%c", &sn);
        }
        else{
            printf("Ação cancelada\n");
        }

        printf("Deseja adicionar outro pedido? (s/n)\n");
        getchar();
        scanf("%c", &sn);
        
        while (sn != 's' && sn != 'n'){
            printf("Valor inválido, insira s = sim ou n = não");
            getchar();
            scanf("%c", &sn);
        }

        if (sn == 's')
            sair = false;
        else
            sair = true;
    }
}

float somapreço(int pedido[][2], int x, char nomearquivo[]){

    int i, n, qtd;
    float Soma, preço;

    Soma = 0;

    for (i = 0; i <= x ; i++){
        for (n = 0; n <= 1; n++){
            if (n == 0){
                pedido[i][n] = qtd;
            }
            if (n == 1){
                preço = PesquisaCatalogoP(n, nomearquivo);
                printf("%.2f\n", preço);
                if(preço != 0){
                    Soma = (float) Soma + (qtd * preço);
                }

            }
        }
    }

    return Soma;
}

float PesquisaCatalogoP (int Codigo, char nomecompra[]){
    char nomearquivo[60];
    bool sair;
    Produto produto;

    sair = false;
    produto.preço = 0;

    sprintf(nomearquivo, "%s%s", "Catalogo",nomecompra);

    catalogo = fopen(nomearquivo, "rb");

    fseek (catalogo, sizeof(Produto), SEEK_SET);
    
    while (sair == false || !feof){
        fread(&produto, sizeof(Produto), 1, catalogo);
        if (produto.cod == Codigo){
            sair = true;
        }
    }
    fclose(catalogo);
    return produto.preço;
}

void PesquisaCatalogoN (int Codigo, char nomecompra[], char nomeP[]){
    char nomearquivo[60], nome[50];
    bool sair;
    Produto produto;

    sair = false;
    produto.preço = 0;

    sprintf(nomearquivo, "%s%s", "Catalogo", nomecompra);

    catalogo = fopen(nomearquivo, "rb");

    fseek (catalogo, sizeof(Produto), SEEK_SET);
    
    while (sair == false || !feof){
        fread(&produto, sizeof(Produto), 1, catalogo);
        if (produto.cod == Codigo){
            sair = true;
        }
    }
    strcpy(nome, produto.nome);
    fclose(catalogo);
}

int menu(){
    int opc;

    system("clear||cls");
    printf("--------------- Menu ---------------\n");
    printf("1 - Abrir compra.\n");
    printf("2 - Cadastrar pedidos.\n");
    printf("3 - Inserir catálogo\n");
    scanf ("%d", &opc);

    return opc;
}

void continuar(){
    char qualquercoisa;

    printf("----------------------------------------\n");
    printf("Aperte enter para continuar\n");
    getchar();
    scanf("%c", &qualquercoisa);
}

void cabeçalhoabertura(){
    system ("clear||cls");
    printf("---------- Abertura de Compra ----------\n");
}

void cabeçalhoconfe(){
    system ("clear||cls");
    printf("---------- Cadastro de pedido ----------\n");
}

void caixinha(){
    printf("--------------------------------\n");
    printf("|g = Guará 2                   |\n");
    printf("|s = SQN 202                   |\n");
    printf("|x = Entrega Exclusíva         |\n");
    printf("|c = Entrega com outros pedidos|\n");
    printf("--------------------------------\n");
}
