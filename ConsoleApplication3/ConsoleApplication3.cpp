// ConsoleApplication3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
using namespace std;

struct pole {
public:
    int wartosc;
    bool odkrycie;

};
pole plansza[10][10];
bool generuj_plansze()
{
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 10; y++)
        {
            plansza[x][y].wartosc = 0;
            plansza[x][y].odkrycie = false;
        }
    return true;
}
void losuj_pozycje()
{
    time_t t;
    int poz_x, poz_y;
    int ilosc = 10;

    srand((unsigned)time(&t));

    while (ilosc > 0)
    {
        poz_x = rand() % 10;
        poz_y = rand() % 10;

        if (plansza[poz_x][poz_y].wartosc != 9)
        {
            ustaw_mine(poz_x, poz_y);
            ilosc--;
        }
    }
}
bool ustaw_mine(int poz_x, int poz_y)
{
    if (plansza[poz_x][poz_y].wartosc != 9)
    {
        plansza[poz_x][poz_y].wartosc = 9; //ustaw mine
        for (int k = -1; k < 2; k++)
            for (int l = -1; l < 2; l++)
            {
                if ((poz_x + l) < 0 || (poz_x + k) < 0) continue; //wyjdz bo krawedz
                if ((poz_x + l) > 9 || (poz_y + k) > 9) continue; //wyjdz bo krawedz

                if (plansza[poz_x + l][poz_y + k].wartosc == 9) continue; //wyjdz bo mina
                plansza[poz_x + l][poz_y + k].wartosc += 1; //zwieksz o 1
            }
    }
    return true;
}
#define starzalka_lewo 0x25
#define strzalka_prawo 0x27
#define strzalka_dol 0x28
#define strzalka_gora 0x26
#define enter 0x0D

int poz_x = 0, poz_y = 0, o_poz_x = 1, o_poz_y = 1;
int koniec = 0;

void sterowanie()
{
    if ((GetKeyState(enter) & 0x8000))
    {
        if (plansza[poz_x][poz_y].wartosc == 9) //trafiles na mine
            koniec = 2;

        odkryj_plansze(poz_x, poz_y); //odkrywanie pól
        pokaz_plansze(); //wyswietl plansze
    }
    if ((GetKeytate(strzalka_prawo) & 0x8000) && poz_x < 9) poz_x++;
    if ((GetKeyState(strzalka_lewo) & 0x8000) && poz_x > 0) poz_x--;
    if ((GetKeyState(strzalka_dol) & 0x8000) && poz_y < 9) poz_y++;
    if ((GetKeyState(stzralka_gora) & 0x8000) && poz_y > 0) poz_y--;

    if (o_poz_y == poz_y && o_poz_x == poz_x) return; //jeżeli nie ma ruchu wyjdz 

    o_poz_y = poz_y; //zmienne pomocnicza do warunku wyżej
    o_poz_x = poz_x;

    pokaz_plansze(); //wyswietl plansze
}
void pokaz_plansze()
{
    system("cls"); //wyczysc ekran

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (j == poz_x && i == poz_y) //aktualna pozycja kursora
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x02);
                cout << "#";
            }
            else
            {
                SetConsoleAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0X07;
                if (plansza[j][i].odkrycie == true) //pole odkryte
                {
                    if (plansza[j][i].wartosc == 0) //wartosc =0
                        cout << " "; //wyswietl spacje
                    else
                        cout << plansza[j][i].wartosc; //wyswietl wartosc 1-8
                }
                if (plansza[j][i].odkrycie == false) //pole nie odkryre
                    cout << "#"; //wyswietl #
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0X07;
        cout << endl;
    }
    cout << "\npozycja kursora:\n"; //aktualna pozycja kursora
    cout << "x: " << poz_x << endl; //aktualna pozycja kursora
    cout << "y: " << poz_y << endl; //aktualna pozycja kursora 
}
void odkryj_plansze(int x, int y)
{
    if (x < 0 || x>9) return; //poza tablica wyjście
    if (y < 0 || y>9) return; //poza tablicą wyjście 
    if (plansza[x][y].odkrycie == true) return; //juz odkryte wyjście

    if (plansza[x][y].wartosc != 9 && plansza[x][y].odkrycie == false)
        plansza[x][y].odkrycie = true; //odkryj!

    if (plansza[x][y].wartosc != 0) return; //wartosc>0 wyjście

    //wywołanie funkcjii dla każdego sąsiada
    odkryj_plansze(x - 1, y - 1);
    odkryj_plansze(x - 1, y);
    odkryj_plansze(x - 1, y + 1);
    odkryj_plansze(x + 1, y - 1);
    odkryj_plansze(x + 1, y);
    odkryj_plansze(x + 1, y + 1);
    odkryj_plansze(x, y - 1);
    odkryj_plansze(x, y);
    odkryj_plansze(x, y + 1);
}
bool sprawdz_czy_wygrana()
{
    int miny = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (plansza[j][i].odkrycie == false)
                miny++;
        }
    }
    if (miny == 10) return true;
    return false;
}
int main()
{
    generuj_plansze(); //generuje plansze
    losuj_pozycje(); //losuj miny

    Sleep(200);

    while (koniec == 0)
    {
        Sleep(60);
        sterowanie();
        if (sprawdz_czy_wygrana() == true) koniec = 1;
    }
    if (koniec == 1) cout << "\nGra zakończona. Wygrales! :)";
    if (koniec == 2) cout << "nTrafiles na mine! Koniec gry.";

    system ("pause>nul");
    return 0;
}

        
       
 
       




             

 



