#include<stdio.h>
#include<time.h>

int dice () {		//ZAR ATMA FONKSİYONU
	return (rand()%6+1);
}

char pieceColor (int a) {		//Piyon numarasına göre rengini belirler. (Örn: 21 = K1, 33 = M3, 43 = Y3 gibi)
	if (a==1)
		return ('S');
	if (a==2)
		return ('K');
	if (a==3)
		return ('M');
	//Kalan tek ihtimal a==4
	return ('Y');
}

void locFind (int yer, int* satir, int* sutun) {		//tableC matrisinde bir satır/sütun değerini bulabilmek için kullanılır.
	int tableI[9][9] = {45,46, 0, 7, 8, 9, 0,49,50,
						48,47, 0, 6,36,10, 0,52,51,
						 0, 0, 0, 5,37,11, 0, 0, 0,
						 1, 2, 3, 4,38,12,13,14,15,
						32,33,34,35, 0,41,40,39,16,
						31,30,29,28,44,20,19,18,17,
						 0, 0, 0,27,43,21, 0, 0, 0,
						57,58, 0,26,42,22, 0,53,54,
						60,59, 0,25,24,23, 0,56,55};
	int i=0, j, found=0;
	while ( i<9 && found==0 ) {
		j=0;
		while ( j<9 && yer!=tableI[i][j] )
			j++;
		if (j<9) {
			*satir = i;
			*sutun = j;
			found = 1;
		}
		i++;
	}
}

void printTable(char tableC[][9][10]) {			//tableC matrisini(masayı) ekrana yazdırır
	int i, j;
	for (i = 0; i < 9; i++) {
		printf("\n        ");
		for (j = 0; j < 9; j++)
			printf("%c%c ", tableC[0][i][j], tableC[1][i][j]);
	}
}

int main () {
	printf("/***********************************************************/\n");
	printf("                        KIZMA BIRADER                        \n");
	printf("/***********************************************************/\n");
	srand(time(0));
	int i, j, k, l, die, tmpI, flag=0, counter, playerNo, winner, loc1, loc2, userInput1, willMove, goingToFinish, pieceLoc, playerColor[5];
	int map[33], dices[5][5], end[20], castle[20], turnCounter[20];		//0: Hiç 6 atmadı | 1: Bir kere 6 attığı için oyuna başladı | 2: O renk(sarı hariç) bir turu tamamladı
		for (i=0; i<32; i++)
			map[i] = 0;
		for (i=0; i<12; i++)
			end[i] = turnCounter[i+4] = 0;
		for (i=8; i<16; i++)
			castle[i] = 0;
		for (i=0; i<4; i++)
			turnCounter[i] = 0;
	char enter, turn[5][10] = { "SARI" , "KIRMIZI" , "MAVI" , "YESIL" };		//RENK MATRİSİ
	char tableC[2][9][10] = {{	"SS ::: KK","SS :_: KK","   :_:   ","::::_::::",":___ ___:","::::_::::","   :_:   ","YY :_: MM","YY ::: MM" },
							 {	"12 ::: 12","43 :_: 43","   :_:   ","::::_::::",":___ ___:","::::_::::","   :_:   ","12 :_: 12","43 ::: 43"	}};
	
/*	BAŞLANGIÇ MENÜSÜ  *********************************************************/

	printf("\nKac kisi oynamak istediginizi girin(2-4): ");	scanf("%d",&playerNo);		//	OYUNCU SAYISI GİRDİSİ
	if((playerNo<2) || (playerNo>4)){
		printf("\nBu oyun 2 ile 4 kisi arasinda oynanabilir!\n");
		while((playerNo<2) || (playerNo>4)){
			printf("Lutfen oyuncu sayisini tekrar giriniz: ");	scanf("%d",&playerNo);
		}
	}
	printf("\n/***********************************************************/\n");
	printf("\nOyuncularin oynama sirasi icin zar atilacaktir.\n");		//OYUNCULARIN ZAR ATMASI
	printf("Ayni zar gelme durumunda o zari ilk atan daha onde olacaktir.\n");
	printf("\nENTER tusuna basarak sirayla zar atiniz.");
		scanf("%c",&enter);
	for(i=0; i<playerNo; i++){
		printf("\n\n%d. oyuncunun zar atma sirasi", i+1);
		scanf("%c",&enter);
		if(enter==10){
			dices[i][0]=i+1;
			dices[i][1] = dice();
			printf("> %d. oyuncuya gelen zar: %d", i+1, dices[i][1]);
		}
	}
	for(i=0; i<(playerNo-1); i++)		//OYUNCULARIN SIRASINI BELİRLEME
		for(j=i+1; j<playerNo; j++){
			if(dices[i][1]<dices[j][1])
				for(k=0; k<2; k++){
					tmpI = dices[i][k];
					dices[i][k] = dices[j][k];
					dices[j][k] = tmpI;
				}
			else if((dices[i][1]==dices[j][1]) && dices[i][0]>dices[j][0])
				for(k=0; k<2; k++){
					tmpI = dices[i][k];
					dices[i][k] = dices[j][k];
					dices[j][k] = tmpI;
				}
		}
	printf("\n\n/***********************************************************/\n\n");
	
	for(i=0; i<playerNo; i++){		//OYUNCULARIN RENKLERİNİ BELİRLEME
		j=0;
		while((j<playerNo) && (dices[j][0]!=i+1))
			j++;
		if(j<playerNo){
			printf("> %d. oyuncu %s ile oynayacak.\n", i+1, turn[j]);
			playerColor[j] = i;
		}
	}
	printf("\n/***********************************************************/\n");
	
	if(playerNo==4){		//OYUNCULARA SIRALARINI SÖYLEME KISMI
		printf("\nOYNAMA SIRASI:   SARI    >  KIRMIZI  >    MAVI   >   YESIL");
		printf("\n               %d. OYUNCU > %d. OYUNCU > %d. OYUNCU > %d. OYUNCU", dices[0][0], dices[1][0], dices[2][0], dices[3][0]);
	} else if(playerNo==3){
		printf("\nOYNAMA SIRASI:   SARI    >  KIRMIZI  >    MAVI");
		printf("\n               %d. OYUNCU > %d. OYUNCU > %d. OYUNCU", dices[0][0], dices[1][0], dices[2][0]);
	} else {
		printf("\nOYNAMA SIRASI:   SARI    >  KIRMIZI");
		printf("\n               %d. OYUNCU > %d. OYUNCU", dices[0][0], dices[1][0]);
	}
	printf("\n\n/***********************************************************/\n\n");
	
	printf("--------------------------KURALLAR--------------------------");
	printf("\n\n> Her oyuncunun renkleri attigi zarlara gore belirlenir.\n> Her oyuncu 4 piyon ile baslar.");
	printf("\n> Oyun tek zar ile oynanir. Zarlar bilgisayar tarafindan rastgele belirlenir.");
	printf("\n> Oyunun basinda her piyon kendi kalesindedir. 6 atana kadar oyuna baslayamazsiniz.");
	printf("\n>>> Piyonlarinizi hareket ettirebilmek icin, ekrandaki numarasini girmeniz gerekir.");
	printf("\n> Bir karede en fazla bir adet piyon bulunabilir.\n>> Hareket ettirdiginiz piyonun varis noktasinda kendi piyonunuz varsa ilerlemeyecektir.");
	printf("\n>> Hareket ettirdiginiz piyonun varis noktasinda baska rengin piyonu varsa, o piyon kendi kalesine geri donecektir.");
	printf("\n> 6 attiginiz zaman; ister kalenizdeki bir piyonu oyuna surebilir, isterseniz de bir piyonunuzu ilerletebilirsiniz.");
	printf("\n> Eve ulasmis piyonlara rakipler tarafindan herhangi bir mudahale yapilamaz.");
	printf("\n> Dort piyonunu da evine getirebilen oyuncu, oyunu kazanir.");
	printf("\n\n>>> Oyunda her turun sonunda, yeni tura gecebilmek icin ENTER tusuna basmaniz gerekmektedir.\n>>> Iyi eglenceler.");
	
	printf("\n\nOYUNU BASLATMAK ICIN HAZIR OLDUGUNUZDA \"ENTER\" TUSUNA BASIN");
	scanf("%c",&enter);
	if(enter==10)
		winner = 5;
	printf("\n/***********************************************************/\n");
	
	for (i=0; i<playerNo; i++)			//başlangıçta oyuna dahil oyuncuların tüm piyonlarını kalelerine yerleştirme kısmı
		for (j=0; j<4; j++)
			castle[(i*4)+j] = (i*10) + (j + 11);
	
/*	OYUN  *********************************************************************/

	printf("\n\n\n\n---------------OYUN BASLIYOR---------------");
	while ( winner == 5 ) {
		for(i=0; i<32; i++){					//PİYONLARI MASADA YERLEŞTİRME
			if ( map[i] > 44 )
				map[i] = 0;
			locFind(i+1, &loc1, &loc2);
			if(map[i]!=0){
				tableC[0][loc1][loc2] = pieceColor(map[i]/10);
				tableC[1][loc1][loc2] = '0' + (map[i]%10);
			} else
				for(j=0; j<2; j++)
					tableC[j][loc1][loc2] = ':';
		}
		printf("\n");
		for (i=0; i<16; i++) {					//PİYONLARI MASAYA <-> KALEYE YERLEŞTİRME
			locFind((45 + i), &loc1, &loc2);
			if ( castle[i] == 0 ) {				//piyon masadaysa kaleye boşluk koyar
				for (j=0; j<2; j++)
					tableC[j][loc1][loc2] = '_';
			} else {							//piyon kaledeyse kaleye işaretler
				tableC[0][loc1][loc2] = pieceColor(castle[i]/10);
				tableC[1][loc1][loc2] = '0' + (castle[i]%10);
			}
		}
		printf("\n");
		for (i=0; i<12; i++) {					//SONA ULAŞAN PİYONLARI MASADA İŞARETLER
			locFind(33+i, &loc1, &loc2);
			if ( end[i] == 0 )
				for (j=0; j<2; j++)
					tableC[j][loc1][loc2] = '_';
			else {
				tableC[0][loc1][loc2] = pieceColor(end[i]/10);
				tableC[1][loc1][loc2] = '0' + (end[i]%10);
			}
		}
		
		printf("\n             - OYUN TABLOSU -");		//TABLOYU EKRANA YAZDIRMA
		printTable(tableC);
		
		for (i=0; i<playerNo; i++) {			//SIRAYLA ZAR ATIP OYNAMA	-	Oyuncu numarası map[i]/10 - Piyon numarası map[i]%10
			//Tur için varsayılan değerler
			enter = 0;					//Enter tuşunu algılamak için
			willMove = 0;				//Oyuncunun zar attıktan sonra piyonunu ilerletebilmesi için
			userInput1 = 1;				//Oyuncunun seçtiği piyon
			goingToFinish = 0;			//Piyonun bitişe gireceği
			
			die = dice();
			printf("\n\n***\n\n%s %d atti.", turn[i], die);
			if ( turnCounter[(i*4) + (userInput1-1)] != 0 )
				printf("\n\n%s OYUNCUNUN SIRASI\n", turn[i]);
			else if ( turnCounter[i*4] == 0 && die != 6 )
				printf("\n> %s oyuncunun, oyuna baslayabilmesi icin 6 atmasi gerekiyor.", turn[i]);
			
			if ( die == 6 ) {							//oyuncunun zarı 6 atma durumları
				if ( turnCounter[i*4] == 0 ) {			//Oyuncunun ilk defa 6 atıp oyuna başlaması
					printf("\n >>>    %s 6 attigi icin ilk piyonu oyuna basladi!    <<<", turn[i]);
					for(j=(i*4); j<(i+1)*4; j++)
						turnCounter[j] = 1;
					
					if ( map[i*8] != 0 ){		//Oyuncu ilk kez başlarken, başlangıç noktasında başka piyon varsa
						j = map[i*8];
						castle[ ((j/10)*4)+((j%10)-5) ] = j;
					}
					map[i*8] = (i+1)*10 + 1;
					castle[i*4] = 0;
				} else {								//Oyuncu daha önce 6 attıysa
/* Kendi piyonu */	if ( (map[i*8]/10) == (i+1) ) {
						printf("\n> Kaleden piyon cikaramazsin.\n>> Hangi piyonla oynamak istedigini gir: ", turn[i]);
						scanf("%d", &userInput1);
						willMove = 1;
						
/* Başka piyon */	} else if ( (map[i*8]/10) != 0 ) {
						printf("> Kaledeki piyonunu oyuna sokarsan onundeki rakip piyonu yiyecektir.\n>> Hangi piyonla oynamak istedigini gir: ", turn[i]);
						scanf("%d", &userInput1);
						
						while ( (userInput1<1) || (userInput1>4) ) {
							printf(">> Lutfen gecerli bir piyon seciniz: ");
							scanf("%d", &userInput1);
						}
						
						if ( castle[(i*4) + userInput1 - 1] == 0 )		//Oyundaki piyonu seçtiyse
							willMove = 1;
						else {											//Kaledeki piyonu seçtiyse
							j = map[i*8];
							castle[ (((j/10)-1)*4 + j%10)-1 ] = j;
							map[i*8] = (i+1)*10 + userInput1;
							castle[ (i*4) + (userInput1-1) ] = 0;
						}
						
/* Piyon yok */		} else {
						printf("> Kaledeki piyonunu secersen, piyon oyuna dahil olacaktir.\n>> Hangi piyonla oynamak istedigini gir: ");
						scanf("%d", &userInput1);
						
						while ( (userInput1<1) || (userInput1>4) ) {
							printf(">> Lutfen gecerli bir piyon seciniz: ");
							scanf("%d", &userInput1);
						}
						j = (i*4) + userInput1 - 1;
						if ( castle[j] != 0 ) {			//Seçilen piyonun kalede olduğu kontrolü
							map[i*8] = castle[j];
							castle[j] = 0;
						} else {
							willMove = 1;
						}
					}
				}
			} else if ( turnCounter[(i*4)+(userInput1-1)] != 0 ) {			//oyuncu önceden 6 attı ama şu an zarı 6 değil
				j = 0;
				flag = 0;
				while ( j<32 && flag==0 ) {
					for (k=1; k<=4; k++)
						if ( map[j] == (i+1)*10 + k )
							flag = 1;
					j++;
				}
				
				if ( flag == 0 ) {
					printf("> Oyunda hicbir piyonunuz olmadigi icin, 6 atana kadar oynayamazsiniz.");
				} else {
					printf("> Hangi piyonunla oynamak istedigini gir: ");
					scanf("%d", &userInput1);
					willMove = 1;
				}
			}
			
			if (willMove==1) {		//PİYONLARIN HAREKET ETTİRİLDİĞİ KISIM
			
				j = 0;
				while ( j<32 && map[j]!=((i+1)*10 + userInput1) )
					j++;
				
				pieceLoc = (i*4)+(userInput1-1);
				
				if ( i!=0 && turnCounter[pieceLoc]==1 && (j+die)>=32 )
					turnCounter[pieceLoc] = 2;
				
				if ( i == 0 )
					k = (-1);
				else
					k = (i*8) - 1;
				
				if ( (j+die)%32 > k ) {		//Zar eklenince bitiş çizgisini geçiyor
					
					if ( i == 0 && (j+die) > 31 ) {		//Sarı için
						goingToFinish = 1;
					} else 								//Sarı hariçleri için
						if ( turnCounter[pieceLoc] == 2 )
							goingToFinish = 1;
						else {
							k = map[(j+die)%32]/10;
							if ( k != i+1 && k != 0 ) {		//Turunu tamamlıyor ama önünde başka rengin piyonu var
								k = map[(j+die)%32];
								printf(">>> %c%d piyonu son hamlesiyle, %c%d piyonunu yiyerek kalesine gonderdi <<<", pieceColor(i+1), userInput1, pieceColor(k/10), k%10);
								turnCounter[(k/10)*4 + (k%10) - 5] = 1;
								castle[ (k/10)*4 + (k%10) - 5 ] = k;
							}
							goingToFinish = 0;
						}
					
					if ( goingToFinish == 1 ) {			//Bitişe girecek
						l = (i*3) + 2;
						while ( l >= (i*3) && end[l] != 0 ) 
							l--;
						
						if ( l>=(i*3) ) {		//Bitişte boş yer varsa bitişe yerleştirir
							end[l] = map[j];
							map[j] = 0;
						} else {				//Bitişte boş yer yoksa son kareye yerleştirir - OYUNU KAZANIR
							map[((i*8)+31)%32] = map[j];
							winner = i;
						}
					} else {					//Bitişe girmeyecek, yani turunu tamamlayacak
						map[(j+die)%32] = map[j];
						map[j] = 0;
					}
					
				} else {								//Zar eklenince bitiş çizgisini geçmiyor
					
					k = map[(j+die)%32];
					if ( k == 0 ) {						//Önünde piyon yok
						map[(j+die)%32] = map[j];
						map[j] = 0;
					} else if ( k/10 != i+1 ) {			//Önünde başka rengin piyonu var
						printf(">>> %c%d piyonu son hamlesiyle, %c%d piyonunu yiyerek kalesine gonderdi <<<", pieceColor(i+1), userInput1, pieceColor(k/10), k%10);
						l = (k/10)*4 + (k%10) - 5;
						turnCounter[l] = 1;
						castle[l] = k;
						map[(j+die)%32] = map[j];
						map[j] = 0;
					}
					
				}
			}
		}
		scanf("%c", &enter);
		printf("\n\nYeni tura baslamak icin ENTER tusuna basin.");
		scanf("%c", &enter);
		printf("\n\n-----------------YENI TUR-----------------\n");
	}
	printf("\n\n          OYUNU KAZANAN %d. OYUNCU (%s) OLDU! TEBRIKLER!\n\n", playerColor[winner]+1, turn[winner]);
	printTable(tableC);
	
	return 0;
}
