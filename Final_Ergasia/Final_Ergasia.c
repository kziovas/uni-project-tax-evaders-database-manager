#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#pragma warning(disable:4996)
#define TRUE 1
#define FALSE 0

/*----------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------Struct Definitions--------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
struct ofiletis {
	char name[50];
	int politeknos;
	int tekna;
	float eisodima;
	float xreos;
};



/*----------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------Functions Definitions-----------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------*/
/*This function produces a new database for Debtors*/
FILE* MakeFile(char* sourcename) {
	//char name[20];
	//printf("Dwse ena onoma sto neo arxeio\n");
	//scanf("%s", name);
	printf("\n%s", sourcename);
	struct ofiletis newdebtor[20];
	char names[20][50] = { "Andreas","Kwstas","Akhs","Vaso","Giorgos","Eleni","Iaswnas","Maria","Mixalis","Apostolis","Panagiota","Aggeliki","Alexandros","Vasiliki","Gewrgia","Panos","Dionisis","Solonas","Natasa","Periklis" };
	int politeknoi[20] = { 1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0 };
	int tekna[20] =      { 4,1,2,3,0,5,0,2,4,7,1,0,3,1,2,2,4,4,2,1 };
	float eisodimata[20] = { 230000,570000,28900,234040,567980,267080,346900,3589700,56600,149000,238600,93400,234091,67980,72900,249857,987460,348905,45690,3467890 };
	float xreos[20] = { 254164,2565657,74681,908784,1245237,467000,98000,65700,2562883,2583580,6734600,125580,72459,2547460,563220,34670,129859,34698,482900,76200 };

	FILE* fp = NULL;
	fp = fopen(sourcename, "w+");
	for (int i = 1; i < 20; i++) {

		strcpy(newdebtor[i].name, names[i]);
		newdebtor[i].politeknos = politeknoi[i];
		newdebtor[i].tekna = tekna[i];
		newdebtor[i].eisodima = eisodimata[i];
		newdebtor[i].xreos = xreos[i];
		fwrite(&newdebtor[i], 1, sizeof(struct ofiletis), fp);
	}
	fclose(fp);
	return fp;
}

/*------------------------------------------------------*/
/*This function adds new debtors to an existing database*/
FILE* AddDebtor(char* sourcename) {
	struct ofiletis newdebtor;
	FILE* fp = NULL;
	//char filename[20];
	//printf("Se poio arxeio thes na prostheseis ton neon ofileth? Dwse to onoma tou arxeiou:\n");
	printf("\n%s\n", sourcename);
	printf("Dwse to onoma tou ofeileth:\t");
	scanf("%s", &newdebtor.name);
	printf("\nEinai politeknos? An NAI patiste:1 \tAn OXI patiste:0\t");
	scanf("%d", &newdebtor.politeknos);
	printf("\nDwse arithmo teknon:\t");
	scanf("%d", &newdebtor.tekna);
	printf("\nDwse eisodima:\t");
	scanf("%f", &newdebtor.eisodima);
	printf("\nDwse xreos:\t");
	scanf("%f", &newdebtor.xreos);
	fp = fopen(sourcename, "a");
	fwrite(&newdebtor, 1, sizeof(struct ofiletis), fp);
	fclose(fp);
	return fp;
}

/*------------------------------------------------------*/
/*This function shows the contents of a Debtors database*/
void ShowDebtors(char* sourcename) {

	//char filename[20];
	struct ofiletis debtor;
	FILE* fp = NULL;
	int ret = 0;
	//printf("Poio arxeio thes na diavaseis? Dwse to onoma tou arxeiou:\n");
	//scanf("%s", filename);
	fp = fopen(sourcename, "r");
	rewind(fp);

	while (1) {
		ret = fread(&debtor, sizeof(struct ofiletis), 1, fp);
		if (ret != 1) {
			break;
		}
		printf("\n------------------------------------------------------\n");
		printf("Onoma: %s\n", debtor.name);
		printf("Politeknos: %d\n", debtor.politeknos);
		printf("Tekna: %d\n", debtor.tekna);
		printf("Eisodima: %.2f\n", debtor.eisodima);
		printf("Xreos: %.2f\n", debtor.xreos);
		printf("------------------------------------------------------\n");
		//strcpy(debtor.name, "kati");
	}

	fclose(fp);
}

/*---------------------------------------------------------------------*/
/*This function produces the statistika.txt file from a source database*/
int Stats(char* sourcename, char* statname) {
	//char namestat[20],namesource[20];
	struct ofiletis debtor;
	FILE* sourcefp = NULL;
	FILE* statfp = NULL;
	int ret = 0, count1 = 0, count2 = 0, count3 = 0;
	float pososto;
	sourcefp = fopen(sourcename, "r");
	statfp = fopen(statname, "w+");
	rewind(sourcefp);
	rewind(statfp);

	while (1) {
		ret = fread(&debtor, sizeof(struct ofiletis), 1, sourcefp);
		if (ret != 1) {
			break;
		}

		//Edw metrame tous ofiletes me 4 paidia 
		if (debtor.tekna == 4) {
			count1++;
		}

		//Edw metrame tous triteknous pou exoun xreos megalitero twn 100000
		if ((debtor.tekna == 3) && (debtor.eisodima >= 100)) {
			count2++;
		}

		//Edw metrame ton sinoliko arithmo twn ofiletwn wste na ipologisoume to pososto pou mas zitite
		count3++;
	}

	//Edw ipologizoume to pososto twn triteknwn me xreos panw apo 100k 
	pososto = (float)count2 * 100 / count3;

	fprintf(statfp, "Plithos ofiletwn me 4 tekna: %d\n", count1);
	fprintf(statfp, "Pososto ofiletwn me 3 tekna kai xreos panw apo 100k: %.2f %%\n", pososto);
	fclose(sourcefp);
	fclose(statfp);
	return 0;
}

/*-----------------------------------------------------------------*/
/*This function produces the fylaki.txt file from a source database*/
int Prison(char* sourcename, char* filakiname) {
	struct ofiletis debtor;
	FILE* sourcefp = NULL;
	FILE* filakifp = NULL;
	int ret = 0;
	sourcefp = fopen(sourcename, "r");
	filakifp = fopen(filakiname, "w+");
	rewind(sourcefp);
	rewind(filakifp);

	while (1) {
		ret = fread(&debtor, sizeof(struct ofiletis), 1, sourcefp);
		if (ret != 1) {
			break;
		}

		//Edw vriskoume tous ofiletes pou dn einai politeknoi(h triteknoi), exoun eisodima >= 30k kai xreos >=250k
		if (debtor.politeknos != 1 && debtor.tekna != 3 && debtor.eisodima >= 30000 && debtor.xreos >= 250000) {
			//Egrafoume ta stoixeia tous sto arxeio fylaki.txt
			fprintf(filakifp, "Onoma: %-10s\t", debtor.name);
			fprintf(filakifp, "Xreos: %.2f\n", debtor.xreos);
		}

	}
	fclose(sourcefp);
	fclose(filakifp);
	return 0;
}



/*----------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------Main Function---------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
int main() {
	int  choice1 = 1;
	char choice2;
	char statname[20] = "statistika.txt";
	char sourcename[20] = "forofigades.dbs";
	char filakiname[20] = "fylaki.txt";
	FILE* fp = NULL;


	while (choice1 == 1) {
		printf("Gia na dimiourgisete to arxeio forofigades.dbs patiste: t\n");
		printf("Gia na prosthesete neo ofeileth sto forofigades.dbs patiste: n\n");
		printf("Gia na deite tous yparxontes forofigades patiste : y\n");
		printf("Gia na dimiourgisete to arxeio statistika.txt patiste : s\n");
		printf("Gia na dimiourgisete to arxeio fylaki.txt patiste: p\n");
		scanf(" %c", &choice2);
		if(choice2 =='t'){
			fp = MakeFile(sourcename);
			ShowDebtors(sourcename);
		}
		else if (choice2 == 'n') {
			fp = AddDebtor(sourcename);
			
		}
		else if (choice2 == 'y') {
			ShowDebtors(sourcename);
		}
		else if (choice2 == 's') {
			Stats(sourcename, statname);
		}
		else if (choice2 == 'p') {
			Prison(sourcename, filakiname);
		}
		else {
			printf("\nTo koumpi pou patisate den antistoixh se kapoia epilogh.");
		}
		printf("\nThelete na kanete kapoia allh energeia?\n Patiste: 1 gia na sinexisete \t Patiste: 0 gia na termatisete\n");
		scanf(" %d", &choice1);

	}
	//system("pause");
	return 0;

}