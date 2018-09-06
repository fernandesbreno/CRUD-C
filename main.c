#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<locale.h>

#define MAX 16
#define MAX_PES 32
#define MAX_OBJ 64
//Menus
typedef struct {
 unsigned char cabecalho[256];
 unsigned char menuPrincipal[256];
 unsigned char menuCurso[256];
 unsigned char menuTurma[256];
 unsigned char menuAluno[256];
}MENUS;

MENUS carregaMenu(){
	MENUS m;
	FILE* arquivo;
	arquivo = fopen("db\\PTBR.lang","rb");
	fread(&m,sizeof(MENUS), 1,arquivo);
	fclose(arquivo);
	return m;
}

void saveMenu(void){
	FILE* arquivo;
	MENUS m;
	strcpy(m.cabecalho, "-------------------------------------------\n SISTEMA DE ALGUMA COISA DE FACULDADE \n-------------------------------------------\n" );
  	strcpy(m.menuPrincipal, "1 - CURSOS\n2 - TURMAS\n3 - ALUNOS\n4 - Sair\n");
  	strcpy(m.menuCurso, "1 - Listar Cursos\n2 - Inserir Cursos\n3 - Editar Cursos\n4 - Remover Cursos\n5 - Voltar\n");
  	strcpy(m.menuTurma, "1 - Listar Turmas\n2 - Inserir Turmas\n3 - Editar Turmas\n4 - Remover Turmas\n5 - Voltar\n");
  	strcpy(m.menuAluno, "1 - Listar Alunos\n2 - Inserir Alunos\n3 - Editar Alunos\n4 - Remover Alunos\n5 - Voltar\n");
	arquivo = fopen("db\\PTBR.lang","wb");
	fwrite(&m,sizeof(MENUS), 1 ,arquivo);
	fclose(arquivo);
}

MENUS m;


//Estruturas dos dados de alunos
typedef struct {
	unsigned char dia;
	unsigned char mes;
	unsigned short int ano;
}DATA;

//Estruturas da faculdade
typedef struct {
	unsigned char nome[MAX_OBJ];
	unsigned int cargaHoraria;
	unsigned char professor[MAX_PES];
}DISCIPLINA;

typedef struct {
	unsigned char nome[MAX_PES];
	unsigned char cpf[MAX_OBJ];
	DATA dataNasc;
}ALUNO;

typedef struct {
	unsigned char nome[MAX_OBJ];
	DISCIPLINA d[MAX];
	ALUNO a[MAX];
	unsigned char qtd_alunos;
}TURMA;

typedef struct {
	unsigned char nome[MAX_OBJ];
	unsigned char coordenador[MAX_PES];
	TURMA t[MAX];
	unsigned char qtd_turmas;
}CURSO;

typedef struct{
	CURSO c[10];
	unsigned int qtd_cursos;
}DADOS;



//dado de todos os cursos
DADOS cursos;

unsigned char main(void){

	//PT-BR
	setlocale(LC_ALL, "Portuguese");
	//redefineDados();
	carregaBd();
	//saveMenu();
	m = carregaMenu();
	//Acoes principais do programa
	menuPrincipal();
	return 0;
}
void saveDados(void){
	FILE* arquivo;
	arquivo = fopen("db\\database.conf","wb");
	fwrite(&cursos,sizeof(DADOS), 1 ,arquivo);
	fclose(arquivo);
}

//E utilizado para restaurar o bd em um estado com alguns dados
void redefineDados(void){
	//Carrega o bd em memoria
	FILE* arquivo;
	arquivo = fopen("db\\database.conf","wb");
	//Adicionando cursos
	strcpy(cursos.c[0].nome, "ADMINISTRACA");
	++cursos.qtd_cursos;
	strcpy(cursos.c[1].nome, "CIENCIA DA COMPUTACAO");
	++cursos.qtd_cursos;
	strcpy(cursos.c[2].nome, "DIREITO");
	++cursos.qtd_cursos;
	strcpy(cursos.c[3].nome, "ENGENHARIA AGRONOMICA");
	++cursos.qtd_cursos;
	strcpy(cursos.c[4].nome, "MEDICINA");
	++cursos.qtd_cursos;
	//Adicionando turmas dos cursos
	strcpy(cursos.c[0].t[0].nome, "1 Periodo");
	++cursos.c[0].qtd_turmas;
	strcpy(cursos.c[0].t[1].nome, "2 Periodo");
	++cursos.c[0].qtd_turmas;
	strcpy(cursos.c[1].t[0].nome, "1 Periodo");
	++cursos.c[1].qtd_turmas;
	strcpy(cursos.c[1].t[1].nome, "2 Periodo");
	++cursos.c[1].qtd_turmas;
	strcpy(cursos.c[2].t[0].nome, "1 Periodo");
	++cursos.c[2].qtd_turmas;
	strcpy(cursos.c[2].t[1].nome, "2 Periodo");
	++cursos.c[2].qtd_turmas;
	//add Alunos
	strcpy(cursos.c[0].t[0].a[0].nome, "8bits");
	++cursos.c[0].t[0].qtd_alunos;
	strcpy(cursos.c[0].t[0].a[1].nome, "16bits");
	++cursos.c[0].t[0].qtd_alunos;
	strcpy(cursos.c[0].t[0].a[2].nome, "32bits");
	++cursos.c[0].t[0].qtd_alunos;
	strcpy(cursos.c[0].t[0].a[3].nome, "64bits");
	++cursos.c[0].t[0].qtd_alunos;

	fwrite(&cursos,sizeof(DADOS), 1 ,arquivo);
	fclose(arquivo);

}

void carregaBd(void){
	//Carrega o bd em memoria
	FILE* arquivo;
	arquivo = fopen("db\\database.conf","rb");
	fread(&cursos,sizeof(DADOS), 1,arquivo);
	fclose(arquivo);
}

void imprimeMenu(char menu[]){
	printf("%s%s",m.cabecalho,menu);
}

unsigned char opcao(void){
	unsigned char op = 0;
	printf("Escolha uma opcao: ");
	scanf(" %hhu",&op);
	system("cls");
	return op;
}

void menuPrincipal(void){
	while(true){
		imprimeMenu(m.menuPrincipal);
		switch(opcao()){
			case 1:
				menuCurso();
				break;
			case 2:
				menuTurma();
				break;
			case 3:
				menuAluno();
				break;
			case 4:
				exit(0);
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				printf("Opcao Invalida!\n");
			}
	}


}

void menuCurso(void){
	imprimeMenu(m.menuCurso);
	switch(opcao()){
		case 1:
			listaCurso();
			break;
		case 2:
			insereCurso();
			break;
		case 3:
			editaCurso();
			break;
		case 4:
			removeCurso();
			break;
		case 5:
			menuPrincipal();
			break;
		default:
			printf("Opcao Invalida!\n");
	}
	printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR");
	getch();
	fflush(stdin);
	system("cls");
	menuCurso();
}


void menuTurma(void){
	imprimeMenu(m.menuTurma);
	switch(opcao()){
		case 1:
			listaTurma();
			break;
		case 2:
			insereTurma();
			break;
		case 3:
			editaTurma();
			break;
		case 4:
			removeTurma();
			break;
		case 5:
			break;
		default:
			printf("Opcao Invalida!\n");
	}
	printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR");
	getch();
	fflush(stdin);
	system("cls");
}

void menuAluno(void) {
	imprimeMenu(m.menuAluno);
	switch(opcao()){
		case 1:
			listaAluno();
			break;
		case 2:
			insereAluno();
			break;
		case 3:
			editaAluno();
			break;
		case 4:
			removeAluno();
			break;
		case 5:
			break;
		default:
			printf("Opcao Invalida!\n");
	}
	printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR");
	getch();
	fflush(stdin);
	system("cls");


}

void listaCurso(void){
	imprimeMenu("LISTA DE CURSOS CADASTRADOS:\n");
	for(register unsigned char i = 0; i < cursos.qtd_cursos; ++i){
		printf("%hhu - %s\n\n",i+1,cursos.c[i].nome);
	}
}

void insereCurso(void){
	imprimeMenu("");
	printf("Digite o nome do Curso: ");
	scanf(" %64[^'\n']", cursos.c[cursos.qtd_cursos].nome);
	++cursos.qtd_cursos;
	saveDados();
	printf("O curso %s foi adicionado com sucesso\n", cursos.c[cursos.qtd_cursos-1].nome);
}
void editaCurso(void){
	listaCurso();
	printf("Digite o numero do curso para editar: ");
	unsigned char n = 0;
	scanf(" %hhu", &n);
	printf("Digite o novo nome para o curso de \"%s\"  : ", cursos.c[n-1].nome);
	scanf(" %64[^'\n']", cursos.c[n-1].nome);
	saveDados();
}
void removeCurso(void){
	listaCurso();
	printf("Digite o numero do curso para editar: ");
	unsigned char n = 0;
	scanf(" %hhu", &n);
	for(register unsigned char i = n-1; i < cursos.qtd_cursos-1; i++){
		cursos.c[i] = cursos.c[i+1];
	}
	strcpy(cursos.c[cursos.qtd_cursos-1].nome, "");
	--cursos.qtd_cursos;
	saveDados();


}

unsigned char listaTurma(void){
	listaCurso();
	printf("Digite o numero do curso da turma: ");
	unsigned char n;
	scanf(" %hhu", &n);
	for(register unsigned char i = 0; i < cursos.c[n-1].qtd_turmas; ++i){
		printf("%hhu - %s\n\n",i+1,cursos.c[n-1].t[i].nome);
	}
	return n;
}

void insereTurma(void){
	unsigned char n;
	n = listaTurma();
	printf("Digite o novo nome da turma do curso de \"%s\"  : ",cursos.c[n-1].nome);
	scanf(" %64[^'\n']",  cursos.c[n-1].t[cursos.c[n-1].qtd_turmas].nome);
	++cursos.c[n-1].qtd_turmas;
	saveDados();
}


void editaTurma(void){
	unsigned char n[2];
	n[0] = listaTurma();
	printf("Digite numero da turma do curso de \"%s\"  : ",cursos.c[n[0]-1].nome);
	scanf(" %hhu",&n[1]);
	printf("Digite o novo nome da turma \"%s\" : ",cursos.c[n[0]-1].t[n[1]-1].nome);
	scanf(" %64[^'\n']",  cursos.c[n[0]-1].t[n[1]-1].nome);
	saveDados();
}

void removeTurma(void){
	unsigned char n[2];
	n[0] = listaTurma();
	printf("Digite numero da turma para excluir  : ");
	scanf(" %hhu",&n[1]);

	for(register unsigned char i = n[1]-1; i < cursos.c[n[0]-1].qtd_turmas-1; i++){
		cursos.c[n[0]-1].t[i] = cursos.c[n[0]-1].t[i+1];
	}
	strcpy(cursos.c[n[0]-1].t[cursos.c[n[0]-1].qtd_turmas-1].nome, "");
	--cursos.c[n[0]-1].qtd_turmas;
	fflush(stdin);
	saveDados();

}

char* listaAluno(void){
	unsigned char n[2];
	n[0] = listaTurma();
	printf("Entrou! Digite o numero da turma do aluno: ");
	scanf(" %hhu", &n[1]);
	for(register unsigned char i = 0; i < cursos.c[n[0]-1].t[n[1]-1].qtd_alunos; ++i){
		printf("%hhu - %s\n\n",i+1,cursos.c[n[0]-1].t[n[1]-1].a[i].nome);
	}
	return n;

}

void insereAluno(void){
	unsigned char *n;
	n = listaAluno();
	unsigned char n1 = n[0]-1;
	unsigned char n2 = n[1]-1;
	printf("Digite o novo nome do aluno da turma de \"%s\"  : ", cursos.c[n[0]-1].t[n[1]-1].nome);
	scanf(" %64[^'\n']",  cursos.c[n1].t[n2].a[cursos.c[n1].t[n2].qtd_alunos].nome);
	++cursos.c[n1].t[n2].qtd_alunos;
	saveDados();

}

void editaAluno(void){
	unsigned char *n;
	n = listaAluno();
	unsigned char n1 = n[0]-1;
	unsigned char n2 = n[1]-1;
	unsigned char n3 =  0;
	printf("Digite o numero do aluno para editar: ");
	scanf(" %hhu",&n3);
	printf("Digite o novo nome da aluno \"%s\" : ",cursos.c[n1].t[n2].a[n3-1].nome);
	scanf(" %64[^'\n']", cursos.c[n1].t[n2].a[n3-1].nome);

}

void removeAluno(void){
	unsigned char *n;
	n = listaAluno();
	unsigned char n1 = n[0]-1;
	unsigned char n2 = n[1]-1;
	unsigned char n3 =  0;
	printf("Digite o numero do aluno para excluir: ");
	scanf(" %hhu",&n3);
	for(register unsigned char i = n3-1; i < cursos.c[n1].t[n2].qtd_alunos-1; i++){
		cursos.c[n1].t[n2].a[i] = cursos.c[n1].t[n2].a[i+1];
	}
	strcpy(cursos.c[n1].t[n2].a[cursos.c[n1].t[n2].qtd_alunos-1].nome, "");
	--cursos.c[n1].t[n2].qtd_alunos;

}
