#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Rastgelelik için program baþýnda seed ayarý[cite: 1]
    srand(time(NULL));

    // Durum Deðiþkenleri[cite: 3]
    int saglik = 100, enerji = 100, oksijen = 100;
    int su = 0, yedekParca = 0, modulHasari = 0;
    int kilitMuhurlu = 0; // 0: Açýk, 1: Mühürlü[cite: 3]
    int gun = 1, tur = 0;
    char zorluk, komut;
    int zorlukSecildi = 0;
    int firtinaTuru = 3;

    printf("====================================================\n");
    printf("      MARS KOLONISI YASAM DESTEK SIMULATORU         \n");
    printf("====================================================\n");

    // 1. ZORLUK SEVÝYESÝ SEÇÝMÝ (SWITCH-CASE ve Geçersiz Giriþ Döngüsü)[cite: 1, 2]
    do {
        printf("\nZorluk Seviyesi Secin (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorluk);

        switch (zorluk) {
            case 'k':
            case 'K':
                su = 60;
                yedekParca = 5;
                modulHasari = 10;
                firtinaTuru = 3;
                zorlukSecildi = 1;
                printf(">> KOLAY seviye secildi.\n");
                break;

            case 'n':
            case 'N':
                su = 40;
                yedekParca = 3;
                modulHasari = 25;
                firtinaTuru = 5;
                zorlukSecildi = 1;
                printf(">> NORMAL seviye secildi.\n");
                break;

            case 'z':
            case 'Z':
                su = 25;
                yedekParca = 1;
                modulHasari = 45;
                firtinaTuru = 7;
                zorlukSecildi = 1;
                printf(">> ZOR seviye secildi.\n");
                break;

            default:
                printf("[HATA] Gecersiz zorluk seviyesi! Lutfen K, N veya Z girin.\n");
                break;
        }
    } while (!zorlukSecildi);

    // 2. ANA KOMUT DÝNLEME DÖNGÜSÜ (DO-WHILE)[cite: 1]
    do {
        printf("\n----------------------------------------------------\n");
        printf("GUN: %d/15 | TUR: %d | Kilit: %s\n", gun, tur, kilitMuhurlu ? "MUHURLU" : "ACIK");
        printf("Saglik: %d | Enerji: %d | Oksijen: %d | Su: %d | Parca: %d | Hasar: %d\n",
               saglik, enerji, oksijen, su, yedekParca, modulHasari);
        printf("Komutlar: [G]esif, [O]ksijen, [T]amir, [D]urum, [U]yu, [K]um Firtinasi, [H]ava Kilidi, [Q]Cikis\n");
        printf("Komutunuz: ");
        scanf(" %c", &komut);

        int zar, esik;

        // Fall-through ile büyük/küçük harf duyarsýz SWITCH-CASE (Süslü parantezlerle kapsamlar güvene alýndý)
        switch (komut) {
            // ================= KEÞÝF GÖREVÝ (G) =================
            case 'g':
            case 'G': {
                if (enerji < 15 || oksijen < 10) {
                    printf("[YETERSIZ KAYNAK] Kesif icin en az 15 Enerji ve 10 Oksijen gerekiyor!\n");
                    break;
                }
                enerji -= 15;
                oksijen -= 10;

                zar = rand() % 100;
                // Enerji ve oksijen durumuna göre baþarý eþiði belirleme[cite: 2]
                if (enerji > 40 && oksijen > 30) {
                    esik = 65;
                } else {
                    esik = 35;
                }

                printf("Zar: %d / Esik: %d -> ", zar, esik);
                if (zar < esik) {
                    printf("BASARILI\n");
                    if (zar % 2 == 0) {
                        su += 15;
                        printf(">> Kesifte buz kutlesi bulundu! +15 Su eklendi.\n");
                    } else {
                        yedekParca += 1;
                        printf(">> Eski uydu enkazina ulasildi! +1 Yedek Parca eklendi.\n");
                    }
                } else {
                    printf("BASARISIZ\n");
                    printf(">> Kesiften eli bos donuldu.\n");
                }

                // Yaralanma kontrolü[cite: 2]
                if (zar < 10 || modulHasari > 70) {
                    saglik -= 10;
                    printf("[TEHLIKE] Kesif sirasinda yaralandiniz! -10 Saglik.\n");
                }
                tur++;
                break;
            }

            // ================= OKSÝJEN ÜRETÝMÝ (O) =================
            case 'o':
            case 'O': {
                if (enerji < 10) {
                    printf("[YETERSIZ KAYNAK] Oksijen uretimi icin en az 10 Enerji gerekiyor!\n");
                    break;
                }
                if (su < 2) {
                    printf("[YETERSIZ KAYNAK] Oksijen uretmek icin en az 2 birim su gerekiyor!\n");
                    break;
                }

                int harcananSu;
                printf("Kullanilacak su miktarini girin (Mevcut Su: %d): ", su);
                scanf("%d", &harcananSu);

                if (harcananSu > su || harcananSu < 2) {
                    printf("[HATA] Gecersiz miktar! En az 2, en fazla %d birim su girebilirsiniz.\n", su);
                    break;
                }

                enerji -= 10;
                // Mod operatörü (%) ile tek/çift kontrolü: tekse 1 birim artýk kalýr[cite: 2]
                int artikSu = harcananSu % 2;
                int islenenSu = harcananSu - artikSu;
                int uretilenOksijen = (islenenSu / 2) * 3;

                su -= islenenSu;
                oksijen += uretilenOksijen;

                if (artikSu == 1) {
                    printf("[BILGI] Girilen miktar tek sayi oldugu icin 1 birim su depoda artik kaldi.\n");
                }
                printf(">> %d birim su islenerek +%d Oksijen uretildi.\n", islenenSu, uretilenOksijen);
                tur++;
                break;
            }

            // ================= TAMÝR (T) =================
            case 't':
            case 'T': {
                if (enerji < 10) {
                    printf("[YETERSIZ KAYNAK] Tamir icin en az 10 Enerji gerekiyor!\n");
                    break;
                }
                if (yedekParca <= 0) {
                    printf("[YETERSIZ KAYNAK] Yedek parcaniz yok! Tamir yapilamaz.\n");
                    break;
                }
                if (modulHasari == 0) {
                    printf("[BILGI] Modul hasari zaten 0, tamire gerek yok.\n");
                    break;
                }

                // IF - ELSE IF - ELSE kademeli hasar kontrolü[cite: 2]
                if (modulHasari <= 30) {
                    if (yedekParca >= 1) {
                        yedekParca -= 1;
                        enerji -= 10;
                        modulHasari -= 15;
                        printf(">> Hafif hasar onarildi (-15 Hasar, -1 Yedek Parca).\n");
                    }
                } else if (modulHasari <= 70) {
                    if (yedekParca >= 2) {
                        yedekParca -= 2;
                        enerji -= 15;
                        modulHasari -= 30;
                        printf(">> Orta seviye hasar onarildi (-30 Hasar, -2 Yedek Parca).\n");
                    } else {
                        printf("[YETERSIZ KAYNAK] Orta seviye hasar icin 2 yedek parca gerekiyor!\n");
                        break;
                    }
                } else {
                    if (yedekParca >= 3) {
                        yedekParca -= 3;
                        enerji -= 20;
                        modulHasari -= 45;
                        printf(">> Agir hasar onarildi (-45 Hasar, -3 Yedek Parca).\n");
                    } else {
                        printf("[YETERSIZ KAYNAK] Agir hasar icin 3 yedek parca gerekiyor!\n");
                        break;
                    }
                }
                tur++;
                break;
            }

            // ================= DURUM RAPORU (D) =================
            case 'd':
            case 'D': {
                printf("\n=== DETAYLI SISTEM DURUM RAPORU ===\n");
                if (oksijen < 25) printf("[KRITIK UYARI] Oksijen seviyesi kritik (< 25)!\n");
                if (saglik < 30)  printf("[KRITIK UYARI] Saglik durumu kritik (< 30)!\n");
                if (enerji < 20)  printf("[KRITIK UYARI] Enerji seviyesi cok dusuk (< 20)!\n");
                if (modulHasari > 70) printf("[KRITIK UYARI] Modul hasari kritik seviyede (> 70)!\n");

                if (oksijen >= 25 && saglik >= 30 && enerji >= 20 && modulHasari <= 70) {
                    printf(">> TUM SISTEMLER NORMAL <<\n");
                }
                printf("====================================\n");
                // D komutu tur sayacýný artýrmaz[cite: 2]
                break;
            }

            // ================= DÝNLEN / UYU (U) =================
            case 'u':
            case 'U': {
                enerji += 25;
                oksijen -= 8;
                printf(">> Istasyonda dinlenildi (+25 Enerji, -8 Oksijen).\n");

                // Ýç içe IF: Oksijen 20'nin altýndaysa saðlýk artmaz, azalýr[cite: 2]
                if (oksijen < 20) {
                    saglik -= 10;
                    printf("[UYARI] Dusuk oksijen nedeniyle uyurken zehirlendiniz! -10 Saglik.\n");
                } else {
                    if (saglik < 100) {
                        saglik += 10;
                        printf(">> Dinlenme sayesinde +10 Saglik kazanildi.\n");
                    }
                }
                tur++;
                break;
            }

            // ================= KUM FIRTINASI (K - FOR DÖNGÜSÜ) =================
            case 'k':
            case 'K': {
                if (enerji < 10) {
                    printf("[YETERSIZ KAYNAK] Firtina onlemleri icin en az 10 Enerji gerekiyor!\n");
                    break;
                }
                enerji -= 10;
                printf("\n*** KUM FIRTINASI BASLADI (%d Tur Surecek) ***\n", firtinaTuru);

                int hasarAlinanTur = 0, topSaglikKaybi = 0, topOksijenKaybi = 0;
                int i;

                for (i = 1; i <= firtinaTuru; i++) {
                    zar = rand() % 100;
                    esik = 50;
                    int carpan = (i % 2 == 0) ? 2 : 1; // Çift turlarda mod (%) ile hasar 2 katýna çýkar[cite: 2]

                    printf("Firtina Tur %d (Carpan: %dx) | Zar: %d / Esik: %d -> \n", i, carpan, zar, esik);

                    if (zar < 30) {
                        // Oksijen sýzýntýsý olayý
                        if (kilitMuhurlu == 1) {
                            printf("Hava kilidi muhurlu oldugu icin oksijen sizintisi engellendi! (Atlandi)\n");
                            continue; // continue ile sýzýntý atlanýr[cite: 2]
                        }
                        int kayip = 6 * carpan;
                        oksijen -= kayip;
                        topOksijenKaybi += kayip;
                        hasarAlinanTur++;
                        printf("OKSIJEN SIZINTISI! -%d Oksijen\n", kayip);
                    } else if (zar < 60) {
                        int hasar = 8 * carpan;
                        modulHasari += hasar;
                        hasarAlinanTur++;
                        printf("MODUL DARBE ALDI! +%d Hasar\n", hasar);
                    } else if (zar < 80) {
                        int canKaybi = 5 * carpan;
                        saglik -= canKaybi;
                        topSaglikKaybi += canKaybi;
                        hasarAlinanTur++;
                        printf("YARALANMA! -%d Saglik\n", canKaybi);
                    } else {
                        printf("KORUNULDU (Hasar yok)\n");
                    }

                    // Saðlýk veya oksijen 0'a düþerse break ile döngü derhal sonlandýrýlýr[cite: 2]
                    if (saglik <= 0 || oksijen <= 0) {
                        if (saglik < 0) saglik = 0;
                        if (oksijen < 0) oksijen = 0;
                        printf("[KRITIK] Firtina sirasinda yasam destegi coktu!\n");
                        break;
                    }
                }

                printf("--- Firtina Ozeti ---\n");
                printf("Hasar Alinan Tur: %d | Kaybedilen Saglik: %d | Kaybedilen Oksijen: %d\n",
                       hasarAlinanTur, topSaglikKaybi, topOksijenKaybi);
                tur++;
                break;
            }

            // ================= HAVA KÝLÝDÝ ÞÝFRESÝ (H - DO-WHILE DÖNGÜSÜ) =================
            case 'h':
            case 'H': {
                if (kilitMuhurlu == 1) {
                    printf("[BILGI] Hava kilidi zaten muhurlu durumda!\n");
                    break;
                }
                if (enerji < 15) {
                    printf("[YETERSIZ KAYNAK] Hava kilidi sistemi icin en az 15 Enerji gerekiyor!\n");
                    break;
                }

                // Aritmetik olarak güne baðlý þifre üretimi[cite: 3]
                char dogruSifre = 'A' + (gun % 26);
                char tahmin;
                int deneme = 0;

                printf("\n=== HAVA KILIDI GUVENLIK SISTEMI ===\n");
                printf("Ipucu: Sifre, alfabede 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun);

                // Hem yanlýþ tahmin hem deneme hakkýný tek ifadede kontrol eden DO-WHILE[cite: 3]
                do {
                    printf("Sifreyi girin (Kalan Hak: %d): ", 3 - deneme);
                    scanf(" %c", &tahmin);

                    // Küçük harf giriþini büyük harfe çevirme (ASCII aritmetiði)
                    if (tahmin >= 'a' && tahmin <= 'z') {
                        tahmin = tahmin - ('a' - 'A');
                    }

                    deneme++;

                    if (tahmin != dogruSifre) {
                        enerji -= 5;
                        if (tahmin < dogruSifre) {
                            printf("[YANLIS] Girdiginiz harf sifreden once! (Ipucu: Ileri git) [-5 Enerji]\n");
                        } else {
                            printf("[YANLIS] Girdiginiz harf sifreden sonra! (Ipucu: Geri git) [-5 Enerji]\n");
                        }
                    }
                } while (tahmin != dogruSifre && deneme < 3);

                if (tahmin == dogruSifre) {
                    kilitMuhurlu = 1;
                    printf(">> BASARILI! Hava kilidi basariyla muhurlendi.\n");
                } else {
                    modulHasari += 20;
                    printf("[BASARISIZ] 3 deneme hakkiniz doldu! Guvenlik kilitlendi ve +20 Modul Hasari alindi.\n");
                }
                tur++;
                break;
            }

            // ================= ÇIKIÞ (Q) =================
            case 'q':
            case 'Q': {
                printf(">> Kullanici istegiyle simulasyondan cikiliyor...\n");
                break;
            }

            // ================= TANIMSIZ KOMUT =================
            default: {
                printf("[UYARI] Tanimsiz komut girdiniz! Bu islem tur harcamadi.\n");
                break;
            }
        }

        // Geçerli bir tur harcayan komutlardan sonra ZAMAN AKIÞI kontrolü[cite: 3]
        if (komut != 'd' && komut != 'D' && komut != 'q' && komut != 'Q' &&
           (komut == 'g' || komut == 'G' || komut == 'o' || komut == 'O' ||
            komut == 't' || komut == 'T' || komut == 'u' || komut == 'U' ||
            komut == 'k' || komut == 'K' || komut == 'h' || komut == 'H')) {

            if (tur > 0 && tur % 3 == 0) {
                gun++;
                oksijen -= 8;
                printf("\n[GUN SONU] Yeni gune gecildi (Gun %d)! -8 Oksijen tuketildi.\n", gun);
                if (modulHasari > 70) {
                    saglik -= 5;
                    printf("[HASAR CEZASI] Modul hasari 70 uzerinde oldugu icin -5 Saglik kaybedildi.\n");
                }
            }
        }

        // SINIRLANDIRMA KONTROLLERI (0 - 100 Aralýðý)[cite: 2]
        if (saglik < 0) saglik = 0;
        if (saglik > 100) saglik = 100;
        if (enerji < 0) enerji = 0;
        if (enerji > 100) enerji = 100;
        if (oksijen < 0) oksijen = 0;
        if (oksijen > 100) oksijen = 100;
        if (modulHasari < 0) modulHasari = 0;
        if (modulHasari > 100) modulHasari = 100;

        // OYUN SONU KONTROLLERI[cite: 3]
        if (saglik == 0 || oksijen == 0) {
            printf("\n[OYUN KAYBEDILDI] Yasam fonksiyonlariniz durdu!\n");
            break;
        }
        if (gun > 15) {
            printf("\n[OYUN KAZANILDI] 15 gun hayatta kaldiniz ve kurtarma ekibi ulasti!\n");
            break;
        }

    } while (komut != 'q' && komut != 'Q');

    // SONUÇ RAPORU VE PUAN HESAPLAMA[cite: 3]
    int puan = (gun * 100) + saglik + oksijen - modulHasari;
    printf("\n====================================================\n");
    printf("                 SIMULASYON SONUCU                  \n");
    printf("====================================================\n");
    printf("Hayatta Kalinan Gun : %d\n", (gun > 15) ? 15 : gun);
    printf("Toplam Tur Sayisi   : %d\n", tur);
    printf("Son Saglik          : %d\n", saglik);
    printf("Son Enerji          : %d\n", enerji);
    printf("Son Oksijen         : %d\n", oksijen);
    printf("Son Modul Hasari    : %d\n", modulHasari);
    printf("TOPLAM PUAN         : %d\n", puan);
    printf("====================================================\n");

    return 0;
}
