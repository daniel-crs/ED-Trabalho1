#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_NOTAS 10
#define MAX_BUFFER 100

typedef struct {
    char nome[MAX_NOME];
    char telefone[15]; // considerando o formato fixo (DDD) NNNN-NNNN
    char curso[MAX_NOME];
    float notas[MAX_NOTAS];
    int num_notas;
} Aluno;

void calcularSituacao(Aluno aluno, float *media, char *situacao);

int main(void) {
	FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    char buffer[MAX_BUFFER];
    while (fgets(buffer, MAX_BUFFER, entrada) != NULL) {
        Aluno aluno;
        char *token = strtok(buffer, ",");
        strcpy(aluno.nome, token);
        token = strtok(NULL, ",");
        strcpy(aluno.telefone, token);
        token = strtok(NULL, ",");
        strcpy(aluno.curso, token);
        aluno.num_notas = 0;
        token = strtok(NULL, ",");
        while (token != NULL) {
            aluno.notas[aluno.num_notas++] = atof(token);
            token = strtok(NULL, ",");
        }

        float media;
        char situacao[MAX_NOME];
        calcularSituacao(aluno, &media, situacao);
        fprintf(saida, "%s, %.2f, %s\n", aluno.nome, media, situacao);
    }

    fclose(entrada);
    fclose(saida);

    printf("Processamento concluído. Verifique o arquivo SituacaoFinal.csv\n");
	
	
	return 0;
}

void calcularSituacao(Aluno aluno, float *media, char *situacao) {
    float soma = 0;
	int i;
	
    for (i = 0; i < aluno.num_notas; i++) {
        soma += aluno.notas[i];
    }
    *media = soma / aluno.num_notas;
    if (*media >= 7.0)
        strcpy(situacao, "APROVADO");
    else
        strcpy(situacao, "REPROVADO");
}

