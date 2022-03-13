#include<stdio.h>
#define MAX 20

int shiftDirection (char);
void encrypt (char[], char[], int, int);

int main () {
	
	char password[MAX], enc[MAX], shiftChar;
	int shiftDir, shiftAmount;
	
	printf("Please enter the password you want to encrypt: ");
	scanf("%[^\n]s", &password);
	
	printf("How would you like to shift the password?\n\t1) Shift to left(L)\n\t2) Shift to right(R)\n");
	do {
		fflush(stdin);
		printf("\t\t> ");
		scanf("%c", &shiftChar);
	} while ((shiftChar != 'L' && shiftChar != 'R') && (shiftChar != 'l' && shiftChar != 'r'));
	
	printf("How much do you like to shift?\n\t> ");
	scanf("%d", &shiftAmount);
	
	shiftDir = shiftDirection(shiftChar);
	
	encrypt(password, enc, shiftDir, shiftAmount);
	
	printf("Given password %s is encrypted as: %s", password, enc);
	
	return 0;
}

int shiftDirection (char shiftChar) {
	if (shiftChar == 'L' || shiftChar == 'l') return -1;
	return 1;
}

void encrypt (char pw[], char enc[], int dir, int amo) {
	int i, j;
	char charOffset;
	
	if (dir == 1) charOffset = 'A';		//where to start from shifting
	else charOffset = 'Z';
	
	for (i = 0; pw[i] != '\0'; ++i)
		if (pw[i] >= 'A' && pw[i] <= 'Z')		//characters between A-Z
			enc[i] = charOffset + dir * ((dir * pw[i] - dir * charOffset + amo) % 26);
		else if (pw[i] >= 'a' && pw[i] <= 'z')		//characters between a-z
			enc[i] = charOffset + 32 + dir * ((dir * pw[i] - dir * (charOffset + 32) + amo) % 26);
		else						//characters that don't exist in the alphabet (they stay same)
			enc[i] = pw[i];
}
