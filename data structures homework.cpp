#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <functional>
#include <iomanip>

using namespace std;

struct Nokta {
    int satir;
    int sutun;
};

/*
 Blok sayısını bulmak için fonksiyon.
veri iki boyutlu vektör.
 satir sayısı.
sutun sayısı.
*/
int blokSayaci(vector<vector<char>>& veri, int satir, int sutun) {

    // Vektörün boyutlarını belirle.
    int satirSayisi = veri.size();
    int sutunSayisi = veri[0].size();

    // Boş noktalar için kontrol yap.
    if (satir < 0 || satir >= satirSayisi || sutun < 0 || sutun >= sutunSayisi || veri[satir][sutun] == ' ')
        return 0;

    veri[satir][sutun] = ' ';
    int toplam = 1;

    // Komşu hücreler için rekürsif arama yap.
    toplam += blokSayaci(veri, satir + 1, sutun);
    toplam += blokSayaci(veri, satir - 1, sutun);
    toplam += blokSayaci(veri, satir, sutun + 1);
    toplam += blokSayaci(veri, satir, sutun - 1);

    // Bulunan blok sayısını döndür.
    return toplam;
}

/**
* Piksel sayısını bulmak için fonksiyon.
 veri "x" karakterlerini içeren vektör.
satir sayısı.
sutun sayısı.
koordinatlar piksellerin saklanacağı vektör.
*/
int pikselSayaci(vector<vector<char>>& veri, int satir, int sutun, vector<Nokta>& koordinatlar) {

    // Piksel sayısı başlangıcı.
    int sayac = 0;

    // Piksel olup olmadığını kontrol et.
    if (satir < 0 || satir >= veri.size() || sutun < 0 || sutun >= veri[satir].size() || veri[satir][sutun] != 'x')
        return 0;

    veri[satir][sutun] = ' ';
    sayac = 1;

    // Bulunan pikselin koordinatlarını kaydet.
    Nokta nokta;
    nokta.satir = satir;
    nokta.sutun = sutun;
    koordinatlar.push_back(nokta);

    // Komşu hücreler için rekürsif kontrol yap.
    sayac += pikselSayaci(veri, satir + 1, sutun, koordinatlar);
    sayac += pikselSayaci(veri, satir - 1, sutun, koordinatlar);
    sayac += pikselSayaci(veri, satir, sutun + 1, koordinatlar);
    sayac += pikselSayaci(veri, satir, sutun - 1, koordinatlar);

    // Piksel sayısını döndür.
    return sayac;
}

/**
* Satır kütle merkezi hesaplama fonksiyonu.
* @param noktalar koordinatların saklandığı vektör.
*/
double satirKutleMerkezi(vector<Nokta>& noktalar) {

    // Koordinatlar toplamı başlangıcı.
    int toplam = 0;

    // Her pikselin satır koordinatlarını topla.
    for (const auto& nokta : noktalar) {
        toplam += nokta.satir;
    }

    // Toplamı piksel sayısına böl ve kütle merkezini döndür.
    return static_cast<double>(toplam) / noktalar.size();
}

/**
* Sütun kütle merkezi hesaplama fonksiyonu.
* @param noktalar koordinatların saklandığı vektör.
*/
double sutunKutleMerkezi(vector<Nokta>& noktalar) {

    // Koordinatlar toplamı başlangıcı.
    int toplam = 0;

    // Her pikselin sütun koordinatlarını topla.
    for (const auto& nokta : noktalar) {
        toplam += nokta.sutun;
    }

    // Toplamı piksel sayısına böl ve kütle merkezini döndür.
    return static_cast<double>(toplam) / noktalar.size();
}

// dosya adını kullanıcıdan iste
string dosyaIsmiAl() {
    string dosyaIsmi;
    cout << "Dosya adini girin (uzantisi ile birlikte): ";
    cin >> dosyaIsmi;
    return dosyaIsmi;
}

//üst alt yatay sınır çizmek için fonksiyon
void yataySinirCiz(int sutunSayisi) {
    for (int i = 0; i < sutunSayisi; i++) {
        cout << "-";
    }
}

//koordinat sayılarını belirlemek için fonksiyon

void koordinatYazici(int n) {
    int sayac = 0;

    while (sayac < n) {
        for (int i = 0; i <= 9 && sayac < n; i++) {
            cout << i;
            sayac++;
        }
    }
}

// Ekrana dosyayı yazdır
void dosyaYazdir(string dosyaAdi) {

    // Başlangıç için değişkenler.
    int satirIndex = -1;
    bool ilkSatir = true;
    string satir;

    // Dosyayı açmak 
    fstream dosya(dosyaAdi);

    // dosyayı yazdır
    while (getline(dosya, satir)) {

        if (ilkSatir) {
            cout << endl;
            ilkSatir = false;
        }
        else {
            // Koordinat ve sınır çizgilerini ekle.
            cout << satirIndex << "|" << satir << "|" << satirIndex << endl;
        }

        satirIndex++;

        if (satirIndex == 10) {
            satirIndex = 0;
        }
    }
}

//üst sınırı çizdirmek için gerekli fonksiyon
void ustSinirCiz(int sutunSayisi) {

    cout << "  ";
    koordinatYazici(sutunSayisi);
    cout << endl;

    cout << " +";
    yataySinirCiz(sutunSayisi);
    cout << "+";
}

//üst sınırı çizdirmek için gerekli fonksiyon
void altSinirCiz(int sutunSayisi) {
    cout << " +";
    yataySinirCiz(sutunSayisi);
    cout << "+" << endl;

    cout << "  ";
    koordinatYazici(sutunSayisi);
    cout << endl << endl;
}

// alınan boyutların uyuşmazlığını kontrol edip hata varsa ekrana yazdıran fonksiyon
int hataKontrol(int satir, int sutun, vector<vector<char>> dizi) {
    if (satir <= 0 || sutun <= 0 || satir != dizi.size() || sutun != dizi[0].size()) {
        cerr << "Hata: Verilen boyutlar ile dizi boyutlari uyusmuyor." << endl;
        return 1;
    }
    return 0;
}

int main() {

    int satirSayisi;
    int sutunSayisi;
    string icerik;
    vector<vector<char>> girdiDizisi;
    // Dosya adını al 
    string dosyaAdi = dosyaIsmiAl();
    // Dosyayı aç
    fstream dosya(dosyaAdi);

    if (dosya.is_open()) { // Dosya başarılı bir şekilde açıldıysa

        // Satır  ve sütun sayısını oku
        dosya >> satirSayisi;
        dosya >> sutunSayisi;
        // Satır ve sütun sayısını yazdır
        cout << "Satir: " << satirSayisi << endl;
        cout << "Sutun: " << sutunSayisi << endl << endl;

        getline(dosya, icerik);
        // Dosyadaki her satırı oku ve girdiDizisi'ne ekle
        while (getline(dosya, icerik)) {
            vector<char> satir(icerik.begin(), icerik.end());
            girdiDizisi.push_back(satir);
        }

        dosya.close();
    }
    // Dosya açılamadıysa
    else {
        cerr << "Dosya acilmiyor ya da bozuk." << endl; // Hata mesajı yazdır
        return 1; // Programı hata koduyla sonlandır
    }
    // KMK : kütle merkezi koordinatları
    ustSinirCiz(sutunSayisi);
    dosyaYazdir(dosyaAdi);
    altSinirCiz(sutunSayisi);

    if (hataKontrol(satirSayisi, sutunSayisi, girdiDizisi) == 1) {
        return 1;
    }
    // Başlık satırını yazdır
    cout << setw(10) << "Blok" << setw(10) << "Pikseller" << setw(10) << "Satir kütle merkezi" << setw(10) << "Sutun kütle merkezi" << endl;
    // İşlem yapılacak blok sayısını tutacak değişken
    int blokSayisi = 0;
    // Satır ve sütunlar arasında döngü
    for (int i = 0; i < satirSayisi; ++i) {

        for (int j = 0; j < sutunSayisi; ++j) {
            // 'x' karakteri bulunan her piksel için işlem yap
            if (girdiDizisi[i][j] == 'x') {
                // Pikselin bulunduğu bloktaki noktaları tutacak vektör
                vector<Nokta> noktalar;
                // Piksel sayısını ve noktaları al
                int bloktakiPikselSayisi = pikselSayaci(girdiDizisi, i, j, noktalar);
                // Blok sayısını ve piksel sayısını yazdır
                cout << setw(10) << ++blokSayisi << setw(8) << bloktakiPikselSayisi;
                // Satır kütle merkezi hesapla
                double satirKMK = satirKutleMerkezi(noktalar);
                // Satır kütle merkezini kontrol et ve yazdır
                if (satirKMK >= 0) {
                    cout << setw(10) << setprecision(4) << satirKMK;
                }
                else { // Hesaplanamadıysa mesaj yazdır
                    cout << "Satir kütle merkezi hesaplanamadi." << endl;
                }
                // Sütun kütle merkezi hesapla
                double sutunKMK = sutunKutleMerkezi(noktalar);
                // Sütun kütle merkezini kontrol et ve yazdır

                if (sutunKMK >= 0) {
                    cout << setw(10) << setprecision(4) << sutunKMK << endl;
                }
                else {
                    // Hesaplanamadıysa mesaj yazdır
                    cout << "Sutun kütle merkezi hesaplanamadi." << endl;
                }
            }
        }
    }
    return 0;// Programı başarıyla sonlandır
}