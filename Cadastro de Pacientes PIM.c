#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100


char emailpesquisa[];
char usuarioresp[];
int senharesp;
char usuariosantoamaro[]="Santo";
int senhasantoamaro=123;
char usuariomoema[]="Moema";
int senhamoema=123;
char usuariochacara[]="Chacara";
int senhachacara=123;


char sexo[SIZE];
long long int cpf[SIZE];
int idade[SIZE];
int op;


//WK


typedef struct{
    char login[30]; // vetor login da struct pessoa
    char senha[30]; // vetor senha da struct pessoa
} pessoa; pessoa p[1];  // diminuindo o nome da struct para "p" e o "[1]" é o máximo de pessoas com logins e senhas


char nome[SIZE][50];
char email[SIZE][50];

int ddn[SIZE];  //Data de nascimento 
int tel[SIZE]; 
char rua[SIZE][50]; 
int cep[SIZE];
int nm[SIZE];   //Numero da casa/Apto

void menugeral();


void menusantoamaro();
void cadastroclientesantoamaro();
void listaclientesantoamaro();
void pesquisaclientesantoamaro();
void deletarcadastroclientesantoamaro();


void menusantomoema();
void cadastroclientemoema();
void listaclientemoema();
void pesquisaclientemoema();
void deletarcadastroclientemoema();


void menuchacara();
void cadastroclientechacara();
void listaclienteschacara();
void pesquisaclientechacara();
void deletarcadastroclientechacara();

//Programa PRINCIPAL
int main(void){
    login();
}
//Final Programa PRINCIPAL


//Login
int login(){
    system("cls");
    system("color 71");

    char login[30]; // armazenar o login inserida pelo usuário
    char senha[30]; // armazenar a senha inserida pelo usuário
    printf("\n----CLINICA MEDICA----\n\n");
    strcpy(p[0].login, "Clinica"); // Definindo o login "clinica" na struct
    strcpy(p[0].senha, "123"); // Definindo a senha "123"  na struct

    printf("\nlogin:");
    scanf("%s", login); // armazenando os dados inseridos pelo usuário para o vetor login que está dentro da função main

    printf("\nsenha:");
    scanf("%s", senha); // armazenando os dados inseridos pelo usuário para o vetor senha que está dentro da função main

    if ((strcmp(login,p[0].login)==0) && (strcmp(senha,p[0].senha)==0)){ // A função strcmp é responsável por comparar string com string
        printf("\nUsuario logado \n"); // se os vetores de dentro da struct tiver os mesmos dados do vetor interno da função main, usuário será logado.
        menugeral();
    }else{
        printf("Login e/ou senha incorretos\n"); // senão, login ou senha incorreta.
        
    }
      
    return 0;
}
//Fim Login


//################################## Interface para a unidade de Santo Amaro ########################################
void menugeral(){
    system("cls");
    printf("\n----ESCOLHA UMA UNIDADE----\n");
    printf("\n1- Unidade Santo Amaro \n");
    printf("\n2- Unidade Moema \n");
    printf("\n3- Unidade Chacara \n");
    printf("\n\nDigite a unidade desejada: ");
    scanf("%d", &op); 
    if(op==1)
    { 
        menusantoamaro();
    }
    if(op==2)
    { 
        menumoema();
    }
    if(op==3)
    { 
        menuchacara();
    }
    
}


//Função Menu
void menusantoamaro(){
    system("cls");
    printf("\n----UNIDADE SANTO AMARO----\n");
    printf("\n\nDIGITE O NUMERO REFERENTE A OPCAO DESEJADA: \n");
    printf("\nCadastrar Cliente(1) \nPesquisar(2) \nExibir Lista de Clientes(3) \nDeletar Cadastro de Cliente(4)\n\n \nMenu Geral(8) \nSair(9)\nInsira a opção desejada: ");
    scanf("%d", &op); 
    if(op==1)
    { 
        cadastroclientesantoamaro();
    }
    if(op==2)
    {
        pesquisaclientesantoamaro();
    }
    if(op==3)
    {
        listaclientesantoamaro();
    }
    if(op==4)
    {
        deletarcadastroclientesantoamaro();
    }
    
    if(op==9)
    {
        exit(0);
    }
    if (op==8)
    {
        menugeral();
        system("cls");
    }
    
    exit(0);
}
//Fim da Função Menu


//Função Cadastro Cliente
void cadastroclientesantoamaro(){
    system("cls");
    static int linha;
    int contadorantigo;
    int resultado;


    //Recolhe os Dados dos Clientes
    do{
        printf("---- Cadastrando Cliente----\n");
        printf("\nDigite o seu nome: ");
        scanf("%s", &nome[linha]);
        printf("\nDigite o seu e-mail: ");
        scanf("%s", &email[linha]);
        printf("\nDigite a sua idade: ");
        scanf("%d", &idade[linha]);
        printf("\nDigite o seu CPF: ");
        scanf("%lld", &cpf[linha]);
        printf("\nDigite o seu gênero[F ou M]: ");
        scanf("%s", &sexo[linha]);

        //Salva o Cadastro no banco de dados
        FILE* filecliente;
        filecliente = fopen("CadastroClienteSantoAmaro.txt", "a");
        fprintf(filecliente, "%s %s %d %lld %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
        fclose(filecliente);

        //Reseta o valor da variavél caso o looping seja efetuado
        contadorantigo = 0;
        resultado = 0;

        //Lê o Contador no Banco de Dados
        FILE* filecontadorcliente;
        filecontadorcliente = fopen("ContadorClienteSantoAmaro.txt", "r");
        fscanf(filecontadorcliente, "%d", &contadorantigo);
        fclose(filecontadorcliente);

        //Salva o contador no banco de dados
        resultado = contadorantigo + 1;
        filecontadorcliente = fopen("ContadorClienteSantoAmaro.txt", "w");
        fprintf(filecontadorcliente, "%d", resultado);
        fclose(filecontadorcliente);

        //Opções
        printf("\nDigite 1 para continuar cadastrando, 8 para voltar ao menu ou 9 para sair: ");
        scanf("%d", &op);
        linha++;
        if(op==8){
            menusantoamaro();
        }
        if(op==9){
            exit(0);
        }
    }while(op==1);
}
//Fim Função Cadastro Cliente


//Função Deletar Cadastro Cliente
void deletarcadastroclientesantoamaro(){
    long long int deletarcpf;
    int contadorantigo;
    int contadornovo=0;
    int i;
    static int linha;

    //Recebe o CPF que deseja excluir
    printf("\nDigite o CPF do cliente: ");
    scanf("%lld", &deletarcpf);

    //Abre o resgistro de clientes
    FILE* filecliente = fopen("CadastroClienteSantoAmaro.txt", "r");

    //abre e pega o contador de clientes
    FILE* filecontadorlciente = fopen("ContadorClienteSantoAmaro.txt", "r");
    fscanf(filecontadorlciente, "%d", &contadorantigo);
    fclose(filecontadorlciente);

    //Faz um looping ate encontrar no banco de dados o CPF digitado
    for(i = 0; i < contadorantigo; i++)
    {
        fscanf(filecliente, "%s %s %d %lld %s", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);

        //Se o CPF é encontrado mostra os dados do Cliente
        if(deletarcpf == cpf[linha])
        {
            fclose(filecliente);

            //Mostra os dados do Cliente
            printf("\nDados de %s\n", &nome[linha]);
            printf("\nNome: %s \nEmail: %s \nIdade: %d \nCPF: %lld \nGenêro: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);

            //Pergunta se deseja realmente excluir aquele CPF
            printf("\nDeseja deletar o cadastro de %s? Digite 1 para SIM e 2 para NÃO: ", &nome[linha]);
            scanf("%d", &op);

            if(op==1)
            {
                //Cria um novo arquivo txt para colocar os dados dos clientes exceto os dados do CPF que foi excluido
                FILE* filenew = fopen("new.txt", "a");

                //Reabre o registro de clientes para nova utilização
                filecliente = fopen("CadastroClienteSantoAmaro.txt", "r");

                for(i = 0; i < contadorantigo; i++)
                {
                    //Lê os dados do registro de clientes
                    fscanf(filecliente, "%s %s %d %lld %s", &nome[i], &email[i], &idade[i], &cpf[i], &sexo[i]);

                    if(cpf[i] != deletarcpf)
                    {
                        //Guarda os dados dos clientes que restaram no novo banco de dados
                        fprintf(filenew, "%s %s %d %lld %s\n", &nome[i], &email[i], idade[i], cpf[i], &sexo[i]);
                    }
                }
                fclose(filecliente);
                fclose(filenew);

                //Registra o novo valor do contador de clientes no banco de dados
                contadornovo = contadorantigo - 1;
                FILE* filecontadorlciente = fopen("ContadorClienteSantoAmaro.txt", "w");
                fprintf(filecontadorlciente, "%d", contadornovo);
                fclose(filecontadorlciente);

                //Excluí o antigo banco de dados
                remove("CadastroClienteSantoAmaro.txt");


                //Altera o nome do novo banco de dados para o nome antigo
                rename("new.txt", "CadastroClienteSantoAmaro.txt");


                //opções
                printf("\nDigite 8 para retornar ao menu ou 9 para sair: ");
                scanf("%d", &op);
                if(op==8)
                {
                    menusantoamaro();
                }
                if(op==9)
                {
                    exit(0);
                }
                if(op!=8,9)
                {
                    menusantoamaro();
                }
            } 
            if(op!=1)
            {
                menusantoamaro();
            }    
        }
        linha++;
    }
    fclose(filecliente);  
    menusantoamaro();  
}
//Fim Função Deletar Cadastro Cliente


//Função Pesquisa
void pesquisaclientesantoamaro(){
    system("cls");
    long long int cpfpesquisa;
    int contadorpesquisa;
    static int i;
    static int linha;

    //Abre Banco de Dados Cliente
    FILE* filecliente;
    filecliente = fopen("CadastroClienteSantoAmaro.txt", "r");

    //Abre e armazena contador
    FILE* filecontadorcliente;
    filecontadorcliente = fopen("ContadorClienteSantoAmaro.txt", "r");
    fscanf(filecontadorcliente, "%d", &contadorpesquisa);
    fclose(filecontadorcliente);

    //Recebe CPF para Pesquisa
    printf("\nDigite o CPF: ");
    scanf("%lld", &cpfpesquisa);

    //Lê o banco de dados até encontrar o CPF pesquisado
    for(i = 0; i < contadorpesquisa; i++)
    {
        fscanf(filecliente, "%s %s %d %lld %s", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);

        //Se o CPF pesquisado constar no Banco de Dados o resgistro é exibido
        if(cpfpesquisa == cpf[linha])
        {
            printf("\nNome: %s \nE-mail: %s \nIdade: %d \nCPF: %lld \nGênero: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
            printf("\nDigite 1 para continuar pesquisando, 8 para voltar ao menu ou 9 para sair: ");
            scanf("%d", &op);
            //Opções
            if(op==1)
            {
                pesquisaclientesantoamaro();
            }
            
            if(op==8)
            {
                menusantoamaro();
            }
            if(op==9)
            {
                exit(0);
            }
            if(op!=8,9)
            {
                menusantoamaro();
            }
        }
        linha++;
    }
    fclose(filecliente);

    //Opções
    if(op==8)
    {
        menusantoamaro();
    }
    if(op==9)
    {
        exit(0);
    }
    if(op!=8,9)
    {
        menusantoamaro();
    }
    exit(0);
}
//Fim Função Pesquisa


//Lista de Cliente
void listaclientesantoamaro(){
    system("cls");
    static int linha;
    int i;
    int contadorantigo;

    //Abre os Cadastros dos Clientes
    FILE* filecliente;
    filecliente = fopen("CadastroClienteSantoAmaro.txt", "r");

    //Lê o Contador no Banco de Dados
    FILE* filecontadorcliente;
    filecontadorcliente = fopen("ContadorClienteSantoAmaro.txt", "r");
    fscanf(filecontadorcliente, "%d", &contadorantigo);
    fclose(filecontadorcliente);

    //Exibe a lista de Clientes
    printf("\n----Lista de Clientes Cadastrados----\n");
    for(i = 0; i < contadorantigo; i++){
        fscanf(filecliente, "%s %s %d %lld %s \n", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);
        printf("\nNome: %s \nE-mail: %s \nIdade: %d \nCPF: %lld \nGênero: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
        linha++;
    }
    fclose(filecliente);

    //Opções
    printf("\nDigite 8 para voltar ao Menu ou 9 para Sair: ");
    scanf("%d", &op);
    if(op==8){
        menusantoamaro();
    }
    if(op==9){
        exit(0);
    }
    if(op!=8,9)
    {
        menusantoamaro();
    }
    exit(0);
}
//Fim da Lista de Clientes



//################################## Interface para a unidade de Moema ##############################################



//Função Menu
void menumoema(){
    system("cls");
    printf("\n----UNIDADE MOEMA----\n");
    printf("\n\nDIGITE O NUMERO REFERENTE A OPCAO DESEJADA: \n");
    printf("\nCadastrar Cliente(1) \nPesquisar(2) \nExibir Lista de Clientes(3) \nDeletar Cadastro de Cliente(4)\n\n \nMenu Geral(8) \nSair(9)\nInsira a opção desejada: ");
    scanf("%d", &op); 
    if(op==1)
    { 
        cadastroclientemoema();
    }
    if(op==2)
    {
        pesquisaclientemoema();
    }
    if(op==3)
    {
        listaclientemoema();
    }
    if(op==4)
    {
        deletarcadastroclientemoema();
    }
    if(op==9)
    {
        exit(0);
    }
    if (op==8)
    {
        menugeral();
        system("cls");
    }
    exit(0);
}
//Fim da Função Menu


//Função Cadastro Cliente
void cadastroclientemoema(){
    system("cls");
    static int linha;
    int contadorantigo;
    int resultado;


    //Recolhe os Dados dos Clientes
    do{
        printf("---- Cadastrando Cliente----\n");
        printf("\nDigite o seu nome: ");
        scanf("%s", &nome[linha]);
        printf("\nDigite o seu e-mail: ");
        scanf("%s", &email[linha]);
        printf("\nDigite a sua idade: ");
        scanf("%d", &idade[linha]);
        printf("\nDigite o seu CPF: ");
        scanf("%lld", &cpf[linha]);
        printf("\nDigite o seu gênero[F ou M]: ");
        scanf("%s", &sexo[linha]);

        //Salva o Cadastro no banco de dados
        FILE* filecliente;
        filecliente = fopen("CadastroClienteMoema.txt", "a");
        fprintf(filecliente, "%s %s %d %lld %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
        fclose(filecliente);

        //Reseta o valor da variavél caso o looping seja efetuado
        contadorantigo = 0;
        resultado = 0;

        //Lê o Contador no Banco de Dados
        FILE* filecontadorcliente;
        filecontadorcliente = fopen("ContadorClienteMoema.txt", "r");
        fscanf(filecontadorcliente, "%d", &contadorantigo);
        fclose(filecontadorcliente);


        //Salva o contador no banco de dados
        resultado = contadorantigo + 1;
        filecontadorcliente = fopen("ContadorClienteMoema.txt", "w");
        fprintf(filecontadorcliente, "%d", resultado);
        fclose(filecontadorcliente);

        //Opções
        printf("\nDigite 1 para continuar cadastrando, 8 para voltar ao menu ou 9 para sair: ");
        scanf("%d", &op);
        linha++;
        if(op==8){
            menumoema();
        }
        if(op==9){
            exit(0);
        }
    }while(op==1);
}
//Fim Função Cadastro Cliente


//Função Deletar Cadastro Cliente
void deletarcadastroclientemoema(){
    system("cls");
    long long int deletarcpf;
    int contadorantigo;
    int contadornovo=0;
    int i;
    static int linha;

    //Recebe o CPF que deseja excluir
    printf("\nDigite o CPF do cliente: ");
    scanf("%lld", &deletarcpf);

    //Abre o resgistro de clientes
    FILE* filecliente = fopen("CadastroClienteMoema.txt", "r");

    //abre e pega o contador de clientes
    FILE* filecontadorlciente = fopen("ContadorClienteMoema.txt", "r");
    fscanf(filecontadorlciente, "%d", &contadorantigo);
    fclose(filecontadorlciente);

    //Faz um looping ate encontrar no banco de dados o CPF digitado
    for(i = 0; i < contadorantigo; i++)
    {
        fscanf(filecliente, "%s %s %d %lld %s", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);

        //Se o CPF é encontrado mostra os dados do Cliente
        if(deletarcpf == cpf[linha])
        {
            fclose(filecliente);

            //Mostra os dados do Cliente
            printf("\nDados de %s\n", &nome[linha]);
            printf("\nNome: %s \nEmail: %s \nIdade: %d \nCPF: %lld \nGenêro: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);

            //Pergunta se deseja realmente excluir aquele CPF
            printf("\nDeseja deletar o cadastro de %s? Digite 1 para SIM e 2 para NÃO: ", &nome[linha]);
            scanf("%d", &op);

            if(op==1)
            {
                //Cria um novo arquivo txt para colocar os dados dos clientes exceto os dados do CPF que foi excluido
                FILE* filenew = fopen("new.txt", "a");

                //Reabre o registro de clientes para nova utilização
                filecliente = fopen("CadastroClienteMoema.txt", "r");

                for(i = 0; i < contadorantigo; i++)
                {
                    //Lê os dados do registro de clientes
                    fscanf(filecliente, "%s %s %d %lld %s", &nome[i], &email[i], &idade[i], &cpf[i], &sexo[i]);

                    if(cpf[i] != deletarcpf)
                    {
                        //Guarda os dados dos clientes que restaram no novo banco de dados
                        fprintf(filenew, "%s %s %d %lld %s\n", &nome[i], &email[i], idade[i], cpf[i], &sexo[i]);
                    }
                }
                fclose(filecliente);
                fclose(filenew);

                //Registra o novo valor do contador de clientes no banco de dados
                contadornovo = contadorantigo - 1;
                FILE* filecontadorlciente = fopen("ContadorClienteMoema.txt", "w");
                fprintf(filecontadorlciente, "%d", contadornovo);
                fclose(filecontadorlciente);


                //Excluí o antigo banco de dados
                remove("CadastroClienteMoema.txt");


                //Altera o nome do novo banco de dados para o nome antigo
                rename("new.txt", "CadastroClienteMoema.txt");


                //opções
                printf("\nDigite 8 para retornar ao menu ou 9 para sair: ");
                scanf("%d", &op);
                if(op==8)
                {
                    menumoema();
                }
                if(op==9)
                {
                    exit(0);
                }
                if(op!=8,9)
                {
                    menumoema();
                }
            } 
            if(op!=1)
            {
                menumoema();
            }    
        }
        linha++;
    }
    fclose(filecliente);  
    menumoema();  
}
//Fim Função Deletar Cadastro Cliente


//Função Pesquisa
void pesquisaclientemoema(){
    system("cls");
    long long int cpfpesquisa;
    int contadorpesquisa;
    static int i;
    static int linha;

    //Abre Banco de Dados Cliente
    FILE* filecliente;
    filecliente = fopen("CadastroClienteMoema.txt", "r");

    //Abre e armazena contador
    FILE* filecontadorcliente;
    filecontadorcliente = fopen("ContadorClienteMoema.txt", "r");
    fscanf(filecontadorcliente, "%d", &contadorpesquisa);
    fclose(filecontadorcliente);

    //Recebe CPF para Pesquisa
    printf("\nDigite o CPF: ");
    scanf("%lld", &cpfpesquisa);

    //Lê o banco de dados até encontrar o CPF pesquisado
    for(i = 0; i < contadorpesquisa; i++)
    {
        fscanf(filecliente, "%s %s %d %lld %s", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);

        //Se o CPF pesquisado constar no Banco de Dados o resgistro é exibido
        if(cpfpesquisa == cpf[linha])
        {
            printf("\nNome: %s \nE-mail: %s \nIdade: %d \nCPF: %lld \nGênero: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
            printf("\nDigite 1 para continuar pesquisando, 8 para voltar ao menu ou 9 para sair: ");
            scanf("%d", &op);
            //Opções
            if(op==1)
            {
                pesquisaclientemoema();
            } 
            if(op==8)
            {
                menumoema();
            }
            if(op==9)
            {
                exit(0);
            }
            if(op!=8,9)
            {
                menumoema();
            }
        }
        linha++;
    }
    fclose(filecliente);

    //Opções
    if(op==8)
    {
        menumoema();
    }
    if(op==9)
    {
        exit(0);
    }
    if(op!=8,9)
    {
        menumoema();
    }
    exit(0);
}
//Fim Função Pesquisa


//Lista de Cliente
void listaclientemoema(){
    system("cls");
    static int linha;
    int i;
    int contadorantigo;

    //Abre os Cadastros dos Clientes
    FILE* filecliente;
    filecliente = fopen("CadastroClienteMoema.txt", "r");

    //Lê o Contador no Banco de Dados
    FILE* filecontadorcliente;
    filecontadorcliente = fopen("ContadorClienteMoema.txt", "r");
    fscanf(filecontadorcliente, "%d", &contadorantigo);
    fclose(filecontadorcliente);

    //Exibe a lista de Clientes
    printf("\n----Lista de Clientes Cadastrados----\n");
    for(i = 0; i < contadorantigo; i++){
        fscanf(filecliente, "%s %s %d %lld %s \n", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);
        printf("\nNome: %s \nE-mail: %s \nIdade: %d \nCPF: %lld \nGênero: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
        linha++;
    }
    fclose(filecliente);

    //Opções
    printf("\nDigite 8 para voltar ao Menu ou 9 para Sair: ");
    scanf("%d", &op);
    if(op==8){
        menumoema();
    }
    if(op==9){
        exit(0);
    }
    if(op!=8,9)
    {
        menumoema();
    }
    exit(0);
}
//Fim da Lista de Clientes



//################################## Interface para a unidade de Chacara ############################################



//Função Menu
void menuchacara(){
    system("cls");
    printf("\n----UNIDADE CHACARA----\n");
    printf("\n\nDIGITE O NUMERO REFERENTE A OPCAO DESEJADA: \n");
    printf("\nCadastrar Cliente(1) \nPesquisar(2) \nExibir Lista de Clientes(3) \nDeletar Cadastro de Cliente(4)\n\n \nMenu Geral(8) \nSair(9)\nInsira a opção desejada: ");
    scanf("%d", &op); 
    if(op==1)
    { 
        cadastroclientechacara();
    }
    if(op==2)
    {
        pesquisaclientechacara();
    }
    if(op==3)
    {
        listaclientechacara();
    }
    if(op==4)
    {
        deletarcadastroclientechacara();
    }
    
    if(op==9)
    {
        exit(0);
    }
    if (op==8)
    {
        menugeral();
        system("cls");
    }
    exit(0);
}
//Fim da Função Menu


//Função Cadastro Cliente
void cadastroclientechacara(){
    system("cls");
    static int linha;
    int contadorantigo;
    int resultado;


    //Recolhe os Dados dos Clientes
    do{
        printf("---- Cadastrando Cliente----\n");
        printf("\nDigite o seu nome: ");
        scanf("%s", &nome[linha]);
        printf("\nDigite o seu e-mail: ");
        scanf("%s", &email[linha]);
        printf("\nDigite a sua idade: ");
        scanf("%d", &idade[linha]);
        printf("\nDigite o seu CPF: ");
        scanf("%lld", &cpf[linha]);
        printf("\nDigite o seu gênero[F ou M]: ");
        scanf("%s", &sexo[linha]);

        //Salva o Cadastro no banco de dados
        FILE* filecliente;
        filecliente = fopen("CadastroClienteChacara.txt", "a");
        fprintf(filecliente, "%s %s %d %lld %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
        fclose(filecliente);

        contadorantigo = 0;
        resultado = 0;

        //Lê o Contador no Banco de Dados
        FILE* filecontadorcliente;
        filecontadorcliente = fopen("ContadorClienteChacara.txt", "r");
        fscanf(filecontadorcliente, "%d", &contadorantigo);
        fclose(filecontadorcliente);

        //Salva o contador no banco de dados
        resultado = contadorantigo + 1;
        filecontadorcliente = fopen("ContadorClienteChacara.txt", "w");
        fprintf(filecontadorcliente, "%d", resultado);
        fclose(filecontadorcliente);

        //Opções
        printf("\nDigite 1 para continuar cadastrando, 8 para voltar ao menu ou 9 para sair: ");
        scanf("%d", &op);
        linha++;
        if(op==8){
            menuchacara();
        }
        if(op==9){
            exit(0);
        }
    }while(op==1);
}
//Fim Função Cadastro Cliente


//Função Deletar Cadastro Cliente
void deletarcadastroclientechacara(){
    system("cls");
    long long int deletarcpf;
    int contadorantigo;
    int contadornovo=0;
    int i;
    static int linha;

    //Recebe o CPF que deseja excluir
    printf("\nDigite o CPF do cliente: ");
    scanf("%lld", &deletarcpf);

    //Abre o resgistro de clientes
    FILE* filecliente = fopen("CadastroClienteChacara.txt", "r");

    //abre e pega o contador de clientes
    FILE* filecontadorlciente = fopen("ContadorClienteChacara.txt", "r");
    fscanf(filecontadorlciente, "%d", &contadorantigo);
    fclose(filecontadorlciente);

    //Faz um looping ate encontrar no banco de dados o CPF digitado
    for(i = 0; i < contadorantigo; i++)
    {
        fscanf(filecliente, "%s %s %d %lld %s", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);

        //Se o CPF é encontrado mostra os dados do Cliente
        if(deletarcpf == cpf[linha])
        {
            fclose(filecliente);

            //Mostra os dados do Cliente
            printf("\nDados de %s\n", &nome[linha]);
            printf("\nNome: %s \nEmail: %s \nIdade: %d \nCPF: %lld \nGenêro: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);

            //Pergunta se deseja realmente excluir aquele CPF
            printf("\nDeseja deletar o cadastro de %s? Digite 1 para SIM e 2 para NÃO: ", &nome[linha]);
            scanf("%d", &op);

            if(op==1)
            {
                //Cria um novo arquivo txt para colocar os dados dos clientes exceto os dados do CPF que foi excluido
                FILE* filenew = fopen("new.txt", "a");

                //Reabre o registro de clientes para nova utilização
                filecliente = fopen("CadastroClienteChacara.txt", "r");

                for(i = 0; i < contadorantigo; i++)
                {
                    //Lê os dados do registro de clientes
                    fscanf(filecliente, "%s %s %d %lld %s", &nome[i], &email[i], &idade[i], &cpf[i], &sexo[i]);

                    if(cpf[i] != deletarcpf)
                    {
                        //Guarda os dados dos clientes que restaram no novo banco de dados
                        fprintf(filenew, "%s %s %d %lld %s\n", &nome[i], &email[i], idade[i], cpf[i], &sexo[i]);
                    }
                }
                fclose(filecliente);
                fclose(filenew);

                //Registra o novo valor do contador de clientes no banco de dados
                contadornovo = contadorantigo - 1;
                FILE* filecontadorlciente = fopen("ContadorClienteChacara.txt", "w");
                fprintf(filecontadorlciente, "%d", contadornovo);
                fclose(filecontadorlciente);


                //Excluí o antigo banco de dados
                remove("CadastroClienteChacara.txt");


                //Altera o nome do novo banco de dados para o nome antigo
                rename("new.txt", "CadastroClienteChacara.txt");


                //opções
                printf("\nDigite 8 para retornar ao menu ou 9 para sair: ");
                scanf("%d", &op);
                if(op==8)
                {
                    menuchacara();
                }
                if(op==9)
                {
                    exit(0);
                }
                if(op!=8,9)
                {
                    menuchacara();
                }
            } 
            if(op!=1)
            {
                menuchacara();
            }    
        }
        linha++;
    }
    fclose(filecliente);  
    menuchacara();  
}
//Fim Função Deletar Cadastro Cliente


//Função Pesquisa
void pesquisaclientechacara(){
    system("cls");
    long long int cpfpesquisa;
    int contadorpesquisa;
    static int i;
    static int linha;

    //Abre Banco de Dados Cliente
    FILE* filecliente;
    filecliente = fopen("CadastroClienteChacara.txt", "r");

    //Abre e armazena contador
    FILE* filecontadorcliente;
    filecontadorcliente = fopen("ContadorClienteChacara.txt", "r");
    fscanf(filecontadorcliente, "%d", &contadorpesquisa);
    fclose(filecontadorcliente);

    //Recebe CPF para Pesquisa
    printf("\nDigite o CPF: ");
    scanf("%lld", &cpfpesquisa);

    //Lê o banco de dados até encontrar o CPF pesquisado
    for(i = 0; i < contadorpesquisa; i++)
    {
        fscanf(filecliente, "%s %s %d %lld %s", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);

        //Se o CPF pesquisado constar no Banco de Dados o resgistro é exibido
        if(cpfpesquisa == cpf[linha])
        {
            printf("\nNome: %s \nE-mail: %s \nIdade: %d \nCPF: %lld \nGênero: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
            printf("\nDigite 1 para continuar pesquisando, 8 para voltar ao menu ou 9 para sair: ");
            scanf("%d", &op);
            //Opções
            if(op==1)
            {
                pesquisaclientechacara();
            }
            
            if(op==8)
            {
                menuchacara();
            }
            if(op==9)
            {
                exit(0);
            }
            if(op!=8,9)
            {
                menuchacara();
            }
        }
        linha++;
    }
    fclose(filecliente);

    //Opções
    if(op==8)
    {
        menuchacara();
    }
    if(op==9)
    {
        exit(0);
    }
    if(op!=8,9)
    {
        menuchacara();
    }
    exit(0);
}
//Fim Função Pesquisa


//Lista de Cliente
void listaclientechacara(){
    system("cls");
    static int linha;
    int i;
    int contadorantigo;

    //Abre os Cadastros dos Clientes
    FILE* filecliente;
    filecliente = fopen("CadastroClienteChacara.txt", "r");

    //Lê o Contador no Banco de Dados
    FILE* filecontadorcliente;
    filecontadorcliente = fopen("ContadorClienteChacara.txt", "r");
    fscanf(filecontadorcliente, "%d", &contadorantigo);
    fclose(filecontadorcliente);

    //Exibe a lista de Clientes
    printf("\n----Lista de Clientes Cadastrados----\n");
    for(i = 0; i < contadorantigo; i++){
        fscanf(filecliente, "%s %s %d %lld %s \n", &nome[linha], &email[linha], &idade[linha], &cpf[linha], &sexo[linha]);
        printf("\nNome: %s \nE-mail: %s \nIdade: %d \nCPF: %lld \nGênero: %s\n", &nome[linha], &email[linha], idade[linha], cpf[linha], &sexo[linha]);
        linha++;
    }
    fclose(filecliente);

    //Opções
    printf("\nDigite 8 para voltar ao Menu ou 9 para Sair: ");
    scanf("%d", &op);
    if(op==8){
        menuchacara();
    }
    if(op==9){
        exit(0);
    }
    if(op!=8,9)
    {
        menuchacara();
    }
    exit(0);
}
//Fim da Lista de Clientes