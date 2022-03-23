typedef struct forPreco
{
    float Tijolo_price;
    float porcelanato_price;
    float saco_cimento_price;
    float saco_argamassa_price;
    float vergalhoes_price;
} forPreco;

typedef struct Preco
{
    float Tijolo_price;
    float porcelanato_price;
    float saco_cimento_price;
    float saco_argamassa_price;
    float vergalhoes_price;
} Preco;

typedef struct forMateriais
{
    int Tijolo;
    int porcelanato;
    int saco_cimento;
    int saco_argamassa;
    int vergalhoes;
} forMateriais;

typedef struct Materiais
{
    int Tijolo;
    int porcelanato;
    int saco_cimento;
    int saco_argamassa;
    int vergalhoes;
} Materiais;

typedef struct Pessoas
{
    int ID;
    char Nome[40];
    char Cpf[14];
    char Telefone[15];
    char Endereco[100];
} Pessoas;

typedef struct Forsafe // Criado outras Sctruct identica pois Nao estava Conseguindo carregar a struct com mesmo nome
{
    int ID;
    char Nome[40];
    char Cpf[14];
    char Telefone[15];
    char Endereco[100];
} Forsafe;
