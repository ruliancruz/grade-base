#include <stdio.h> //Biblioteca de entrada e saída de dados
#include <locale.h> //Biblioteca de configurações de localização
#include <string.h> //Biblioteca de manipulação de strings

//Estrutura que armazena os dados do aluno na memória RAM
struct Students
{
	int registration;
	char name[60];
	float grade[3];
	float averageGrade;
	char situation;
};

//Estrutura de cadastro de alunos
void Create()
{
	int registration = 0;
	int sucessfulRegistration = 0;
	struct Students student;
	FILE *database;
	
	do
	{
		sucessfulRegistration = 1;
		printf("\nInforme o número da matrícula (digite 0 para cancelar): ");
		scanf("%d", &registration);
		
		if(registration == 0)
		{
			printf("\n");
			return;
		}
		
		database = fopen("Alunos", "rb");
		fread(&student, sizeof(student), 1, database);
		
		while(!feof(database))
		{
			if(registration == student.registration)
			{
				printf("\nErro! Essa matrícula já está cadastrada, tente outra.\n");
				sucessfulRegistration = 0;
			}
			
			fread(&student, sizeof(student), 1, database);
		}
		
		fclose(database);
	} while(sucessfulRegistration != 1);
	
	student.registration = registration;
	printf("Informe o nome do aluno: ");
	fflush(stdin);
	gets(student.name);
	
	do
	{
		printf("Informe a primeira nota do aluno: ");
		scanf("%f", &student.grade[0]);
		
		if(student.grade[0] < 0 || student.grade[0] > 10)
			printf("Erro! A nota precisa estar entre 1 e 10. Tente outro valor.\n");
			
	} while(student.grade[0] < 0 || student.grade[0] > 10);
	
	do
	{
		printf("Informe a segunda nota do aluno: ");
		scanf("%f", &student.grade[1]);
		
		if(student.grade[1] < 0 || student.grade[1] > 10)
			printf("Erro! A nota precisa estar entre 1 e 10. Tente outro valor.\n");
			
	} while(student.grade[1] < 0 || student.grade[1] > 10);
	
	do
	{
		printf("Informe a terceira nota do aluno: ");
		scanf("%f", &student.grade[2]);
		
		if(student.grade[2] < 0 || student.grade[2] > 10)
			printf("Erro! A nota precisa estar entre 1 e 10. Tente outro valor.\n");
			
	} while(student.grade[2] < 0 || student.grade[2] > 10);

	student.averageGrade = (student.grade[0] + student.grade[1] + student.grade[2]) / 3;
	
	if(student.averageGrade >= 7)
		student.situation = 'A';
	else
		student.situation = 'R';
	
	database = fopen("Alunos", "ab");
	fwrite(&student, sizeof(student), 1, database);
	fclose(database);
	printf("\n");
}

//Estrutura de consulta de alunos e média
void ReadAll()
{
	struct Students student;
	FILE *database;
	
	database = fopen("Alunos", "rb");
	fread(&student, sizeof(student), 1, database);
	
	printf("\nLista de Alunos e Médias");
	
	if(feof(database))
	{
		printf("\nNão há nenhum aluno cadastrado no sistema.\n\n");
		fclose(database);
		return;
	}
	
	while(!feof(database))
	{
		printf("\n\nMatrícula: %d", student.registration);
		printf("\nNome: %s", student.name);
		printf("\nNota 1: %.2f", student.grade[0]);
		printf("\nNota 2: %.2f", student.grade[1]);
		printf("\nNota 3: %.2f", student.grade[2]);
		printf("\nMédia: %.2f", student.averageGrade);
		fread(&student, sizeof(student), 1, database);
	}
	
	fclose(database);
	printf("\n\n");
}

//Estrutura de consulta de alunos aprovados
void ReadApproved()
{
	int approvedCounter = 0;
	struct Students student;
	FILE *database;
	
	database = fopen("Alunos", "rb");
	fread(&student, sizeof(student), 1, database);
	
	if(feof(database))
	{
		printf("\nNão há nenhum aluno cadastrado no sistema.\n\n");
		fclose(database);
		return;
	}
	
	printf("\nLista de Alunos Aprovados");
	
	while(!feof(database))
	{
		if(student.situation == 'A')
		{
			printf("\n\nMatrícula: %d", student.registration);
			printf("\nNome: %s", student.name);
			printf("\nMédia: %.2f", student.averageGrade);
			approvedCounter++;
		}
		
		fread(&student, sizeof(student), 1, database);
	}
	
	if(approvedCounter == 0)
		printf("\nNão há nenhum aluno aprovado cadastrado no sistema.");
	
	fclose(database);
	printf("\n\n");
}

//Estrutura de consulta de alunos reprovados
void ReadDisapproved()
{
	int disapprovedCounter = 0;
	struct Students student;
	FILE *database;
	
	database = fopen("Alunos", "rb");
	fread(&student, sizeof(student), 1, database);
	
	if(feof(database))
	{
		printf("\nNão há nenhum aluno cadastrado no sistema.\n\n");
		fclose(database);
		return;
	}
	
	printf("\nLista de Alunos Reprovados");
	
	while(!feof(database))
	{
		if(student.situation == 'R')
		{
			printf("\n\nMatrícula: %d", student.registration);
			printf("\nNome: %s", student.name);
			printf("\nMédia: %.2f", student.averageGrade);
			disapprovedCounter++;
		}
		
		fread(&student, sizeof(student), 1, database);
	}
	
	if(disapprovedCounter == 0)
		printf("\nNão há nenhum aluno reprovado cadastrado no sistema.");
	
	fclose(database);
	printf("\n\n");
}

//Estrutura de alteração de cadastro de alunos
void Update()
{
	while(1)
	{
		int registration;
		int databasePosition = 1;
		int databaseUpdatePosition = 1;
		struct Students student;
		struct Students studentUpdate;
		FILE *database;
		FILE *databaseUpdate;
		
		database = fopen("Alunos", "rb");
		fread(&student, sizeof(student), 1, database);
		
		if(feof(database))
		{
			printf("\nNão há nenhum aluno cadastrado no sistema.\n\n");
			fclose(database);
			return;
		}
		
		printf("\nInforme a matrícula do aluno o qual deseja alterar as notas (digite 0 para cancelar): ");
		scanf("%d", &registration);
		
		if(registration == 0)
		{
			printf("\n");
			fclose(database);
			return;
		}
		
		while(!feof(database))
		{
			if(registration == student.registration)
			{
				printf("\nDados do Aluno:");
				printf("\nMatrícula: %d", student.registration);
				printf("\nNome: %s", student.name);
				printf("\nNota 1: %.2f", student.grade[0]);
				printf("\nNota 2: %.2f", student.grade[1]);
				printf("\nNota 3: %.2f", student.grade[2]);
				printf("\nMédia: %.2f", student.averageGrade);
				printf("\nInforme os novos valores para as notas:\n");
			
				do
				{
					printf("Nota 1: ");
					scanf("%f", &studentUpdate.grade[0]);
		
					if(studentUpdate.grade[0] < 0 || studentUpdate.grade[0] > 10)
						printf("Erro! A nota precisa estar entre 1 e 10. Tente outro valor.\n");
			
				} while(studentUpdate.grade[0] < 0 || studentUpdate.grade[0] > 10);
		
				do
				{
					printf("Nota 2: ");
					scanf("%f", &studentUpdate.grade[1]);
		
					if(studentUpdate.grade[1] < 0 || studentUpdate.grade[1] > 10)
						printf("Erro! A nota precisa estar entre 1 e 10. Tente outro valor.\n");
			
				} while(studentUpdate.grade[1] < 0 || studentUpdate.grade[1] > 10);
	
				do
				{
					printf("Nota 3: ");
					scanf("%f", &studentUpdate.grade[2]);
		
					if(studentUpdate.grade[2] < 0 || studentUpdate.grade[2] > 10)
						printf("Erro! A nota precisa estar entre 1 e 10. Tente outro valor.\n");
			
				} while(studentUpdate.grade[2] < 0 || studentUpdate.grade[2] > 10);
			
				studentUpdate.averageGrade = (studentUpdate.grade[0] + studentUpdate.grade[1] + studentUpdate.grade[2]) / 3;
			
				if(student.averageGrade >= 7)
					studentUpdate.situation = 'A';
				else
					studentUpdate.situation = 'R';
						
				studentUpdate.registration = student.registration;
				strcpy(studentUpdate.name, student.name);
				databaseUpdate = fopen("AlunosUpdate", "ab");
				rewind(database);
				fread(&student, sizeof(student), 1, database);
				
				while(!feof(database))
				{
					if(databaseUpdatePosition == databasePosition)
						fwrite(&studentUpdate, sizeof(studentUpdate), 1, databaseUpdate);
					else
						fwrite(&student, sizeof(student), 1, databaseUpdate);
					
					fread(&student, sizeof(student), 1, database);
					databaseUpdatePosition++;
				}
				
				fclose(database);
				fclose(databaseUpdate);
				remove("Alunos");
				rename("AlunosUpdate", "Alunos");
				printf("\n");
				return;
			}
			else
			{
				fread(&student, sizeof(student), 1, database);
			}
			
			databasePosition++;
		}
		
		fclose(database);
		printf("Erro! Nenhum aluno com encontrado com essa matrícula, tente outra.");
	}
}

//Estrutura de exclusão de cadastro de alunos
void Delete()
{
	while(1)
	{
		int registration;
		int databasePosition = 1;
		int databaseUpdatePosition = 1;
		int deleteConfirmation;
		struct Students student;
		FILE *database;
		FILE *databaseUpdate;
		
		database = fopen("Alunos", "rb");
		fread(&student, sizeof(student), 1, database);
			
		if(feof(database))
		{
			printf("\nNão há nenhum aluno cadastrado no sistema.\n\n");
			fclose(database);
			return;
		}
		
		printf("\nInforme a matrícula do aluno o qual deseja excluir (digite 0 para cancelar): ");
		scanf("%d", &registration);
		
		if(registration == 0)
		{
			printf("\n");
			fclose(database);
			return;
		}
		
		while(!feof(database))
		{
			if(registration == student.registration)
			{
				printf("\nMatrícula: %d", student.registration);
				printf("\nNome: %s", student.name);
				printf("\nTem certeza que deseja excluir este aluno? Digite 1 pra confirmar: ");
				scanf("%d", &deleteConfirmation);
				
				if(deleteConfirmation != 1)
				{
					fclose(database);
					printf("\n");
					return;
				}
				
				databaseUpdate = fopen("AlunosUpdate", "ab");
				rewind(database);
				fread(&student, sizeof(student), 1, database);
				
				while(!feof(database))
				{
					if(databaseUpdatePosition == databasePosition)
						fread(&student, sizeof(student), 1, database);
					else
						fwrite(&student, sizeof(student), 1, databaseUpdate);
					
					fread(&student, sizeof(student), 1, database);
					databaseUpdatePosition++;
				}
				
				fclose(database);
				fclose(databaseUpdate);
				remove("Alunos");
				rename("AlunosUpdate", "Alunos");
				printf("\n");
				return;
			}
			else
			{
				fread(&student, sizeof(student), 1, database);
			}
			
			databasePosition++;
		}
		
		fclose(database);
		printf("Erro! Nenhum aluno com encontrado com essa matrícula, tente outra.");
	}
}

//Estrutura principal com o menu principal
void main()
{
	int menuOption = 0;
	FILE *database;
	
	database = fopen("Alunos", "ab");
	setlocale(LC_ALL, "Portuguese");
	
	if(database == NULL)
	{
		printf("Erro! O arquivo não pôde ser criado. Contate o desenvolvedor.");
		return;
	}
	
	fclose(database);
	
	do
	{
		printf("MENU PRINCIPAL");
		printf("\n1 - Cadastrar Alunos e Notas");
		printf("\n2 - Alterar Alunos e Notas");
		printf("\n3 - Excluir Alunos e Notas");
		printf("\n4 - Listar Alunos e Médias");
		printf("\n5 - Listar Alunos Aprovados");
		printf("\n6 - Listar Alunos Reprovados");
		printf("\n7 - Encerrar o Programa");
		printf("\nDigite um número para escolher uma opção: ");
		scanf("%d", &menuOption);
		
		//Estrutura de seleção do menu principal
		switch(menuOption)
		{
			case 1:
				Create();
				break;
			case 2:
				Update();
				break;
			case 3:
				Delete();
				break;
			case 4:
				ReadAll();
				break;
			case 5:
				ReadApproved();
				break;
			case 6:
				ReadDisapproved();
				break;
			case 7:
				return;
			default:
				printf("Erro! Opção inválida, tente outra.\n\n");
				break;
		}
	} while (menuOption != 7);
}
