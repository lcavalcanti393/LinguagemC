#import <cstdio>
#import <locale.h>
#import <windows.h>
#import <conio.h>

/*
	* O sistema de vendas não tem um ramo específico,
	pode vender tudo o que for cadastrado. Portanto
	para uma rápida avaliação cadastre coisas simples
	do dia a dia, como: arroz, feijão, macarrão, café,
	leite, etc.
	
	* No cadastro de produtos utilize vírgula para
	atribuir o preço, caso contrário irá apresentar
	valor inteiro, sem a parte flutuante.
*/


void tabelaProdutos();
void mostrarCompra();
void comprarProdutos();
void calcularLucro();

#define S 115	//	valor da tecla 's' 
#define LMT 20 	//	defina aqui a quantidade de produtos

struct ficha_de_venda{
	char nomeProduto[30], nomeCliente[20][20];
	int qtd, qtdnome=0;
	float valorProd;
};

struct ficha_de_venda vendas[LMT];

float lucro[50];
int nc=0;

int main(){
	setlocale(LC_ALL, "Portuguese");  //Função para utilizar acentos e caracteres
	
	////////////////////////  CADASTRAR PRODUTO ////////////////////////////////////
	int a=0;
	int b;
	
	printf("   <<< CADASTRAR PRODUTO >>> \n#####################################\n");
	for(b=0;b<LMT;b++){
	
		printf("PRODUTO:	");
		fflush(stdin); gets(vendas[a].nomeProduto);
		
		printf("PREÇO (R$):	");
		fflush(stdin); scanf("%f", &vendas[a].valorProd);
		
		printf("QUANTIDADE:	");
		fflush(stdin); scanf("%d", &vendas[a].qtd);
		printf("#####################################\n");	
		
		printf("\nCADASTRAR MAIS UM PRODUTO? [S/N]\n");
		if(getch()==115){a++;printf("--------------------------------------\n");}
		else{system("cls");break;}
		
	}
    ////////////////////////////////////////////////////////////////////////////////
		
	tabelaProdutos();
	mostrarCompra();
	calcularLucro();
	
	getch();
	return 0;
}


void tabelaProdutos(){	
	printf("  PRODUTO\t\t PREÇO(R$)\tQUANTIDADE\n");
    printf("---------------------------------------------------\n");
    for(int b=0;b<LMT;b++){
		if(vendas[b].nomeProduto[0] == '\0'){break;}
		
        printf("%i - %-20s ", b+1,vendas[b].nomeProduto);

        printf(" R$%.2f\t ", vendas[b].valorProd);

        printf("  %3d\n", vendas[b].qtd);
    
	}
	
	comprarProdutos();
}

void comprarProdutos(){
	
	int nprod[LMT];	 // Número de produtos cadastrados
	int b;
	
	
	for(b=0;b<LMT;b++){
		printf("\n\nDIGITE O NÚMERO DO PRODUTO QUE DESEJA COMPRAR: ");
		fflush(stdin); scanf("%i", &nprod[b]);
		
		if(vendas[nprod[b]-1].qtd>0){
			vendas[nprod[b]-1].qtd--;
			printf("  -->  Você comprou: %s \n", vendas[nprod[b]-1]);
			printf("  -->  Restam: %i\n", vendas[nprod[b]-1].qtd);
			lucro[nc] = vendas[nprod[b]-1].valorProd;
			nc++;
		}
		else{printf("Produto indisponível!\n"); b--;}
		
		
		printf("Deseja comprar algo mais? [S/N]:");
		fflush(stdin);
		if(getch()!=S){nprod[b+1]=0;break;}
		//else{printf("\n\n################################################");break;}
	}
	
	char nomeCliente[20];
	
	printf("\nNome do cliente: ");
	fflush(stdin); gets(nomeCliente);
	
	for(b=0;b<LMT;b++){
		if(nprod[b] == 0){break;}
		for(int c=0;c<LMT;c++){
			if(nomeCliente[c]=='\0'){
				vendas[nprod[b]-1].nomeCliente[vendas[nprod[b]-1].qtdnome][c] = '\0';
				break;
			}
			vendas[nprod[b]-1].nomeCliente[vendas[nprod[b]-1].qtdnome][c] = nomeCliente[c];
		}
		vendas[nprod[b]-1].qtdnome++;
	}
	
	printf("\nNova compra? [S/N]\n");
	fflush(stdin);if(getch()==S){system("cls");tabelaProdutos();}
	
}

void mostrarCompra(){
	int nprod;
	int resp=S;
	while(resp==S){
		printf("\n\nDigite o número do produto para ver seu(s) comprador(es): ");
		fflush(stdin);	scanf("%i", &nprod);
	
		printf("Compradores de %s: ", vendas[nprod-1].nomeProduto);	
	
		for(int b=0;b<vendas[nprod-1].qtdnome;b++){
			printf("%i-%s, ", b+1, vendas[nprod-1].nomeCliente[b]);
		
		}
	
		printf("\nOutro produto? [S/N] ");
		resp = getch();
	}
}

void calcularLucro(){
	
	int b;
	float total;
	
	printf("\n\nLUCRO:");
	
	for(b=0;b<50;b++){
		if(lucro[b]==0){break;}
		printf(" R$%.2f ", lucro[b]);
	}
	
	for(b=0;b<50;b++){
		if(lucro[b]==0){break;}
		total+=lucro[b];
	}
	
	printf(" = R$%.2f ", total);
	
}
