#include <stdio.h>
#define MAX 20
#define ITR 20
#define PI 3.1415926535897932384626433832795
#define N_E 2.7182818284590452353602874713527

double calcPI(int);                                                                       // program çalýþýnca pi sayisini hesaplar
double calcE(int);                                                                        // program calisinca e sayisini hesaplar
double floatMut(double);                                                                  // float ve double deðerlerin mutlak deðerini bulur
double floatMod(double, double);                                                          // float ve double deðerlerin modunu alýr
void reset(double[][MAX], int, int);                                                      // matrisin tüm deðerlerini 0'a eþitler
void getEquations(double[][MAX], int *);                                                  // Gauss Seidel yönteminin denklemlerini alýr
void printEquations(double[][MAX], int);                                                  // Gauss Seidel yönteminin denklemlerini ekrana yazdýrýr
void printEqRes(double[], int);                                                           // Gauss Seidel yöntemi sonucunda bulunan kökleri ekrana yazdýrýr
void sortMatrixDiagonally(double[][MAX], int);                                            // Gauss Seidel yöntemi için denklem takýmlarýný köþegen bazýnda sýralar
void getM(double[][MAX], int *);                                                          // kullanýcýdan matris alýr
void printM(double[][MAX], int, int);                                                     // ekrana matrisi yazdýrýr
int create(double[][MAX]);                                                                // kullanýcýdan fonksiyon türlerini ve deðerlerini alýr
double calc(double[][MAX], double, int, double, double);                                  // alýnan fonksiyonu verilen x deðerine göre hesaplar
double derivate(double[][MAX], double[][MAX], double, int, double, int, double, double);  // alýnan fonksiyonun türev deðerini hesaplar
void gregoryNewtonMtr(double[][MAX], int);                                                // Gregory Newton yöntemi için kullanýcýdan x ve y deðerleri alýr
double gregoryNewton(double[][MAX], int, double, double);                                 // Gregory Newton yöntemi
double trapez(double, double, double[][MAX], int, int, double);                           // Trapez yöntemi
double tmpTrapez(double, double, double[][MAX], int, int, double);                        // Trapez yöntemi için iþlem yapar
double simpson(double, double, double[][MAX], int, int, double, int);                     // Simpson 1/3 ve 3/8 yöntemleri
double tmpSimpson1_3(double, double, int, double, double[][MAX], int, double);            // Simpson 1/3 yöntemi için iþlem yapar
double tmpSimpson3_8(double, double, int, double[][MAX], int, double);                    // Simpson 3/8 yöntemi için iþlem yapar
double calcPol(double[][MAX], double, int);                                               // kullanýcýdan alýnan polinomu hesaplar
double calcSin(double, double, double);                                                   // kullanýcýdan alýnan sinüsü hesaplar
double calcCos(double, double, double);                                                   // kullanýcýdan alýnan cosinüsu hesaplar
double calcLn(double);                                                                    // kullanýcýdan alýnan ln fonksiyonunu hesaplar
double calcLog(double, double);                                                           // kullanýcýdan alýnan logaritmayý hesaplar
double calcUst(double, double);                                                           // kullanýcýdan alýnan üstel ifadeyi hesaplar
double calcExp(double);                                                                   // kullanýcýdan alýnan e^x ifadesini hesaplar
double calcKok(double);                                                                   // kullanýcýdan alýnan karekök ifadesini hesaplar
double bisection(double[][MAX], double, double, double, int, double);                     // Bisection yöntemi
double interp(double[][MAX], double, double, double, int, double);                        // Enterpolasyon yöntemi
double newtonRaphson(double[][MAX], double[][MAX], double, double, int, double, double);  // Newton-Raphson yöntemi
void printItr(char[], int);                                                               // Bazý yöntemlerin kaç iterasyonda tamamlandýðýný ekrana yazdýrýr
void printResult(double[][MAX], double, int, double);                                     // Bulunan kökü ekrana yazdýrýr
void gaussElemination(double[][MAX], int);                                                // Gauss Eleminasyon yöntemi
int gaussSeidel(double[][MAX], double[], int, double, int);                               // Gauss Seidel yöntemi
void upperTriangular(double[][MAX], int, int);                                            // Aldýðý matrisi üst üçgen matris formatýna getirir
void lowerTriangular(double[][MAX], int, int);                                            // Aldýðý matrisi alt üçgen matris formatýna getirir
void diagonalValuesToOne(double[][MAX], int, int);                                        // Aldýðý matrisin köþegen elemanlarýný 1'e eþitleyecek iþlemler yapar

int main() {
    int i, j, k, size, choice, menu, derece, yontem, n;
    double mtr[MAX][MAX], fonk[2][MAX], denk[MAX][MAX], der[2][MAX], eqRes[MAX], gregNewtMtr[MAX][MAX];
    double x, x1, eps, pi, num_e, integral, alt, ust;
    char kosegendeSirala;

    n = 100;
    pi = calcPI(n);
    printf("pi sayisi; %d iterasyonda, %.16f olarak hesaplandi. (Hata = %.16f)\n", n, pi, floatMut(PI - pi));
    num_e = calcE(n);
    printf("e  sayisi; %d iterasyonda, %.16f olarak hesaplandi. (Hata = %.16f)\n", n, num_e, floatMut(N_E - num_e));

    do {
        printf("\n1) Fonksiyon Islemleri\n2) Matris Islemleri\n3) Denklem Takimi Cozumu(Gauss-Seidel Yontemi)\n4) Yaklasik Deger Hesaplama(Gregory Newton Enterpolasyonu)\n0) CIKIS\n\n> ");
        scanf("%d", &choice);

        if (choice == 1) {  // FONKSÝYON ÝÞLEMLERÝ
            reset(fonk, 2, MAX);
            reset(der, 2, MAX);
            printf(" Yeni denklem olustur:\n");
            derece = create(fonk);
            do {
                printf("\n 1) Degiskeni kendin sec\n 2) Kok bul\n 3) Turev al\n 4) Integral al\n 0) MENUYE DON\n\n>> ");
                scanf("%d", &menu);
                if (menu == 1) {  // DEÐÝÞKEN SEÇ
                    printf("  Kac kez degisken gireceksiniz: ");
                    scanf("%d", &j);
                    for (i = 0; i < j; i++) {
                        printf("\n  x = ");
                        scanf("%lf", &x);

                        while ((fonk[0][3] != 0 || fonk[0][4] == 1) && x <= 0) {
                            printf("  Girdiginiz x degeri logaritmik fonksiyonlarin tanim araligini bozmaktadir.\n  x = ");
                            scanf("%lf", &x);
                        }
                        while (fonk[0][9] != 0 && x < 0) {
                            printf("  Girdiginiz x degeri koklu ifadenin tanim araligina uymamaktadir.\n  x = ");
                            scanf("%lf", &x);
                        }

                        printf("  f(%2.3lf) = %3.7lf\n", x, calc(fonk, x, derece, pi, 0));
                    }
                } else if (menu == 2) {  // KÖK BUL
                    printf("\n Hangi yontemi kullanacaginizi giriniz:\n 1) Aralik Yarilama(Bisection)\n 2) Interpolasyon(Regula Falsi)\n 3) Newton-Raphson Yontemi\n\n>>> ");
                    scanf("%d", &yontem);
                    if (yontem == 1) {  // Bisection
                        printf("  Araligi girin: ");
                        scanf("%lf %lf", &x, &x1);
                        printf("  Hata payini girin: ");
                        scanf("%lf", &eps);
                        printResult(fonk, bisection(fonk, x, x1, eps, derece, pi), derece, pi);
                    } else if (yontem == 2) {  //Ýnterpolasyon
                        printf("  Araligi girin: ");
                        scanf("%lf %lf", &x, &x1);
                        printf("  Hata payini girin: ");
                        scanf("%lf", &eps);
                        printResult(fonk, interp(fonk, x, x1, eps, derece, pi), derece, pi);
                    } else if (yontem == 3) {  // Newton-Raphson
                        printf("  Baslangic kokunu girin: ");
                        scanf("%lf", &x);
                        printf("  Hata payini girin: ");
                        scanf("%lf", &eps);
                        printResult(fonk, newtonRaphson(fonk, der, x, eps, derece, pi, num_e), derece, pi);
                    }
                } else if (menu == 3) {  // TÜREV AL
                    do {
                        printf("\n  Hangi yontemle turev almak istediginizi giriniz:\n  1) Ileri fark\n  2) Geri fark\n  3) Merkezi fark\n  4) Gercek Turev\n  0) CIKIS\n\n>>> ");
                        scanf("%d", &yontem);
                        if (yontem > 0) {
                            eps = 0;
                            if (yontem != 4) {
                                printf("  Hata payini girin: ");
                                scanf("%lf", &eps);
                            }
                            printf("  Kac farkli deger icin turev alacaksiniz: ");
                            scanf("%d", &j);
                            for (i = 0; i < j; i++) {
                                printf("   x = ");
                                scanf("%lf", &x);
                                printf("   %.3lf icin turev degeri %.7lf\n", x, derivate(fonk, der, x, derece, eps, yontem, pi, num_e));
                            }
                        }
                    } while (yontem > 0);
                } else if (menu == 4) {  //ÝNTEGRAL AL
                    do {
                        printf("\n  Hangi yontemle integral almak istediginizi giriniz:\n  1) Trapez\n  2) Simpson\n  0) CIKIS\n\n>>> ");
                        scanf("%d", &yontem);
                        if (yontem > 0) {
                            printf("\n   Kac defa integral almak istediginizi girin: ");
                            scanf("%d", &j);
                            for (i = 0; i < j; i++) {
                                printf("\n    Integralin alt ve ust sinirlarini sirasiyla giriniz: ");
                                scanf("%lf %lf", &alt, &ust);
                                printf("\n    Aralik sayisini(n) giriniz: ");
                                scanf("%d", &n);
                                if (yontem == 1) {
                                    integral = trapez(alt, ust, fonk, n, derece, pi);
                                } else if (yontem == 2) {
                                    printf("\n     Simpson Integral yontemlerinden hangisini kullanacaksiniz?\n   1) Simpson 1/3\n   2) Simpson 3/8\n\n>>>> ");
                                    scanf("%d", &k);
                                    integral = simpson(alt, ust, fonk, n, derece, pi, k);
                                }
                                printf("\n   Girdiginiz sinirlar icerisinde integralin sonucu %.7lf\n", integral);
                            }
                        }
                    } while (yontem > 0);
                } else if (menu == 5) {
                }
            } while (menu > 0);
        } else if (choice == 2) {  // MATRÝS ÝÞLEMLERÝ
            reset(mtr, MAX, MAX);
            printf(" Yeni kare matris olustur:\n (Gireceginiz matrisin boyutu en fazla 10 olabilir)\n\n");
            getM(mtr, &size);  // Matris al

            do {
                printf("\n  1) Matrisin inversini bul\n  2) Ust ucgen matrisi bul\n  3) Alt ucgen matrisi bul\n  0) CIKIS\n\n>> ");
                scanf("%d", &menu);
                if (menu == 1) {  // Tersini bul
                    gaussElemination(mtr, size);
                } else if (menu == 2) {  //Üst üçgen matrisi bul
                    upperTriangular(mtr, size, size);
                } else if (menu == 3) {  // Alt üçgen matrisi bul
                    lowerTriangular(mtr, size, size);
                }
                printM(mtr, size, size);
            } while (menu > 0);
        } else if (choice == 3) {  // DENKLEM TAKIMI ÝÞLEMLERÝ
            reset(mtr, MAX, MAX);
            getEquations(mtr, &size);
            do {  // Denklem takýmý matrisinin köþegende maksimum olacak þekilde sýralanmasý isteniyor mu?
                printf("\n ! Denklem takiminin kosegen uzerinde mutlak degerce maksimum olarak siralanmasini istiyor musunuz? (E/H)\n  > ");
                scanf(" %c", &kosegendeSirala);
            } while ((kosegendeSirala != 'E' && kosegendeSirala != 'e') && (kosegendeSirala != 'H' && kosegendeSirala != 'h'));
            if (kosegendeSirala == 'E' || kosegendeSirala == 'e') {
                k = 1;
            } else {
                k = 0;
            }
            printf("\n Hata payini giriniz: ");
            scanf("%lf", &eps);
            j = gaussSeidel(mtr, eqRes, size, eps, k);
            printEquations(mtr, size);
            if (j == -1) {
                printf("  !!! Verilen denklem takiminin kokleri iraksadigi icin sonuc uretilemedi.\n");
            } else {
                printEqRes(eqRes, size);
            }
        } else if (choice == 4) {  // GREGORY NEWTON ENTERPOLASYONU
            do {
                reset(gregNewtMtr, MAX, MAX);
                printf("\n  Kac adet deger gireceksiniz? (0 - CIKIS)\n  > ");
                scanf("%d", &n);
                if (n > 0) {
                    while (n > MAX) {
                        printf("\n\n   En fazla 20 deger girebilirsiniz.\n   > ");
                        scanf("%d", &n);
                    }
                    printf("\n  Gireceginiz x degerleri arasinda belli bir fark olmalidir. Lutfen bu farki giriniz:\n");
                    do {
                        printf("  > ");
                        scanf("%lf", &eps);
                    } while (eps == 0);
                    printf("\n   > X0 = ");
                    scanf("%lf", &gregNewtMtr[0][0]);
                    printf("\n");
                    for (i = 0; i < n; i++) {
                        printf("    > X%d = %.3lf icin f(%.2lf) = ", i, gregNewtMtr[i][0], gregNewtMtr[i][0]);
                        scanf("%lf", &gregNewtMtr[i][1]);
                        if (i < n - 1) {
                            gregNewtMtr[i + 1][0] = gregNewtMtr[i][0] + eps;
                        }
                    }
                    gregoryNewtonMtr(gregNewtMtr, n);
                    printf("\n  Kac farkli deger icin yaklasik deger hesaplayacaksiniz?\n  > ");
                    scanf("%d", &k);
                    for (i = 0; i < k; i++) {
                        printf("   > x = ");
                        scanf("%lf", &x);
                        printf("   --> F(%.2lf) = %.4lf\n\n", x, gregoryNewton(gregNewtMtr, n, eps, x));
                    }
                }
            } while (n > 0);
        }
    } while (choice > 0);

    printf("\n\n >   PROGRAM SONLANDIRILDI   <");

    return 0;
}
double calcPI(int iterasyon) {  // program çalýþýnca pi sayisini hesaplar
    int i;
    double pi = 3, sign = 4.0;
    for (i = 1; i <= iterasyon; i++) {
        pi += (sign / ((2 * i) * (2 * i + 1) * (2 * i + 2)));
        sign = -sign;
    }
    return pi;
}
double calcE(int iterasyon) {  // program calisinca e sayisini hesaplar
    int i;
    double e = 0, payda = 1;
    for (i = 0; i < iterasyon; i++) {
        e += 1 / payda;
        payda *= (i + 1);
    }
    return e;
}
double floatMut(double x) {  // float ve double deðerlerin mutlak deðerini bulur
    return x < 0 ? (-x) : x;
}
double floatMod(double x, double mod) {  // float ve double deðerlerin modunu alýr
    while (x >= mod) {
        x -= mod;
    }
    while (x < 0.0) {
        x += mod;
    }
    return x;
}
void reset(double m[][MAX], int satir, int sutun) {  // matrisin tüm deðerlerini 0'a eþitler
    int i, j;
    for (i = 0; i < satir; i++) {
        for (j = 0; j < sutun; j++) {
            m[i][j] = 0;
        }
    }
}
void getEquations(double denk[][MAX], int *size) {  // Gauss Seidel yönteminin denklemlerini alýr
    int i, j;
    printf(" Yeni denklem takimi olustur:\n\n Denklem takiminin kac adet denklemden olustugunu girin: ");
    scanf("%d", size);
    printf("\n  (%d adet denklem takimi oldugu icin %d adet bilinmeyen oldugu varsayilacaktir.)", *size, *size);
    for (i = 0; i < (*size); i++) {
        printf("\n\n  %d. DENKLEM\n", i + 1);
        for (j = 0; j < (*size); j++) {
            printf("   X%d bilinmeyeninin katsayisi: ", j);
            scanf("%lf", &denk[i][j]);
        }
        printf("\n   > %d. denklemin sonucu = ", i + 1);
        scanf("%lf", &denk[i][*size]);
    }
}
void printEquations(double denk[][MAX], int size) {  // Gauss Seidel yönteminin denklemlerini ekrana yazdýrýr
    int i, j;
    printf("\n <!-- DENKLEM TAKIMI -->\n\n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (denk[i][j]) {
                printf("%+.1f*X%d", denk[i][j], j);
            } else {
                printf("       ");
            }
        }
        printf(" = %.3lf\n", denk[i][size]);
    }
    printf("\n");
}
void printEqRes(double eqRes[], int size) {  // Gauss Seidel yöntemi sonucunda bulunan kökleri ekrana yazdýrýr
    int i;
    printf(" Gauss-Seidal yontemi sonucu bilinmeyenlerin degerleri:\n\n");
    for (i = 0; i < size; i++) {
        printf("  X%d = %4.5lf\n", i, eqRes[i]);
    }
}
void sortMatrixDiagonally(double m[][MAX], int size) {  // Gauss Seidel yöntemi için denklem takýmlarýný köþegen bazýnda sýralar
    int i, j, k, tmp_j, flag;
    double max, t;
    for (i = 0; i < size - 1; i++) {
        max = floatMut(m[i][i]);
        flag = 0;
        for (j = i + 1; j < size; j++) {
            if (max < floatMut(m[j][i])) {
                tmp_j = j;
                max = m[j][i];
                flag = 1;
            }
        }
        if (flag == 1) {
            for (k = 0; k <= size; k++) {
                t = m[i][k];
                m[i][k] = m[tmp_j][k];
                m[tmp_j][k] = t;
            }
        }
    }
}
void getM(double m[][MAX], int *size) {  // kullanýcýdan matris alýr
    int i, j;

    do {
        printf(" Matrisin boyutunu girin: ");
        scanf("%d", size);
    } while (*size > 10);

    for (i = 0; i < (*size); i++) {
        printf("\n");
        for (j = 0; j < (*size); j++) {
            printf("  (%d,%d): ", i + 1, j + 1);
            scanf("%lf", &m[i][j]);
        }
    }
}
void printM(double m[][MAX], int rows, int cols) {  // ekrana matrisi yazdýrýr
    int i, j;
    for (i = 0; i < rows; i++) {
        printf("\n");
        for (j = 0; j < cols; j++) {
            printf("  %+3.4lf", m[i][j]);
        }
    }
    printf("\n");
}
/******************DENKLEM******************/
int create(double fonk[][MAX]) {  // kullanýcýdan fonksiyon türlerini ve deðerlerini alýr
    int secenek, derece, i;

    do {
        printf("\n Fonksiyon tipi sec\n 1-Polinom | 2-sinx | 3-cosx | 4-lnx | 5-logx | 6-b^x | 7-e^x | 8-Karekok\n (0 girerseniz denklem tamamlanir.)\n> ");
        scanf("%d", &secenek);

        if (secenek == 1) {  // POLÝNOM
            fonk[0][0] = 1;  // fonk matrisinde polinom bölümünün deðerini 1 yapar
            do {
                printf("  Polinomun derecesini girin: ");
                scanf("%d", &derece);
            } while (derece >= MAX);

            printf("  Belirtilen katsayilari girin:\n");
            for (i = derece; i >= 0; i--) {
                printf("   %d. derece: ", i);
                scanf("%lf", &fonk[1][i]);
            }
        } else if (secenek == 2) {  // SIN
            printf("  a*sinx:\n");
            printf("   > a = ");
            scanf("%lf", &fonk[0][1]);
        } else if (secenek == 3) {  // COS
            printf("  a*cosx:\n");
            printf("   > a = ");
            scanf("%lf", &fonk[0][2]);
        } else if (secenek == 4) {  // LNX
            printf("  a*lnx:\n");
            printf("   > a = ");
            scanf("%lf", &fonk[0][3]);
        } else if (secenek == 5) {  // LOG
            printf("  a*logb(x):\n");
            printf("   > a = ");
            scanf("%lf", &fonk[0][4]);
            printf("   > b = ");
            scanf("%lf", &fonk[0][5]);
            while (fonk[0][5] <= 0 || fonk[0][5] == 1) {
                printf(" !!! Girdiginiz b degeri tanim araligini bozmaktadir.\n   > Yeni b degeri: ");
                scanf("%lf", &fonk[2][7]);
            }
        } else if (secenek == 6) {  //ÜSTEL
            printf("  a*b^x:\n");
            printf("   > a = ");
            scanf("%lf", &fonk[0][6]);
            printf("   > b = ");
            scanf("%lf", &fonk[0][7]);
        } else if (secenek == 7) {  // EXP
            printf("  a*e^x:\n");
            printf("   > a = ");
            scanf("%lf", &fonk[0][8]);
        } else if (secenek == 8) {  // KAREKÖK
            printf("  a*karekok(x):\n");
            printf("   > a = ");
            scanf("%lf", &fonk[0][9]);
        }
    } while (secenek > 0);

    return derece;
}
double derivate(double fonk[][MAX], double der[][MAX], double x, int derece, double hata, int tur, double pi, double num_e) {  // alýnan fonksiyonun türev deðerini hesaplar
    double t = 0, tmp;
    int i;
    if (tur == 4) {        // Gerçek türev
        if (fonk[0][0]) {  // Polinom türevi
            for (i = 0; i < derece; i++) {
                der[1][i] = fonk[1][i + 1] * (i + 1);
            }
            t += calcPol(der, x, derece);
        }
        if (fonk[0][1])  // sin türevi
            t += fonk[0][1] * calcCos(x, pi, 0);

        if (fonk[0][2])  // cos türevi
            t += -fonk[0][2] * calcSin(x, pi, 0);

        if (fonk[0][3]) {  // ln türevi
            if (x)
                t += (fonk[0][3] / x);
            else
                printf("Tanim kumesi ihlal edildi(lnx)\n");
        }
        if (fonk[0][4]) {  // log türevi
            if (x)
                t += (fonk[0][4] / (x * calcLn(fonk[0][5])));
            else
                printf("Tanim kumesi ihlal edildi(log)\n");
        }
        if (fonk[0][6]) {  //Üstel türevi
            tmp = calcLn(fonk[0][7]);
            t += (fonk[0][6] * tmp * calcExp(x * tmp));
        }
        if (fonk[0][8])  // e^x türevi
            t += (fonk[0][8] * calcExp(x));

        if (fonk[0][9]) {  // karekök türevi
            if (x > 0)
                t += (fonk[0][9] / (2 * calcKok(x)));
            else
                printf("Tanim kumesi ihlal edildi(karekok)\n");
        }
        return t;
    }
    if (tur == 3) {  // Merkezi fark
        t = (calc(fonk, x, derece, pi, hata) - calc(fonk, x, derece, pi, -hata)) / (hata * 2);
        return t;
    }
    if (tur == 1) {  //Ýleri fark
        t = (calc(fonk, x, derece, pi, hata) - calc(fonk, x, derece, pi, 0)) / hata;
        return t;
    }
    if (tur == 2)  // Geri fark
        t = (calc(fonk, x, derece, pi, 0) - calc(fonk, x, derece, pi, -hata)) / hata;
    return t;
}
void gregoryNewtonMtr(double gregNewtMtr[][MAX], int n) {  // Gregory Newton yöntemi için kullanýcýdan x ve y deðerleri alýr
    int i, j = 2;
    n--;
    while (n > 0) {
        for (i = 0; i < n; i++) {
            gregNewtMtr[i][j] = gregNewtMtr[i + 1][j - 1] - gregNewtMtr[i][j - 1];
        }
        j++;
        n--;
    }
}
double gregoryNewton(double gregNewtMtr[][MAX], int n, double h, double x) {  // Gregory Newton yöntemi
    int i, j;
    double carpan = 1, t = 0;
    for (i = 0; i < n; i++) {
        t += carpan * gregNewtMtr[0][i + 1];
        carpan *= ((x - gregNewtMtr[i][0]) / (h * (i + 1)));
    }
    return t;
}
double trapez(double x0, double xn, double fonk[][MAX], int n, int derece, double pi) {  // Trapez yöntemi
    double toplam = 0, tmpFonk[2][MAX];
    int i, j;
    for (i = 0; i < MAX; i++) {
        tmpFonk[0][i] = fonk[0][i];
        tmpFonk[1][i] = fonk[1][i];
    }
    tmpFonk[0][1] = tmpFonk[0][2] = 0;

    toplam += tmpTrapez(x0, xn, tmpFonk, n, derece, pi);

    if (fonk[0][1] || fonk[0][2]) {
        for (i = 0; i < MAX; i++) {
            tmpFonk[0][i] = 0;
            tmpFonk[1][i] = 0;
        }
        tmpFonk[0][1] = fonk[0][1];
        tmpFonk[0][2] = fonk[0][2];

        toplam += tmpTrapez(x0, xn, tmpFonk, n, 0, pi) * pi / 180;
    }
    return toplam;
}
double tmpTrapez(double x0, double xn, double fonk[][MAX], int n, int derece, double pi) {  // Trapez yöntemi için iþlem yapar
    int i;
    double delta, toplam = 0;
    delta = (xn - x0) / n;
    for (i = 1; i < n; i++) {
        toplam += calc(fonk, x0 + i * delta, derece, pi, 0);
    }
    return delta * ((calc(fonk, x0, derece, pi, 0) + calc(fonk, xn, derece, pi, 0)) / 2 + toplam);
}
double simpson(double x0, double xn, double fonk[][MAX], int n, int derece, double pi, int tur) {  // Simpson 1/3 ve 3/8 yöntemleri
    int i, j;
    double toplam = 0, tmp = 0, h, alt, ust, tmpFonk[2][MAX];
    if (tur == 1) {  // SIMPSON 1/3
        for (i = 0; i < MAX; i++) {
            tmpFonk[0][i] = fonk[0][i];
            tmpFonk[1][i] = fonk[1][i];
        }
        tmpFonk[0][1] = tmpFonk[0][2] = 0;
        h = (xn - x0) / n;
        toplam += tmpSimpson1_3(x0, xn, n, h, tmpFonk, derece, pi);

        if (fonk[0][1] || fonk[0][2]) {
            for (i = 0; i < MAX; i++) {
                tmpFonk[0][i] = 0;
                tmpFonk[1][i] = 0;
            }
            tmpFonk[0][1] = fonk[0][1];
            tmpFonk[0][2] = fonk[0][2];

            toplam += tmpSimpson1_3(x0, xn, n, h, tmpFonk, 0, pi) * pi / 180;
        }
        return toplam;
    }
    h = (xn - x0) / n;  // SIMPSON 3/8
    for (i = 0; i < MAX; i++) {
        tmpFonk[0][i] = fonk[0][i];
        tmpFonk[1][i] = fonk[1][i];
    }
    tmpFonk[0][1] = tmpFonk[0][2] = 0;
    toplam = 0;
    toplam += tmpSimpson3_8(x0, xn, n, tmpFonk, derece, pi);

    if (fonk[0][1] || fonk[0][2]) {
        for (i = 0; i < MAX; i++) {
            tmpFonk[0][i] = 0;
            tmpFonk[1][i] = 0;
        }
        tmpFonk[0][1] = fonk[0][1];
        tmpFonk[0][2] = fonk[0][2];

        toplam += tmpSimpson3_8(x0, xn, n, tmpFonk, 0, pi) * pi / 180;
    }
    return toplam / 4;
}
double tmpSimpson1_3(double x0, double xn, int n, double h, double fonk[][MAX], int derece, double pi) {  // Simpson 1/3 yöntemi için iþlem yapar
    double toplam = 0, tmp = 0;
    int i;
    for (i = 1; i <= (n - 1); i += 2) {
        toplam += calc(fonk, x0 + i * h, derece, pi, 0);
    }
    toplam *= 4;
    for (i = 2; i <= (n - 2); i += 2) {
        tmp += calc(fonk, x0 + i * h, derece, pi, 0);
    }
    toplam += tmp * 2 + calc(fonk, x0, derece, pi, 0) + calc(fonk, xn, derece, pi, 0);
    toplam *= h / 3;
    return toplam;
}
double tmpSimpson3_8(double x0, double xn, int n, double fonk[][MAX], int derece, double pi) {  // Simpson 3/8 yöntemi için iþlem yapar
    double delta, alt, ust, toplam = 0, h;
    int i;
    h = (xn - x0) / n;
    for (i = 1; i <= n; i++) {
        alt = x0 + h * (i - 1);
        ust = x0 + h * i;
        delta = (ust - alt) / 3;
        toplam += (calc(fonk, alt, derece, pi, 0) + calc(fonk, ust, derece, pi, 0) + 3 * (calc(fonk, alt + delta, derece, pi, 0) + calc(fonk, alt + delta * 2, derece, pi, 0)));
    }
    return toplam * (xn - x0) / 8;
}
double calc(double fonk[][MAX], double x, int derece, double pi, double hata) {  // alýnan fonksiyonu verilen x deðerine göre hesaplar
    double t = 0;
    if (hata) {  // sin, cos için türev ve integrallerde sýkýntý çýktýðýndan hata payýný burada ekleme kararý aldým
        x += hata;
    }

    if (fonk[0][0]) {  // fonk[0][0] sadece 0 ve 1 deðerlerini alabilir
        t += calcPol(fonk, x, derece);
    }
    if (fonk[0][1]) {  // SIN
        t += fonk[0][1] * calcSin(x - hata, pi, hata);
    }
    if (fonk[0][2]) {  // COS
        t += fonk[0][2] * calcCos(x - hata, pi, hata);
    }
    if (fonk[0][3]) {  // LNX
        if (x > 0)
            t += fonk[0][3] * calcLn(x);
        else
            printf("Tanim kumesi ihlal edildi(lnx)\n");
    }
    if (fonk[0][4]) {  // LOG
        if (x > 0) {
            t += fonk[0][4] * calcLog(fonk[0][5], x);
        } else {
            printf("Tanim kumesi ihlal edildi(log)\n");
        }
    }
    if (fonk[0][6]) {  //ÜSTEL
        t += fonk[0][6] * calcUst(fonk[0][7], x);
    }
    if (fonk[0][8]) {  // EXP
        t += fonk[0][8] * calcExp(x);
    }
    if (fonk[0][9]) {  // KAREKÖK
        if (x >= 0) {
            t += fonk[0][9] * calcKok(x);
        } else {
            printf("Tanim kumesi ihlal edildi(karekok)\n");
        }
    }
    return t;
}
double calcPol(double m[][MAX], double x, int derece) {  // kullanýcýdan alýnan polinomu hesaplar
    int i;
    double tmp = x, toplam = m[1][0];
    for (i = 1; i <= derece; i++) {
        toplam += (tmp * m[1][i]);
        tmp *= x;
    }
    return toplam;
}
double calcSin(double x, double pi, double h) {  // kullanýcýdan alýnan sinüsü hesaplar
    int i;
    double tmp, toplam = 0, sign = 1, payda = 1;

    tmp = x = (floatMod(x, 360.0) * pi) / 180 + h;
    for (i = 0; i <= ITR; i++) {
        toplam += (sign * tmp) / payda;
        payda *= (2 * i + 2) * (2 * i + 3);
        tmp *= x * x;
        sign = -sign;
    }
    return toplam;
}
double calcCos(double x, double pi, double h) {  // kullanýcýdan alýnan cosinüsu hesaplar
    int i;
    double tmp = 1, toplam = 1, sign = -1, payda = 2;

    x = (floatMod(x, 360.0) * pi) / 180 + h;
    for (i = 1; i <= ITR; i++) {
        tmp *= x * x;
        toplam += (sign * tmp) / payda;
        payda *= (2 * i + 1) * (2 * i + 2);
        sign = -sign;
    }
    return toplam;
}
double calcLn(double x) {  // kullanýcýdan alýnan ln fonksiyonunu hesaplar
    double tmp, toplam = 0, sign = 1;
    int i;

    if (x <= 0) {
        printf("\n\n ! Ln'li ifadenin tanim araligi ihlal edildi !\n\n");
        return;
    }
    if (x == 1) {
        return 0;
    }
    if (x < 1) {
        tmp = --x;
        for (i = 1; i <= 250; i++) {
            toplam += ((tmp * sign) / i);
            tmp *= x;
            sign = -sign;
        }
        return toplam;
    }
    return -calcLn(1 / x);
}
double calcLog(double b, double x) {  // kullanýcýdan alýnan logaritmayý hesaplar
    return (calcLn(x) / calcLn(b));
}
double calcUst(double b, double x) {  // kullanýcýdan alýnan üstel ifadeyi hesaplar
    return (calcExp(x * calcLn(b)));
}
double calcExp(double x) {  // kullanýcýdan alýnan e^x ifadesini hesaplar
    int i;
    double tmp = 1, toplam = 1, payda = 1;

    for (i = 1; i <= ITR; i++) {
        tmp *= x;
        toplam += tmp / payda;
        payda *= (i + 1);
    }
    return toplam;
}
double calcKok(double x) {  // kullanýcýdan alýnan karekök ifadesini hesaplar
    if (x < 0) {
        printf("\n\n ! Karekoklu ifadenin tanim araligi ihlal edildi !\n\n");
        return;
    }
    if (x == 0) {
        return 0;
    }
    return calcExp(calcLn(x) / 2);
}

double bisection(double fonk[][MAX], double x1, double x2, double eps, int derece, double pi) {  // Bisection yöntemi
    double hata, two = 2, x3;
    int i = 0;

    do {
        x3 = (x1 + x2) / 2;
        if (calc(fonk, x1, derece, pi, 0) * calc(fonk, x3, derece, pi, 0) > 0) {
            x1 = x3;
        } else if (calc(fonk, x2, derece, pi, 0) * calc(fonk, x3, derece, pi, 0) > 0) {
            x2 = x3;
        }
        hata = (x2 - x1) / two;
        two *= 2;
        i++;
    } while (hata >= eps && calc(fonk, x1, derece, pi, 0) * calc(fonk, x2, derece, pi, 0) < 0);
    printItr("Bisection", i);

    return x3;
}
double interp(double fonk[][MAX], double x1, double x2, double eps, int derece, double pi) {  // Enterpolasyon yöntemi
    double x3, hata, two = 2, tmp, tmpx1, tmpx2, tmpx3;
    int i = 0;
    tmp = x2;

    do {
        x3 = (double)(x2 * calc(fonk, x1, derece, pi, 0) - x1 * calc(fonk, x2, derece, pi, 0)) / (calc(fonk, x1, derece, pi, 0) - calc(fonk, x2, derece, pi, 0));
        if (calc(fonk, x1, derece, pi, 0) * calc(fonk, x3, derece, pi, 0) < 0) {
            x2 = x3;
        } else if (calc(fonk, x1, derece, pi, 0) * calc(fonk, x3, derece, pi, 0) > 0) {
            x1 = x3;
        }
        i++;
        hata = (tmp - x3) / two;
        two *= 2;
    } while (hata > eps && calc(fonk, x1, derece, pi, 0) * calc(fonk, x2, derece, pi, 0) < 0);
    printItr("Interpolasyon", i);

    return x3;
}
double newtonRaphson(double fonk[][MAX], double der[][MAX], double x, double eps, int derece, double pi, double e) {  // Newton-Raphson yöntemi
    double fark;
    int i = 0;
    do {
        fark = calc(fonk, x, derece, pi, 0) / derivate(fonk, der, x, derece, 0, 4, pi, e);
        x -= fark;
    } while (floatMut(fark) > eps);

    return x;
}
void printResult(double fonk[][MAX], double x, int derece, double pi) {  // Bulunan kökü ekrana yazdýrýr
    printf("   Kok yaklasik olarak %.7lf\n   f(%.3lf) = %.7lf\n", x, x, calc(fonk, x, derece, pi, 0));
}
void printItr(char tur[], int i) {  // Bazý yöntemlerin kaç iterasyonda tamamlandýðýný ekrana yazdýrýr
    printf("\n   %s yontemi ile %d iterasyonda tamamlandi.\n", tur, i);
}
/******************MATRÝS******************/
void gaussElemination(double m[][MAX], int size) {  // Gauss Eleminasyon yöntemi
    int i, j, k, x = 0;
    double tmpM[MAX][MAX], tmp;

    for (i = 0; i < size; i++) {  // Matrisin saðýna birim matris ekler
        for (j = 0; j < size; j++) {
            tmpM[i][j] = m[i][j];
        }
        for (; j < (size * 2); j++) {
            if ((i + size) == j) {
                tmpM[i][j] = 1;
            } else {
                tmpM[i][j] = 0;
            }
        }
    }

    upperTriangular(tmpM, size, size * 2);
    lowerTriangular(tmpM, size, size * 2);
    diagonalValuesToOne(tmpM, size, size * 2);

    for (i = 0; i < size; i++) {  // Elde edilen ters matrisi, m matrisine aktarýr
        for (j = 0; j < size; j++) {
            m[i][j] = tmpM[i][j + size];
        }
    }
}
int gaussSeidel(double m[][MAX], double x[], int boyut, double hata, int getSorted) {  // Gauss Seidel yöntemi
    int i, j, flag = 1, divergenceCounter = 0;
    double tmp, prevX, deltaX[MAX] = {0};

    hata = floatMut(hata);
    if (getSorted)
        sortMatrixDiagonally(m, boyut);

    for (i = 0; i < boyut; i++)
        x[i] = 1.0;

    printf("\n(X: deger, D: delta)\n");  // köklerin ekrana yazdýrýlmasý için X ve delta(D) tablosunun ilk satýrý
    for (i = 0; i < boyut; i++)
        printf("   X%d        D%d     ", i, i);
    printf("\n");
    for (i = 0; i < boyut; i++)
        printf("--------  --------  ", i, i);
    printf("\n");

    while (flag) {
        for (i = 0; i < boyut; i++) {  // köklerin ekrana yazdýrýlmasý
            printf("%+.5lf  %+.5lf  ", x[i], deltaX[i]);
        }
        printf("\n");
        for (i = 0; i < boyut; i++) {
            prevX = x[i];
            x[i] = m[i][boyut];
            for (j = 0; j < boyut; j++) {
                if (j != i) {
                    x[i] -= (m[i][j] * x[j]);
                }
            }
            x[i] /= m[i][i];
            tmp = deltaX[i];
            deltaX[i] = floatMut(prevX - x[i]);
            if (deltaX[i] / 3 > tmp) {
                divergenceCounter++;
            }
        }
        i = 0;
        while (i < boyut && deltaX[i] <= hata) {  // DURMA KOÞULU
            i++;
        }
        if (i == boyut) {
            return 0;
        }
        if (divergenceCounter / boyut > 20) {
            return -1;
        }
        flag = 1;
    }
}
void upperTriangular(double m[][MAX], int rows, int cols) {  // Aldýðý matrisi üst üçgen matris formatýna getirir
    int i, j, k;
    double tmp;
    for (i = 0; i < rows; i++) {
        for (k = i + 1; k < rows; k++) {
            tmp = m[k][i] / m[i][i];
            for (j = 0; j < cols; j++) {
                m[k][j] -= (m[i][j] * tmp);
            }
        }
    }
}
void lowerTriangular(double m[][MAX], int rows, int cols) {  // Aldýðý matrisi alt üçgen matris formatýna getirir
    int i, j, k;
    double tmp;
    for (i = rows - 1; i > 0; i--) {
        for (k = i - 1; k >= 0; k--) {
            tmp = m[k][i] / m[i][i];
            for (j = 0; j < cols; j++) {
                m[k][j] -= (m[i][j] * tmp);
            }
        }
    }
}
void diagonalValuesToOne(double m[][MAX], int rows, int cols) {  // Aldýðý matrisin köþegen elemanlarýný 1'e eþitleyecek iþlemler yapar
    int i, j;
    double tmp;
    for (i = 0; i < rows; i++) {
        tmp = m[i][i];
        for (j = 0; j < cols; j++) {
            m[i][j] /= tmp;
        }
    }
}
