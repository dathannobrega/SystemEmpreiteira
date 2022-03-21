#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <C:\Users\datha\OneDrive - ufu.br\Documentos\DATHAN\IPC\TRABALHO FINAL\Alpha Trab\teladeloading.c>
#include <C:\Users\datha\OneDrive - ufu.br\Documentos\DATHAN\IPC\TRABALHO FINAL\Alpha Trab\references.c>

void formatacpf(char T[])
{
    int i, j = 1;
    for (i = 0; i < 11; i++, j++)
    {
        printf("%c", T[i]);
        if (i == 8)
            printf("-");
        else if (j == 3)
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
        else if (i == 7)
        {
            printf("-");
        }
        printf("%c", T[i]);
    }
}

// void verificacpf(){
//
// }

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

int buscaCPF(char a[], struct Pessoas T[]) //! PESQUISAR CPF NA STRUCT
{
    int i;
    for (i = 0; i < 30; i++)
    {
        if (strcmp(a, T[i].Cpf) == 0)
            return i; // se existir vai mostrar em qual vetor está localizado.
    }
    return -1; // SE nao AChar vai retornar -1
};

// int Verificar_Dados()
// { // se um dado dor igual a outro cliente cadatrato, ira recusar
// }

void carregar(Pessoas P[], Materiais *M, Preco *pr) //!!!!!!!!!FUNÇAO QUE CARREGA O PROGRAMA !!!!!!!!!
{
    int i = 1;
    for (i = 0; i < 30; i++)
        P[i].ID = 0;
    // =======INICIANDO VARIAVEIS DE PREÇO======
    pr->Tijolo_price = 0.0;
    pr->porcelanato_price = 0.0;
    pr->saco_argamassa_price = 0.0;
    pr->saco_cimento_price = 0.0;
    pr->vergalhoes_price = 0.0;

    // ===CARREGADO DADOS DOS USUARIOS==========
    Forsafe F;
    FILE *file = fopen("database.bin", "rb");
    i = 1;
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
    // === CAREGAR PRECOS SALVOS========
    forPreco fpr;
    FILE *fprecos = fopen("precosDB.bin", "rb");
    fread(&fpr, sizeof(Preco), 1, fprecos);
    pr->porcelanato_price = fpr.porcelanato_price;
    pr->saco_argamassa_price = fpr.saco_argamassa_price;
    pr->saco_cimento_price = fpr.saco_cimento_price;
    pr->Tijolo_price = fpr.Tijolo_price;
    pr->vergalhoes_price = fpr.vergalhoes_price;
    fclose(fprecos);
    // === CARREGAR ESTOQUE=======
    forMateriais fM;
    FILE *fproduct = fopen("productDB.bin", "rb");
    fread(&fM, sizeof(Materiais), 1, fproduct);
    M->porcelanato = fM.porcelanato;
    M->saco_argamassa = fM.saco_argamassa;
    M->saco_cimento = fM.saco_cimento;
    M->Tijolo = fM.Tijolo;
    M->vergalhoes = fM.vergalhoes;
    fclose(fproduct);
    // =========================================
}

void salvar(Pessoas P[], Materiais M, Preco pr) //!!!!!!!!!FUNÇAO QUE Salva Todas As Modificaçoes DO PROGRAMA
{
    int i = 1;
    remove("database.bin");

    FILE *file = fopen("database.bin", "ab");

    while (1)
    {
        if (i == 30)
            break;
        fwrite(&P[i], sizeof(Pessoas), 1, file);
        i++;
    }
    fclose(file);

    FILE *fprecos = fopen("precosDB.bin", "wb");
    fwrite(&pr, sizeof(Preco), 1, fprecos);
    fclose(fprecos);
// =======SAlvando qd estoque =========
    FILE *fproduct = fopen("productDB.bin", "wb");
    fwrite(&M, sizeof(Materiais), 1, fproduct);
    fclose(fproduct);
}

void ajustepreco(Preco pr)
{
    while (1)
    {
        int opcao;
        float newvalue = 0;
        system("cls");
        printf("=========================================\n");
        printf("      COTACAO ATUAL DAS MERCADORIAS      \n");
        printf("=========================================\n");
        printf("|A empresa esta com os Seguinte produtos|\n");
        printf("-----------------------------------------\n");
        printf("|Tijolos: R$%5.2f|\n|Porcelanato: R$%5.2f|\n", pr.Tijolo_price, pr.porcelanato_price);
        printf("|Sacos de cimento: R$%5.2f|\n|Sacos de Argamassa: R$%5.2f|\n", pr.saco_cimento_price, pr.saco_argamassa_price);
        printf("|Vergalhoes: R$%5.2f|\n", pr.vergalhoes_price);
        printf("=========================================\n");
        printf("|      QUAL PRECO DESEJA MODIFICAR?     |\n");
        printf("-----------------------------------------\n");
        printf("|1- Tijolo                              |\n");
        printf("|2- Porcelanato                         |\n");
        printf("|3- Saco de Cimento                     |\n");
        printf("|4- Saco de Argamassa                   |\n");
        printf("|5- Vergalhao                           |\n");
        printf("|9- SAIR                                |\n");
        printf("=========================================\n");
        printf("OPCAO: ");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO VALORES           \n");
            printf("=========================================\n");
            printf("Qual o Novo Valor do Tijolo?");
            scanf("%f", &newvalue);
            pr.Tijolo_price = newvalue;
        }
        if (opcao == 2)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO VALORES           \n");
            printf("=========================================\n");
            printf("Qual o Novo Valor do Porcelanato?");
            scanf("%f", &newvalue);
            pr.porcelanato_price = newvalue;
        }
        if (opcao == 3)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO VALORES           \n");
            printf("=========================================\n");
            printf("Qual o Novo Valor do Saco de Cimento??");
            scanf("%f", &newvalue);
            pr.saco_cimento_price = newvalue;
        }
        if (opcao == 4)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO VALORES           \n");
            printf("=========================================\n");
            printf("Qual o Novo Valor do Saco de Argamassa?");
            scanf("%f", &newvalue);
            pr.saco_argamassa_price = newvalue;
        }
        if (opcao == 5)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO VALORES           \n");
            printf("=========================================\n");
            printf("Qual o Novo Valor do Vergalhao?");
            scanf("%f", &newvalue);
            pr.vergalhoes_price = newvalue;
        }
        if (opcao == 9)
        {
            break;
        }
    }
}

void modificaestoque(Materiais *M)
{
    while (1)
    {
        int opcao;
        float newvalue = 0;
        system("cls");
        printf("=========================================\n");
        printf("      ESTOQUE ATUAL DAS MERCADORIAS      \n");
        printf("=========================================\n");
        printf("|A empresa esta com os Seguinte produtos|\n");
        printf("-----------------------------------------\n");
        printf("|Tijolos: %d un|\n|Porcelanato: %d m2|\n", M->Tijolo, M->porcelanato);
        printf("|Sacos de cimento: %d un|\n|Sacos de Argamassa: %d un|\n", M->saco_cimento, M->saco_argamassa);
        printf("|Vergalhoes: %d un|\n", M->vergalhoes);
        printf("=========================================\n");
        printf("| QUAL PRODUTO DESEJA ALTERAR O ESTOQUE |\n");
        printf("-----------------------------------------\n");
        printf("|1- Tijolo                              |\n");
        printf("|2- Porcelanato                         |\n");
        printf("|3- Saco de Cimento                     |\n");
        printf("|4- Saco de Argamassa                   |\n");
        printf("|5- Vergalhao                           |\n");
        printf("|9- SAIR                                |\n");
        printf("=========================================\n");
        printf("OPCAO: ");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO ESTOQUE           \n");
            printf("=========================================\n");
            printf("quantas Unidades de Tijolos a empresa possui?");
            scanf("%f", &newvalue);
            M->Tijolo = newvalue;
        }
        if (opcao == 2)
        {
            system("cls");
            printf("=========================================\n");
             printf("           MODIFICANDO ESTOQUE           \n");
            printf("=========================================\n");
            printf("Quantos m2 de Porcelanato a empresa possui?");
            scanf("%f", &newvalue);
            M->porcelanato = newvalue;
        }
        if (opcao == 3)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO ESTOQUE           \n");
            printf("=========================================\n");
            printf("Quantos Sacos de Cimento a empresa Possui?");
            scanf("%f", &newvalue);
            M->saco_cimento = newvalue;
        }
        if (opcao == 4)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO ESTOQUE           \n");
            printf("=========================================\n");
            printf("Quantos Sacos de Argamassa a empresa Possui?");
            scanf("%f", &newvalue);
            M->saco_argamassa = newvalue;
        }
        if (opcao == 5)
        {
            system("cls");
            printf("=========================================\n");
            printf("           MODIFICANDO ESTOQUE           \n");
            printf("=========================================\n");
            printf("Quanto Vergalhoes a empresa possui?");
            scanf("%f", &newvalue);
            M->vergalhoes = newvalue;
        }
        if (opcao == 9)
        {
            break;
        }
    }
}

void consultarestoque(Materiais *M, Preco pr, int tipo_consulta)
{
    while (1)
    {

        int opcao;
        system("cls");
        printf("=========================================\n");
        printf("           CONTROLE DE ESTOQUE           \n");
        printf("=========================================\n");
        printf("|A empresa esta com os Seguinte produtos|\n");
        printf("-----------------------------------------\n");
        printf("|Tijolos: %30d|\n|Porcelanato: %26d|\n", M->Tijolo, M->porcelanato);
        printf("|Sacos de cimento: %21d|\n|Sacos de Argamassa: %19d|\n", M->saco_cimento, M->saco_argamassa);
        printf("|Vergalhoes: %27d|\n", M->vergalhoes);
        printf("=========================================\n");

        if (tipo_consulta == 1)
        {
            system("pause");
            break;
        }
        if (tipo_consulta == 0)
        {
            printf("=========================================\n");
            printf("|            OPCOES DE ESTOQUE          |\n");
            printf("=========================================\n");
            printf("|           1-AJUSTE DE PRECO           |\n");
            printf("|           2-ADICIOANR ESTOQUE         |\n");
            printf("|           9-VOLTAR                    |\n");
            printf("=========================================\n\n");
            printf("OPCAO: ");
            scanf("%d", &opcao);
            if (opcao == 1)
            {
                ajustepreco(pr);
            }
            else if (opcao == 2)
            {
                modificaestoque(M);
            }
            else if (opcao == 9)
            {
                system("cls");
                break;
            }
            else
            {
                printf("OPCAO INVALIDA!!\n");
                system("pause");
            }
        }
    }
}

// void gerar_orcamento_txt()
// {
// }

void add(struct Materiais M, struct Pessoas T[], struct Preco pr)
{
    //=======DECLARANDO FUNÇOES=======================
    void cadastro(Pessoas T[]);
    // ======Declarando as funçoes que serao usadas===

    system("cls");
    float valor = 0, product[5] = {0, 0, 0, 0, 0};
    int material, buscpf;
    int qntd;
    char busccpf[14], escolha;
    while (1)
    {
        escolha = 'V';
        printf("==================================\n");
        printf("     CRIACAO DE NOVO ORCAMENTO    \n");
        printf("==================================\n");
        printf("Qual o CPF do Cliente?: ");
        scanf("%s", busccpf);
        buscpf = 0;
        buscpf = (buscaCPF(busccpf, T));
        if (buscpf == (-1))
        {
            system("cls");
            printf("Cliente nao Cadastrado!\n");
            printf("Deseja Cadastrar esse Cliente? [S/N]\n");
            while (escolha != 'S' && escolha != 'N')
            {
                scanf("%c", &escolha);
            }
            if (escolha == 'S')
            {
                system("cls");
                cadastro(T);
            }
            if (escolha == 'N')
            {
                system("cls");
            }
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        system("cls");
        printf("==================================\n");
        printf("Orcamento para %s\n", T[buscpf].Nome);
        printf("==================================\n");
        escolha = 'V'; // Reseta a escolha para segunda parte.
        printf("Quais Materiais Necessita?\n");
        printf("\n1- Tijolos");
        printf("\n2- Porcelanato");
        printf("\n3- saco_cimento");
        printf("\n4- saco_argamassa");
        printf("\n5- vergalhoes");
        printf("\n6- Consultar Estoque");
        printf("\n9- Cancelar ");
        printf("\n Digite opcao: ");
        scanf("%d", &material);

        if (material == 1)
        {
            while (1)
            {
                system("cls");
                printf("Quantos tijolos o Cliente precisa?\n");
                printf("0- VOLTAR\n");
                setbuf(stdin, NULL);
                scanf("%d", &qntd);
                if (qntd > M.Tijolo)
                {
                    escolha = 'V'; // Reseta a escolha para segunda parte.
                    printf("Nao ha estoque para esse pedido!\n");
                    printf("Deseja Verificar seu Estoque? [S/N]\n");
                    setbuf(stdin, NULL);
                    scanf("%c", &escolha);
                    if (escolha == 'S')
                    {
                        consultarestoque(&M, pr, 1);
                        continue;
                    }
                    continue;
                    if (escolha == 'N')
                        continue;
                }
                else
                {
                    valor += pr.Tijolo_price * qntd;
                    product[0] += qntd;
                    M.Tijolo -= qntd;
                    break;
                }
            }
        }
        if (material == 2)
        {
            while (1)
            {
                escolha = 'V'; // Reseta a escolha para segunda parte.
                system("cls");
                printf("Quantos m2 de porcelanato o Cliente precisa?\n");
                printf("0- VOLTAR\n");
                scanf("%d", &qntd);
                if (qntd > M.porcelanato)
                {
                    printf("Nao ha estoque para esse pedido!\n");
                    printf("Deseja Verificar seu Estoque? [S/N]\n");
                    setbuf(stdin, NULL);
                    scanf("%c", &escolha);
                    if (escolha == 'S')
                        consultarestoque(&M, pr, 1);
                    if (escolha == 'N')
                        continue;
                }
                else
                    valor += pr.porcelanato_price * qntd;
                product[1] += qntd;
                M.Tijolo -= qntd;
            }
        }
        if (material == 3)
        {
            while (1)
            {
                escolha = 'V'; // Reseta a escolha para segunda parte.
                system("cls");
                printf("Quantos Sacos de Cimento serao necessario ?\n");
                printf("0- VOLTAR\n");
                scanf("%d", &qntd);
                if (qntd > M.saco_cimento)
                {
                    printf("Nao ha estoque para esse pedido!\n");
                    printf("Deseja Verificar seu Estoque? [S/N]\n");
                    scanf("%c", &escolha);
                    if (escolha == 'S')
                        consultarestoque(&M, pr, 1);

                    if (escolha == 'N')
                        continue;
                }
                else
                    valor += pr.saco_cimento_price * qntd;
                product[2] += qntd;
                M.saco_cimento -= qntd;
            }
        }
        if (material == 4)
        {
            while (1)
            {
                escolha = 'V'; // Reseta a escolha para segunda parte.
                system("cls");
                printf("Quantos saco_argamassa o Cliente precisa?");
                printf("0- VOLTAR\n");
                scanf("%d", &qntd);
                if (qntd > M.Tijolo)
                {
                    printf("Nao ha estoque para esse pedido!\n");
                    printf("Deseja Verificar seu Estoque? [S/N]\n");
                    scanf("%c", &escolha);
                    if (escolha == 'S')
                        consultarestoque(&M, pr, 1);
                    if (escolha == 'N')
                        continue;
                }
                else
                    valor += pr.saco_argamassa_price * qntd;
                product[3] += qntd;
                M.saco_argamassa -= qntd;
            }
        }
        if (material == 5)
        {
            while (1)
            {
                escolha = 'V'; // Reseta a escolha para segunda parte.
                system("cls");
                printf("Quantos vergalhoes o Cliente precisa?");
                printf("0- VOLTAR\n");
                scanf("%d", &qntd);
                if (qntd > M.vergalhoes)
                {
                    printf("Nao ha estoque para esse pedido!\n");
                    printf("Deseja Verificar seu Estoque? [S/N]\n");
                    scanf("%c", &escolha);
                    if (escolha == 'S')
                        consultarestoque(&M, pr, 1);
                    if (escolha == 'N')
                        continue;
                }
                else
                    valor += pr.vergalhoes_price * qntd;
                product[4] = qntd;
                M.vergalhoes -= qntd;
            }
        }
        if (material == 6)
        {
            consultarestoque(&M, pr, 1);
        }
        if (material == 9)
        {
            // Se cancelar o orcamento, tudo reseta e os valores voltam ao normal
            M.Tijolo += product[0];
            M.porcelanato += product[1];
            M.saco_cimento += product[2];
            M.saco_argamassa += product[3];
            M.vergalhoes += product[4];
            system("cls");
            break;
        }
    }
}

void cadastro(Pessoas T[])
{
    int ID;
    system("cls");
    printf("Digite o ID do Novo Cliente: ");
    scanf("%d", &ID);

    // PARTE Q  salvadados usuarios
    FILE *file = fopen("database.bin", "ab");
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
    system("cls");
    int ID;
    for (ID = 1; ID < 30; ID++)
    {
        if (T[ID].ID == 0)
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
        system("cls");
        int ID;
        char escolha = 'h';
        printf("Digite o ID do cliente que deseja ver as informacoes: ");
        scanf("%d", &ID);
        printf("-------------------------------------\n");
        printf("|Nome: %s \n|CPF: ", T[ID].Nome);
        formatacpf(T[ID].Cpf);
        printf("\n|Telefone: ");
        formatacell(T[ID].Telefone);
        printf("\n|Endereco: %s \n", T[ID].Endereco);
        printf("-------------------------------------\n");
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
    struct Materiais M;
    struct Preco pr;
    carregar(P, &M, &pr);
    abertura();
    system("cls");

    while (1)
    {
        printf("======================================================================\n");
        printf("Programa loja de construcao!!\n");
        printf("======================================================================\n");
        printf("\n1- Cadastrar Cliente");
        printf("\n2- Editar cadastro!");
        printf("\n3- Excluir dados de um cadastro!");
        printf("\n4- Lista Clientes");
        printf("\n5- Pesquisar Cliente Por ID");
        printf("\n6- Novo Orcamento");
        printf("\n7- Estoque");
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
        if (opcao == 6)
            add(M, P, pr);
        if (opcao == 7)
            consultarestoque(&M, pr, 0);
        if (opcao == 9)
        {
            salvar(P, M, pr); // SALVA TODAS AS MODIFICAÇOES.
            return;
        }
    }
}

int main()
{
    // IMPRIMIT !! system("notepad /p database.bin");
    menu();
}
