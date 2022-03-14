#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoas
{
    int ID;
    char Nome[40];
    char Cpf[14];
    char Telefone[15];
    char Endereco[100];
} Pessoas;

typedef struct Forsafe//Criado outras Sctruct identica pois Nao estava Conseguindo carregar a struct com mesmo nome
{
    int ID;
    char Nome[40];
    char Cpf[14];
    char Telefone[15];
    char Endereco[100];
} Forsafe;

void formatacpf(char T[])
{
    int i, j = 1;
    for (i = 0; i < 11; i++, j++)
    {
        printf("%c", T[i]);
        if (i == 8)
            printf("-");
        else if ((j == 3))
        {
            printf(".");
            j = 0;
        }
    }
}

void formatacell(char T[])
{
    int i;
    for (i = 0; i < 11; i++)
    {
        if (i == 0)
            printf("(");
        if (i == 2)
            printf(")");
        else if ((i == 7))
        {
            printf("-");
        }
        printf("%c", T[i]);
    }
}

// int Verificar_ID(struct Pessoas T[], int a)
// { // se um Id ja estiver sendo usado ira dar erro
//     int i = 0;
//     FILE *file;
//     file = fopen("quantidade_usuarios.txt", "r");
//     while(fscanf(file,"%d",&a) != EOF)
//     {
//         if (fscanf(file, "%d", T[i].ID) == a)
//             return 1; // 1==TRUE
//     }
//     return 0; // 0==FALSE
// }

// int Verificar_Dados()
// { // se um dado dor igual a outro cliente cadatrato, ira recusar
// }

void carregar(Pessoas P[])//!!!!!!!!!FUNÇAO QUE CARREGA O PROGRAMA !!!!!!!!!
{
    int i = 1;
    for (i = 0; i < 30; i++)
        P[i].ID = 0;
    
    Forsafe F;
    FILE *file = fopen("database.bin", "rb");
    i=1;
    while (fread(&F, sizeof(Forsafe), 1, file))
    {
        P[i].ID = F.ID;
        strcpy(P[i].Nome, F.Nome);
        strcpy(P[i].Cpf, F.Cpf);
        strcpy(P[i].Telefone, F.Telefone);
        strcpy(P[i].Endereco, F.Endereco);
        i++;
    }
    fclose(file);
}

void salvar(Pessoas P[])//!!!!!!!!!FUNÇAO QUE Salva Todas As Modificaçoes DO PROGRAMA 
{
    int i = 1;
    Forsafe F;
    remove("database.bin");
    FILE *file = fopen("database.bin", "ab");
    
    while (1)
    {
        if(i==30)
            break;
        fwrite(&P[i], sizeof(Pessoas), 1, file);
        i++;
    }

    fclose(file);
}

void cadastro(struct Pessoas T[])
{
    int total = 0, Ids;
    int ID;
    system("cls");
    printf("Digite o ID do Novo Cliente: ");
    scanf("%d", &ID);

    // PARTE Q  salvadados usuarios
    FILE *file = fopen("database.bin", "ab");
    ;
    //=======================
    T[ID].ID = ID;

    system("cls");
    setbuf(stdin, NULL);
    printf("Programa loja de construcao!!\n");
    printf("Nome:");
    scanf("%[^\n]s", T[ID].Nome);
    system("cls");
    // LIMPA BUFFER
    setbuf(stdin, NULL);
    printf("Programa loja de construcao!!\n");
    printf("Digite o numero do CPF sem pontos, espacos ou tracos:");
    scanf("%s", T[ID].Cpf);
    system("cls");

    // LIMPAR BUFFER
    setbuf(stdin, NULL);
    printf("Programa loja de construcao!!\n");
    printf("endereco:");
    scanf("%[^\n]s", T[ID].Endereco);
    system("cls");

    // LIMPA BUFFER
    setbuf(stdin, NULL);
    printf("Programa loja de construcao!!\n");
    printf("telefone:");
    scanf("%s", T[ID].Telefone);
    system("cls");
    //==SALVA A STRUCT EM BINARIO
    fwrite(&T[ID], sizeof(Pessoas), 1, file);
    fclose(file);
}

void editar(struct Pessoas T[])
{
    int opcao, ID;
    system("cls");
    printf("Digite o Numero de indetificacao do clitente cadastrado!!\n");
    printf("ID : ");
    scanf("%d", &ID);
    system("cls");

    printf("Selecione o dado que deseja alterar!!\n");
    printf("1- Nome\n");
    printf("2- CPF\n");
    printf("3- endereco\n");
    printf("4- telefone\n");

    printf("Dado : ");
    scanf("%d", &opcao);
    system("cls");

    if (opcao == 1)
    {
        // LIMPA BUFFER
        setbuf(stdin, NULL);
        printf("Nome:");
        scanf("%[^\n]s", T[ID].Nome);
        system("cls");
    }
    if (opcao == 2)
    {
        printf("Digite o numero do CPF sem pontos, espacos ou tracos:");
        scanf("%s", T[ID].Cpf);
        system("cls");
    }
    if (opcao == 3)
    {
        // LIMPA BUFFER
        setbuf(stdin, NULL);
        printf("endereco:");
        scanf("%[^\n]s", T[ID].Endereco);
        system("cls");
    }
    if (opcao == 4)
    {
        printf("telefone:");
        scanf("%s", T[ID].Telefone);
        system("cls");
    }
}

void excluir(struct Pessoas T[])
{
    system("cls");
    int ID, opcao;
    printf("Digite o Numero de indetificacao do clitente cadastrado!!\n");
    printf("ID : ");
    scanf("%d", &ID);
    system("cls");
    printf("Editando a Conta ID: %d\n", ID);
    printf("Selecione o dado que ddeseja excluir!!\n");
    printf("1- Nome\n");
    printf("2- CPF\n");
    printf("3- endereco\n");
    printf("4- telefone\n");
    printf("5- Sair\n");

    printf(":");
    scanf("%d", &opcao);
    system("cls");
    while (1)
    {
        if (opcao == 1)
        {
            printf("Nome removido!!");
            strcpy(T[ID].Nome, "Sem dado");
            system("cls");
        }
        if (opcao == 2)
            printf("CPF removido!!");
        strcpy(T[ID].Cpf, "0");
        system("cls");
        break;
        if (opcao == 3)
            printf("endereco removido!!");
        strcpy(T[ID].Endereco, "Sem dado");
        system("cls");
        break;
        if (opcao == 4)
            printf("telefone removido!!");
        strcpy(T[ID].Telefone, "0");
        system("cls");
        break;
        if (opcao == 5)
            break;
        if (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 && opcao != 5) // SE nenhuma das opçoes acontecer
            system("cls");
        printf("Numero Invalido!\n");
    }
}

void mostra(struct Pessoas T[]) // imprime todas as pessoas que o programa tem
{
    int i, j, total = 0;
    int ID;
    for (ID=1;ID<30;ID++)
    {
        if(T[ID].ID==0)
            continue;
            printf("-------------------------------------\n");
            printf("|ID :%d\n", T[ID].ID);
            printf("|Nome :%s\n", T[ID].Nome);
            printf("|CPF : ");
            formatacpf(T[ID].Cpf);
            printf("\n|Tell : ");
            formatacell(T[ID].Telefone);
            printf("\n|Endereco :%s\n", T[ID].Endereco);
            printf("-------------------------------------\n");
    }
    system("Pause");
    system("cls");
}

void mostra1(struct Pessoas T[])
{
    system("cls");
    while (1)
    {
        int ID;
        char escolha = 'h';
        printf("Digite o ID do cliente que deseja ver as informacoes: ");
        scanf("%d", &ID);
        printf("Nome: %s \nCPF: ", T[ID].Nome);
        // formatacpf(ID, T);
        printf("\nTelefone: ");
        // formatacell(ID, T);
        printf("\nEndereco: %s \n", T[ID].Endereco);
        printf("Deseja ver a informacao de mais algum cliente? [S/N]\n");
        while (escolha != 'S' && escolha != 'N')
        {
            scanf("%c", &escolha);
        }
        if (escolha == 'N')
        {
            system("cls");
            break;
        }
    }
}

void menu()
{
    int opcao;
    struct Pessoas P[30];
    carregar(P);
    while (1)
    {
        printf("Programa loja de construcao!!\n");
        printf("\n1- Cadastrar Cliente");
        printf("\n2- Editar cadastro!");
        printf("\n3- Excluir dados de um cadastro!");
        printf("\n4- Lista Clientes");
        printf("\n5- Pesquisar Cliente Por ID");
        printf("\n9- Sair ");
        printf("\n Digite opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
            cadastro(P);
        if (opcao == 2)
            editar(P);
        if (opcao == 3)
            excluir(P);
        if (opcao == 4)
            mostra(P);
        if (opcao == 5)
            mostra1(P);
        if (opcao == 9){
            salvar(P);// SALVA TODAS AS MODIFICAÇOES.
            return;
        }
    }
}

int main()
{
    menu();
}
