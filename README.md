Mars Kolonisi Yaşam Destek Simülatörü

C programlama dilinin temel yapıları (koşullu ifadeler, döngüler, aritmetik ve mantıksal operatörler) kullanılarak geliştirilmiş karakter tabanlı bir hayatta kalma simülasyon oyunudur.

Proje Hakkında

Oyuncu, Mars yüzeyindeki küçük bir araştırma istasyonunda tek başına mahsur kalan bir mühendisi yönetir. Temel amaç, kurtarma ekibi ulaşana kadar 15 gün boyunca istasyonun kritik yaşam destek kaynaklarını (sağlık, enerji, oksijen, su, yedek parça ve modül hasarı) dengede tutarak hayatta kalmaktır.

Temel Özellikler ve Oyun Mekanikleri

Zorluk Seviyeleri: Kolay (K), Normal (N) ve Zor (Z) olmak üzere üç farklı zorluk seviyesi başlangıç kaynaklarını ve kum fırtınası sürelerini belirler.

Büyük/Küçük Harf Duyarsız Komut Sistemi: switch-case (fall-through) yapısı ile tüm komutlar hem büyük hem küçük harf olarak kabul edilir. Geçersiz komutlar tur/süre harcamaz.

Zaman ve Gün Döngüsü: Geçerli her 3 turda bir (tur % 3 == 0) yeni bir güne geçilir. Gün değişiminde oksijen tüketimi gerçekleşir ve yüksek modül hasarı durumunda sağlık kaybı yaşanır.

Rastgele Olay Sistemi: srand(time(NULL)) ve rand() % 100 kullanılarak üretilen zar değerleri, belirlenen eşiklerle karşılaştırılır ve sonucu ekrana yazdırılır.

Komut Listesi
Komut                             İşlev                                                                                              Açıklama 
G                              Keşif Görevi                                                                   Enerji ve oksijen harcanarak dışarıda su veya yedek parça aranır. 
                                                                                                Düşük zar veya yüksek hasar durumunda yaralanma riski vardır.
                            
O                              Oksijen Üretimi                                                     Mevcut sudan oksijen üretilir (2 birim su = 3 birim oksijen).
                                                                                                   Mod (%) operatörü ile tek sayılı su girişlerinde 1 birim depoda kalır.
  
T                                Tamir                                                           Yedek parça ve enerji kullanılarak modül hasarı onarılır.
                                                                                                 Hasar seviyesi (hafif, orta, ağır) kademeli olarak değerlendirilir.
                                                              
D                             Durum Raporu                                                        Sistemdeki kritik seviyeleri raporlar. Tüm değerler güvenli aralıktaysa genel sistem onayı verir. 
                                                                                                  (Tur harcamaz)
    
U                             Dinlen / Uyu                                                       Enerji ve sağlık yeniler. Oksijen seviyesi kritik eşiğin (< 20) altındaysa sağlık artışı yerine sağlık kaybı yaşanır.

K                            Kum Fırtınası                                                       for döngüsü ile fırtına simüle edilir. Çift turlarda hasar iki katına çıkar; hava kilidi mühürlüyse oksijen sızıntısı engellenir.

H                          Hava Kilidi Şifresi                                                   do-while döngüsü ve en fazla 3 deneme hakkı ile güne bağlı aritmetik şifre çözülerek hava kilidi mühürlenir.

Q                            Çıkış                                                               Simülasyonu sonlandırır ve genel sonuç/puan raporunu ekrana yazdırır.

Puanlama Formülü

Simülasyon sonunda (kazanma, kaybetme veya çıkış durumunda) elde edilen puan aşağıdaki formülle hesaplanır:
Puan=(Hayatta Kalınan Gün * 100) + Sağlık + Oksijen - Modül Hasarı
Kurulum ve Çalıştırma

Projeyi yerel bilgisayarınızda derlemek ve çalıştırmak için herhangi bir standart C derleyicisi (GCC, Dev-C++, Code::Blocks vb.) kullanabilirsiniz:

gcc main.c -o mars_simulator
./mars_simulator


Kullanılan C Yapıları

Karar Yapıları: if, else if, else, iç içe if, switch-case (fall-through)

Döngüler: do-while (ana oyun döngüsü, zorluk doğrulama ve şifre mekanizması), for (kum fırtınası simülasyonu)

Kontrol İfadeleri: break ve continue

Operatörler: Aritmetik (+, -, *, /, %), Mantıksal (&&, ||, !) ve İlişkisel operatörler
