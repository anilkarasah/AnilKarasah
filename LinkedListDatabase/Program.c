#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define FAIL(x)                      \
	{                                \
		printf("\n\nHata: %s", (x)); \
		exit(-1);                    \
	}
#define SUCCESS(x)             \
	{                          \
		printf("! %s\n", (x)); \
	}

typedef struct lecture
{
	char classCode[8];
	char name[50];
	short capacity;
	short credit;
	int studentCount;
	int *registered;
	struct lecture *next;
} LCT;

typedef struct student
{
	int number;
	char name[20];
	char surname[20];
	short maxCredits;
	short totalCredits;
	short maxLectures;
	short totalLectures;
	struct student *prev;
	struct student *next;
} STD;

typedef struct
{
	int id;
	char classCode[8];
	int studentNo;
	char status[20];
	char date[12];
} RLT;

/*	DERS FONKSÝYONLARI	*/
void lectureOperations(LCT **, STD *, RLT *, int);
LCT *loadLecturesFromFile();
LCT *lectureAddress(LCT *, char[]);
void addLecture(LCT **, LCT *);
void deleteLecture(LCT **, char[], STD *, RLT *, int);
void printLectures(LCT *);
void saveLecturesToFile(LCT *);
/*	ÖÐRENCÝ FONKSÝYONLARI	*/
void studentOperations(STD **, LCT **, RLT **, int *, short, short);
STD *loadStudentsFromFile(short, short);
void addStudent(STD **, STD *);
void deleteStudent(STD **, LCT *, int, RLT *, int);
void deleteStudentFromFiles(STD *, LCT *, int, RLT *, int);
void printStudents(STD *);
void saveStudentsToFile(STD *, RLT *, int);
void studentSyllabus(STD *, RLT *, int);
STD *studentAddress(STD *, int);
/*	ÝLÝÞKÝ FONKSÝYONLARI	*/
RLT *loadRelationsFromFile(int *, LCT *, STD *);
void saveRelationsToFile(RLT *, STD *, int);
int addStudentToLecture(LCT *, int);
int removeStudentFromLecture(LCT *, int);
void writeStudentsToLecture(LCT *);
int addRelationBetween_SL(int *, LCT *, STD *, RLT **);
void newRelationToArray(RLT **, int *, char[], int, char[]);
void updateRelationOnArray(RLT *, int, char[], int, char[]);
int removeRelationBetween_SL(int *, LCT *, STD *, RLT **);
//////////////////////////////////
void freeEverything(LCT *, STD *, RLT *, int);

int main()
{
	setlocale(LC_ALL, "turkish");
	short menuSelector;
	LCT *lectureHead;
	STD *studentHead;
	RLT *relations;
	int relationSize = 0;
	short maxCredits, maxLectures;

	printf("Bir öðrencinin alabileceði en fazla ders sayýsý: ");
	scanf("%hd", &maxLectures);
	printf("Bir öðrencinin alabileceði en fazla kredi sayýsý: ");
	scanf("%hd", &maxCredits);

	lectureHead = loadLecturesFromFile();
	SUCCESS("Ders bilgileri baþarýyla okundu");

	studentHead = loadStudentsFromFile(maxCredits, maxLectures);
	SUCCESS("Öðrenci bilgileri baþarýyla okundu");

	relations = loadRelationsFromFile(&relationSize, lectureHead, studentHead);
	SUCCESS("Öðrenci-Ders kayýtlarý baþarýyla okundu");

	/************************** MENÜ **************************/
	do
	{
		printf("\nLütfen sýradaki iþleminizi seçiniz:\n");
		printf("1) Ders iþlemleri\n");
		printf("2) Öðrenci iþlemleri\n");
		printf("3) Konsolu temizle\n");
		printf("Diðer ÇIKIÞ\n");

		printf("\n> ");
		scanf("%hd", &menuSelector);
		switch (menuSelector)
		{
		case 1:
			lectureOperations(&lectureHead, studentHead, relations, relationSize);
			break;
		case 2:
			studentOperations(&studentHead, &lectureHead, &relations, &relationSize, maxCredits, maxLectures);
			break;
		case 3:
			system("cls");
			break;
		}

	} while (menuSelector >= 1 && menuSelector <= 3);

	freeEverything(lectureHead, studentHead, relations, relationSize);

	return 0;
}

void freeEverything(LCT *lecHead, STD *stuHead, RLT *relations, int size)
{
	LCT *nextLec;
	STD *nextStu;

	saveLecturesToFile(lecHead);
	while (lecHead != NULL)
	{
		// free(lecHead->registered);
		nextLec = lecHead->next;
		free(lecHead);
		lecHead = nextLec;
	}

	saveStudentsToFile(stuHead, relations, size);
	while (stuHead != NULL)
	{
		nextStu = stuHead->next;
		free(nextStu);
		stuHead = nextStu;
	}

	if (relations != NULL)
	{
		saveRelationsToFile(relations, stuHead, size);
		free(relations);
	}

	SUCCESS("Bellekte ayrýlan tüm alanlar boþaltýldý.");
}

void lectureOperations(LCT **lecHead, STD *stdHead, RLT *relations, int size)
{
	char classCode[8];
	short menuSelector;
	LCT *p;

	do
	{
		printf("\n\tDERS ÝÞLEMLERÝ:\n\t1) Ders ekle\n\t2) Ders kapat\n\t3) Dersleri görüntüle\n\t4) Dersleri dosyaya kaydet\n\tDiðer ÇIKIÞ");
		printf("\n\t> ");
		scanf("%hd", &menuSelector);
		switch (menuSelector)
		{
		case 1:
			if ((p = (LCT *)malloc(sizeof(LCT))) == NULL)
				FAIL("Malloc ile yer ayrýlamadý");

			fflush(stdin);
			printf("\nDers kodu: ");
			scanf("%7s", p->classCode);
			fflush(stdin);
			printf("Ders adý: ");
			scanf("%[^\n]s", p->name);
			fflush(stdin);
			printf("Dersin kapasitesi: ");
			scanf("%hd", &(p->capacity));
			printf("Dersin kredisi: ");
			scanf("%hd", &(p->credit));
			p->studentCount = 0;

			addLecture(lecHead, p);
			break;
		case 2:
			printf("Ders kodu giriniz: ");
			scanf("%7s", classCode);
			deleteLecture(lecHead, classCode, stdHead, relations, size);
			break;
		case 3:
			printLectures(*lecHead);
			break;
		case 4:
			saveLecturesToFile(*lecHead);
			break;
		}
	} while (menuSelector >= 1 && menuSelector <= 4);
}

LCT *loadLecturesFromFile()
{
	LCT *p;
	LCT *head = NULL;
	FILE *file;
	if ((file = fopen("dersler.txt", "r+")) == NULL)
		FAIL("Dersler dosyasý bulunamadý.");

	fseek(file, 0, SEEK_END);
	if (!ftell(file))
		return NULL;
	fseek(file, 0, SEEK_SET);

	while (!feof(file))
	{
		if ((p = (LCT *)malloc(sizeof(LCT))) == NULL)
			FAIL("Malloc ile yer ayrýlamadý");
		fscanf(file, "%[^,],%[^,],%hd,%hd\n", p->classCode, p->name, &(p->credit), &(p->capacity));
		if (p->classCode == NULL)
			return NULL;
		p->studentCount = 0;
		p->registered = (int *)malloc(sizeof(int));
		if (p->registered == NULL)
			FAIL("Malloc ile yer ayrýlamadý");
		addLecture(&head, p);
	}

	fclose(file);

	return head;
}

void addLecture(LCT **head, LCT *element)
{
	LCT *p, *prev;

	// Listede eleman yok
	if (*head == NULL)
	{
		*head = element;
		(*head)->next = NULL;
		return;
	}

	// Yeni eklenecek elemanýn, head elemanýnýn
	// öncesine yerleþtirilmesi gerekiyorsa
	if (strcmp(element->classCode, (*head)->classCode) < 0)
	{
		element->next = *head;
		*head = element;
		return;
	}

	prev = p = *head;
	while (p->next != NULL && strcmp(element->classCode, p->next->classCode) > 0)
	{
		prev = p;
		p = p->next;
	}

	if (p != NULL)									   //Liste henüz bitmemiþ
		if (!strcmp(element->classCode, p->classCode)) //Þu an bulunduðumuz eleman daha önceden var mý?
		{
			printf("\nAyný ders koduna sahip bir ders zaten bulunuyor.\n");
			return;
		}

	element->next = p->next;
	p->next = element; //Liste*/
}

void deleteLecture(LCT **head, char classCode[], STD *stdHead, RLT *relations, int size)
{
	LCT *tmp, *prev;
	STD *std;
	int i;

	if (*head == NULL)
	{
		printf("\nHiçbir ders bulunamadý.\n");
		return;
	}
	tmp = *head;
	if (!strcmp(tmp->classCode, classCode))
	{
		// Ýlk elemanýn silinmesi gerekiyorsa
		for (i = 0; i < size; ++i)
			if (!strcmp((relations[i]).status, "kayitli") && !strcmp((relations[i]).classCode, classCode))
			{
				std = studentAddress(stdHead, (relations[i]).studentNo);
				(std->totalLectures)--;
				(std->totalCredits) -= (*head)->credit;
				strcpy((relations[i]).status, "ders kapandi");
			}
		*head = tmp->next;
		free(tmp);
		printf("%s baþarýyla silindi!", classCode);
		return;
	}
	while (tmp != NULL && strcmp(tmp->classCode, classCode))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		printf("Aradýðýnýz ders bulunamadý.");
		return;
	}
	for (i = 0; i < size; ++i)
		if (!strcmp((relations[i]).status, "kayitli") && !strcmp((relations[i]).classCode, classCode))
		{
			std = studentAddress(stdHead, (relations[i]).studentNo);
			(std->totalLectures)--;
			(std->totalCredits) -= tmp->credit;
			strcpy((relations[i]).status, "ders kapandi");
		}
	prev->next = tmp->next;
	free(tmp);
	printf("%s baþarýyla silindi!", classCode);
}

void printLectures(LCT *head)
{
	int i, j;
	int k;
	if (head == NULL)
	{
		printf("\nHiçbir ders bulunamadý.\n");
		return;
	}
	printf("\n%5s %10s %50s %10s %10s", "#", "DERS KODU", "DERS ADI", "KAPASÝTE", "KREDÝ");
	k = 0;
	while (head != NULL)
	{
		printf("\n%5d %10s: %49s %6d/%3d %10d", ++k, head->classCode, head->name, head->studentCount, head->capacity, head->credit);

		j = head->studentCount;
		if (j != 0)
		{
			printf("\n\t\tBu derse kayýtlý öðrenciler:");
			for (i = 0; i < j; ++i)
				printf("\n\t\t\t> %d", (head->registered)[i]);
		}

		head = head->next;
	}
}

void saveLecturesToFile(LCT *head)
{
	FILE *file;
	if ((file = fopen("dersler.txt", "w+")) == NULL)
		FAIL("Dersler dosyasý bulunamadý.");

	while (head != NULL)
	{
		fprintf(file, "%s,%s,%d,%d\n", head->classCode, head->name, head->credit, head->capacity);
		writeStudentsToLecture(head);
		head = head->next;
	}
	fclose(file);

	SUCCESS("Dersler baþarýyla dosyaya kaydedildi.");
}

LCT *lectureAddress(LCT *head, char code[])
{
	while (head != NULL && strcmp(head->classCode, code) != 0)
		head = head->next;
	return head;
	// while'dan çýkýnca head NULL ise öyle bir ders bulunamamýþtýr
	// aksi taktirde head ile dersin adresi döndürülür
}

void studentOperations(STD **stuHead, LCT **lecHead, RLT **relations, int *size, short maxC, short maxL)
{
	short menuSelector;
	STD *currStd;
	LCT *currLec;
	int id;
	char classCode[8];

	do
	{
		printf("\n\tÖÐRENCÝ ÝÞLEMLERÝ:\n\t1) Öðrenci ekle\n\t2) Öðrenci sil\n\t3) Öðrencileri görüntüle\n\t4) Öðrenciyi derse kaydet\n\t5) Öðrenciyi dersten sil\n\t6) Ders programý görüntüle ve kaydet\n\t7) Öðrencileri dosyaya kaydet\n\tDiðer ÇIKIÞ");
		printf("\n\t> ");
		scanf("%hd", &menuSelector);
		switch (menuSelector)
		{
		case 1:
			if ((currStd = (STD *)malloc(sizeof(STD))) == NULL)
				FAIL("Malloc ile yer ayrýlamadý");

			currStd->maxCredits = maxC;
			currStd->maxLectures = maxL;
			printf("\nÖðrenci numarasý: ");
			scanf("%d", &(currStd->number));
			fflush(stdin);
			printf("Öðrencinin ismi: ");
			scanf("%[^\n]s", currStd->name);
			fflush(stdin);
			printf("Öðrencinin soyismi: ");
			scanf("%[^\n]s", currStd->surname);
			fflush(stdin);
			currStd->totalCredits = currStd->totalLectures = 0;
			currStd->maxCredits = maxC;
			currStd->maxLectures = maxL;
			addStudent(stuHead, currStd);
			break;
		case 2:
			printf("Öðrenci numarasýný giriniz: ");
			scanf("%d", &id);
			deleteStudent(stuHead, *lecHead, id, *relations, *size);
			break;
		case 3:
			printStudents(*stuHead);
			break;
		case 4:
			printf("Öðrenci numarasý giriniz: ");
			scanf("%d", &id);
			currStd = studentAddress(*stuHead, id);
			if (currStd == NULL)
			{
				printf("Aradýðýnýz öðrenci bulunamadý.");
				return;
			}
			printf("Ders kodunu giriniz: ");
			scanf("%7s", classCode);
			currLec = lectureAddress(*lecHead, classCode);
			if (currLec == NULL)
			{
				printf("Aradýðýnýz ders bulunamadý.");
				return;
			}
			if (addRelationBetween_SL(size, currLec, currStd, relations))
				printf("\n%s %s isimli öðrenci %s koduna sahip %s dersine kaydedildi.", currStd->name, currStd->surname, currLec->classCode, currLec->name);

			break;
		case 5:
			printf("Öðrenci numarasý giriniz: ");
			scanf("%d", &id);
			currStd = studentAddress(*stuHead, id);
			if (currStd == NULL)
			{
				printf("Aradýðýnýz öðrenci bulunamadý.");
				return;
			}
			printf("Ders kodunu giriniz: ");
			scanf("%7s", classCode);
			currLec = lectureAddress(*lecHead, classCode);
			if (currLec == NULL)
			{
				printf("Aradýðýnýz ders bulunamadý.");
				return;
			}
			if (removeRelationBetween_SL(size, currLec, currStd, relations))
				printf("\n%s %s isimli öðrenci %s koduna sahip %s dersinden silindi.", currStd->name, currStd->surname, currLec->classCode, currLec->name);

			break;
		case 6:
			printf("Ders programýný görüntülemek istediðiniz öðrencinin numarasýný giriniz: ");
			scanf("%d", &id);
			currStd = studentAddress(*stuHead, id);
			if (currStd == NULL)
				printf("Öðrenci bulunamadý.");
			else if (relations == NULL)
				printf("Öðrencinin kayýtlý olduðu hiçbir ders yok.");
			else
				studentSyllabus(currStd, *relations, *size);
			break;
		case 7:
			saveStudentsToFile(*stuHead, *relations, *size);
			break;
		}
	} while (menuSelector >= 1 && menuSelector <= 7);
}

STD *loadStudentsFromFile(short maxC, short maxL)
{
	STD *p;
	STD *head = NULL;
	FILE *file;
	if ((file = fopen("ogrenciler.txt", "r+")) == NULL)
		FAIL("Öðrenciler dosyasý bulunamadý.");

	fseek(file, 0, SEEK_END);
	if (!ftell(file))
		return NULL;
	fseek(file, 0, SEEK_SET);

	while (!feof(file))
	{
		if ((p = (STD *)malloc(sizeof(STD))) == NULL)
			FAIL("Malloc ile yer ayrýlamadý");

		fscanf(file, "%d,%[^,],%[^,],%hd,%hd\n", &(p->number), p->name, p->surname, &(p->totalCredits), &(p->totalLectures));
		if ((p->name)[0] == '\0')
			return NULL;
		p->maxCredits = maxC;
		p->maxLectures = maxL;
		addStudent(&head, p);
	}

	fclose(file);

	return head;
}

void addStudent(STD **head, STD *element)
{
	STD *p, *prev;

	// Listede eleman yok
	if (*head == NULL)
	{
		*head = element;
		(*head)->prev = NULL;
		(*head)->next = NULL;
		return;
	}

	if (element->number == (*head)->number)
	{
		printf("\nAyný öðrenci numarasýna sahip bir öðrenci zaten bulunuyor.\n");
		return;
	}

	// Yeni eklenecek elemanýn, head elemanýnýn
	// öncesine yerleþtirilmesi gerekiyorsa
	if (element->number < (*head)->number)
	{
		element->next = *head;
		(*head)->prev = element;
		element->prev = NULL;
		*head = element;
		return;
	}

	prev = p = *head;
	while (p->next != NULL && element->number > p->next->number)
	{
		prev = p;
		p = p->next;
	}

	if (p->next != NULL && element->number == p->next->number)
	{
		printf("\nAyný öðrenci numarasýna sahip bir öðrenci zaten bulunuyor.\n");
		return;
	}

	element->next = p->next;
	element->prev = p;
	p->next = element;
	// Listenin son elemaný deðilse baðlama amaçlý
	if (element->next != NULL)
		element->next->prev = element;
}

void deleteStudent(STD **head, LCT *lecHead, int id, RLT *relations, int rltSize)
{
	STD *tmp, *prev;
	int i;
	if (*head == NULL)
	{
		printf("\nHiçbir öðrenci bulunamadý.\n");
		return;
	}

	tmp = *head;
	if ((*head)->number == id)
	{
		// Ýlk öðrencinin silinmesi gerekiyorsa
		prev = *head;
		deleteStudentFromFiles(prev, lecHead, id, relations, rltSize);
		*head = (*head)->next;
		(*head)->prev = NULL;
		free(prev);
		return;
	}

	while (tmp != NULL && tmp->number != id)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		printf("\nAradýðýnýz öðrenci bulunamadý.\n");
		return;
	}

	deleteStudentFromFiles(tmp, lecHead, id, relations, rltSize);
	prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = prev;
	free(tmp);
}

void deleteStudentFromFiles(STD *curr, LCT *lecHead, int id, RLT *relations, int rltSize)
{
	LCT *currLec;
	int *tmpRegistered;
	int i, j, k, size;

	for (i = 0; i < rltSize; ++i)
	{
		// DersKayýt dosyasýndan öðrencinin kayýtlý olduðu dersleri bulup, listelerinden sildiðimiz kýsým
		if ((relations[i]).studentNo == curr->number)
		{
			currLec = lectureAddress(lecHead, (relations[i]).classCode);
			size = currLec->studentCount;
			(currLec->studentCount)--;
			if (size == 1)
			{
				free(currLec->registered);
				currLec->registered = NULL;
			}
			else if (size) //size 0 deðilse
			{
				tmpRegistered = (int *)malloc((size - 1) * sizeof(int));
				if (tmpRegistered == NULL)
					FAIL("Malloc ile yer ayrýlamadý");
				k = 0;
				for (j = 0; j < size; ++j)
					if ((currLec->registered)[j] != id)
						tmpRegistered[k++] = (currLec->registered)[j];

				free(currLec->registered);
				currLec->registered = tmpRegistered;
			}
		}

		// Öðrencinin DersKayýt dosyasýndaki ilgili tüm durumlarýný "býraktý" olarak güncelleme kýsmý
		if (!strcmp((relations[i]).status, "kayitli") && (relations[i]).studentNo == id)
			strcpy((relations[i]).status, "birakti");
	}

	printf("\n%d nolu öðrenci baþarýyla silindi!\n", id);
}

void printStudents(STD *head)
{
	int k;
	if (head == NULL)
	{
		printf("\nHiçbir öðrenci bulunamadý.\n");
		return;
	}

	k = 0;
	printf("\n%5s %20s %20s %10s %15s %15s\n", "#", "ÝSÝM", "SOYÝSÝM", "NUMARA", "KREDÝ HAKKI", "DERS HAKKI");
	while (head != NULL)
	{
		printf("%5d %20s %20s %10d %12d/%2d %12d/%2d\n", ++k, head->name, head->surname, head->number, head->totalCredits, head->maxCredits, head->totalLectures, head->maxLectures);
		head = head->next;
	}
}

void saveStudentsToFile(STD *head, RLT *relations, int size)
{
	FILE *file;
	if ((file = fopen("ogrenciler.txt", "w")) == NULL)
		FAIL("Dosyaya yazma hatasý.");

	while (head != NULL)
	{
		fprintf(file, "%d,%s,%s,%hd,%hd\n", head->number, head->name, head->surname, head->totalCredits, head->totalLectures);
		head = head->next;
	}
	fclose(file);
	SUCCESS("Öðrenciler baþarýyla dosyaya kaydedildi.");
}

void studentSyllabus(STD *curr, RLT *relations, int size)
{
	int i, j;
	char fileName[50] = "DersProgramlari/";
	char idStr[12];
	FILE *file;

	itoa(curr->number, idStr, 10);
	strcat(fileName, idStr);
	strcat(fileName, "_DERSPROGRAMI.txt");

	if ((file = fopen(fileName, "w")) == NULL)
		FAIL("Ders programý dosyasý açýlamadý.");

	j = 0;
	for (i = 0; i < size; ++i)
	{
		if (!strcmp((relations[i]).status, "kayitli") && (relations[i]).studentNo == curr->number)
		{
			printf("%s\n", (relations[i]).classCode);
			fprintf(file, "%s\n", (relations[i]).classCode);
			++j;
		}
	}

	fclose(file);

	if (!j)
		printf("Öðrencinin kayýtlý olduðu hiçbir ders yok.");
}

STD *studentAddress(STD *head, int no)
{
	while (head != NULL && head->number != no)
		head = head->next;
	return head;
	// head NULL dönerse öðrenci bulunamamýþtýr
	// aksi taktirde ilgili öðrencinin linkli liste adresi döndürülür
}

RLT *loadRelationsFromFile(int *size, LCT *lctHead, STD *stdHead)
{
	RLT *array;
	RLT *tmp;
	LCT *curr;
	FILE *file;
	if ((file = fopen("OgrenciDersKayit.txt", "r+")) == NULL)
		FAIL("ÖðrenciDersKayit dosyasý bulunamadý.");

	fseek(file, 0, SEEK_END);
	if (!ftell(file))
		return NULL;
	fseek(file, 0, SEEK_SET);

	if ((array = (RLT *)malloc(sizeof(RLT))) == NULL)
		FAIL("Malloc ile yer ayrýlamadý.");

	while (!feof(file))
	{
		if (*size != 0)
		{
			tmp = (RLT *)realloc(array, (*size + 1) * sizeof(RLT));
			if (tmp == NULL)
				FAIL("Realloc ile yer ayrýlamadý");
			array = tmp;
		}

		fscanf(file, "%d,%[^,],%d,%[^,],%[^\n]\n", &((array[*size]).id), (array[*size]).classCode, &((array[*size]).studentNo), (array[*size]).date, (array[*size]).status);

		if (!strcmp((array[*size]).status, "kayitli"))
		{
			curr = lectureAddress(lctHead, (array[*size]).classCode);
			addStudentToLecture(curr, (array[*size]).studentNo);
		}

		(*size)++;
	}
	fclose(file);

	return array;
}

void saveRelationsToFile(RLT *relations, STD *head, int size)
{
	int i;
	FILE *programFile;
	FILE *file;
	char fileName[50];
	char idStr[12];
	STD *curr;

	if ((file = fopen("OgrenciDersKayit.txt", "w")) == NULL)
		FAIL("OgrenciDersKayit dosyasý bulunamadý.");

	for (i = 0; i < size; ++i)
	{
		// DersKayýt iliþkisinde kayýtlý bilgiye ulaþýlýrsa bunu o öðrencinin ders programýna kaydetmek
		if (!strcmp((relations[i]).status, "kayitli"))
		{
			strcpy(fileName, "DersProgramlari/");
			itoa((relations[i]).studentNo, idStr, 10);
			strcat(fileName, idStr);
			strcat(fileName, "_DERSPROGRAMI.txt");
			if ((programFile = fopen(fileName, "r")) != NULL)
			{
				programFile = fopen(fileName, "w");
				curr = studentAddress(head, (relations[i].studentNo));
				// saveStudentProgramToFile(curr, relations[i], fileName);
			}
			fclose(programFile);
		}
		fprintf(file, "%d,%s,%d,%s,%s\n", (relations[i]).id, (relations[i]).classCode, (relations[i]).studentNo, (relations[i]).date, (relations[i]).status);
	}

	fclose(file);
}

int addStudentToLecture(LCT *curr, int studentID)
{
	int i, j;
	int size = (curr->studentCount)++;
	curr->registered = (int *)realloc(curr->registered, sizeof(int) * (size + 2));
	if (curr->registered == NULL)
		FAIL("Realloc ile yer ayrýlamadý.");

	i = 0;
	while (i < size && (curr->registered)[i] < studentID)
		i++;

	if ((curr->registered)[i] == studentID)
	{
		printf("Öðrenci zaten bu derse kayýtlý!");
		(curr->studentCount)--;
		return 0;
	}

	if (i < size)
	{
		// öðrenci numarasý ortalarda olacaðý için dizinin kalanýnda öteleme iþlemi yapýlmalý
		for (j = size; j > i; --j)
			(curr->registered)[j] = curr->registered[j - 1];
	}
	(curr->registered)[i] = studentID;

	return 1;
}

int removeStudentFromLecture(LCT *curr, int studentID)
{
	int i, j, k;
	int size = (curr->studentCount)--;
	int *tmp;

	if (size == 1)
	{
		free(curr->registered);
		return 1;
	}

	i = 0;
	while (i < size && (curr->registered)[i] != studentID)
		++i;

	if (i < size) // doðruysa i'de aranan öðrencinin indisi var
	{
		tmp = (int *)malloc((size - 1) * sizeof(int));
		if (tmp == NULL)
			FAIL("Malloc ile yer ayrýlamadý.");

		for (j = 0; j < size; ++j)
			if (j != i)
				tmp[k++] = (curr->registered)[i];

		curr->registered = tmp;

		return 1;
	}

	printf("Aradýðýnýz öðrenci bulunamadý.");
	return 0;
}

void writeStudentsToLecture(LCT *curr)
{
	int i, size;
	char fileName[30] = "OgrenciListeleri/";
	FILE *file;

	size = curr->studentCount;
	// Eðer o derse hiçbir öðrenci kayýtlý deðilse geri kalan iþlemler yapýlmamalý
	if (!size)
		return;

	strcat(fileName, curr->classCode);
	strcat(fileName, ".txt");
	if ((file = fopen(fileName, "w")) == NULL)
		FAIL("Dosyaya yazma hatasý.");

	for (i = 0; i < size; ++i)
		fprintf(file, "%d\n", (curr->registered)[i]);

	fclose(file);
}

int addRelationBetween_SL(int *size, LCT *currLec, STD *currStd, RLT **relations)
{
	int i, j;
	if (currLec->studentCount == currLec->capacity)
	{
		printf("Dersin kontenjaný dolu olduðu için yeni öðrenci eklenemedi.");
		return 0;
	}

	if ((currStd->totalLectures == currStd->maxLectures) || (currStd->totalCredits + currLec->credit > currStd->maxCredits))
	{
		printf("Öðrencinin kredi veya ders limiti yetmediði için derse kaydedilemedi.");
		return 0;
	}

	if (!addStudentToLecture(currLec, currStd->number))
		return 0;
	newRelationToArray(relations, size, currLec->classCode, currStd->number, "kayitli");
	(currStd->totalLectures)++;
	(currStd->totalCredits) += currLec->credit;

	return 1;
}

void newRelationToArray(RLT **relations, int *size, char classCode[], int id, char status[])
{
	RLT newR;
	char date[12];

	if (*relations == NULL)
		newR.id = 10000;
	else
		newR.id = ((*relations)[*size - 1]).id + 1;

	strcpy(newR.classCode, classCode);
	newR.studentNo = id;
	strcpy(newR.status, status);
	printf("Bugünün tarihini giriniz (gg.aa.yyyy formatýnda): ");
	scanf("%10s", date);
	strcpy(newR.date, date);
	(*size)++;
	*relations = (RLT *)realloc(*relations, sizeof(RLT) * (*size));
	(*relations)[*size - 1] = newR;
}

void updateRelationOnArray(RLT *relations, int size, char classCode[], int id, char status[])
{
	int i;
	for (i = 0; i < size; ++i)
	{
		if ((relations[i]).studentNo == id && !strcmp((relations[i]).classCode, classCode))
		{
			strcpy((relations[i]).status, status);
			return;
		}
	}
}

int removeRelationBetween_SL(int *size, LCT *currLec, STD *currStd, RLT **relations)
{
	int i, j;
	if (currLec->studentCount == 0)
	{
		printf("Bu derse kayýtlý hiçbir öðrenci bulunamadý.");
		return 0;
	}

	if (currStd->totalLectures == 0)
	{
		printf("Öðrencinin kayýtlý olduðu hiçbir ders bulunamadý.");
		return 0;
	}

	if (!removeStudentFromLecture(currLec, currStd->number))
		return 0;
	updateRelationOnArray(*relations, *size, currLec->classCode, currStd->number, "birakti");
	(currStd->totalLectures)--;
	(currStd->totalCredits) -= currLec->credit;

	return 1;
}
