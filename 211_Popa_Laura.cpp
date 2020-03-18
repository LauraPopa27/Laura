#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <bits/stdc++.h>

#define NR_MAX_INDIVIZI 30
#define en_init 1000
#define varsta_max 101
#define en_minus 10

using namespace std;

void menu_output()
{
    cout<<endl<<"\n POPA LAURA IOANA 211 - Proiect 16 - Individ: \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<endl;
    cout<<"1. Optiune actualizare individ in pozitia <x>   : 1 <x>"<<endl;
    cout<<"2. Optiune test este viu individ in pozitia <x> : 2 <x>"<<endl;
    cout<<"3. Optiune get tip individ in pozitia <x>       : 3 <x>"<<endl;
    cout<<"4. Optiune afisare tabel indivizi "<<endl;
    cout<<"0. Optiune iesire din program."<<endl;

    cout << endl <<"Introduceti optiunea din meniu : ";
}

class individ
{
private:
    int i;
    char tip[2];
    int varsta;
    double energie;
    unsigned char viu;

    void hraneste();
    void inmulteste(individ **);
    void ataca(individ **);
    void imbatraneste();
    void moare();


public:
    individ (); //constructor 1
    individ (int, char*); //constructor 2

    int getpozitie();
    char * gettip();
    int esteviu();
    void actualizare(individ **);

    friend istream& operator >> (istream  &, individ &);
    friend ostream& operator << (ostream &, const individ &);
};

individ::individ(int pozz, char * tipp)
{
    varsta=0;
    energie=en_init;
    viu=1;

    i = pozz;
    strncpy(tip, tipp, 2);
}


individ::individ()
{
    varsta=0;
    energie=en_init;
    viu=1;

    i = -1;
    strcpy(tip, "-");
}

int individ::getpozitie()
{
    return i;
}

char * individ::gettip()
{
    return tip;
}

int individ::esteviu()
{
    return (int)viu;
}

void individ::actualizare(individ ** tbl_indivizi)
{
    hraneste();
    inmulteste(tbl_indivizi);
    ataca(tbl_indivizi);
    imbatraneste();
}

void individ::hraneste()
{
    energie+=(rand()%10)+1;
    cout << endl << "       Hranire : Hranit individ la pozitia " << i << ". Energie noua = " << energie;
}

void individ::inmulteste(individ ** tbl_indivizi)
{
  int index_crt = i;

  if(index_crt>0)
  {
      individ I_stanga = *tbl_indivizi[index_crt-1];
      if(I_stanga.i < 0)
      {
          I_stanga.i = index_crt-1;
          strncpy(I_stanga.tip, tip, 2);
          I_stanga.varsta = 0;
          I_stanga.energie = 2*energie;
          *tbl_indivizi[index_crt-1] = I_stanga;
          cout << endl << "       Inmultire : Inmultit individ de la pozitia " << index_crt <<
                                               ". Fiu nou la pozitia = " << index_crt-1 <<
                                               ", cu energie = " << I_stanga.energie;
          return;
      }
  }


  if(index_crt<NR_MAX_INDIVIZI-1)
  {
      individ I_dreapta = *tbl_indivizi[index_crt+1];
      if(I_dreapta.i < 0)
      {
          I_dreapta.i = index_crt+1;
          strncpy(I_dreapta.tip, tip, 2);
          I_dreapta.varsta = 0;
          I_dreapta.energie = 2*energie;
          *tbl_indivizi[index_crt+1] = I_dreapta;
          cout << endl << "       Inmultire : Individul de la pozitia " << index_crt <<
                                               ". Fiu nou la pozitia = " << index_crt+1 <<
                                               ", cu energie = " << I_dreapta.energie;
          return;
      }
  }


  cout << endl << "       Inmultire : Individul nu are pozitii libere alaturate.";
}

void individ::ataca(individ ** tbl_indivizi)
{
  int index_crt = i;
  int i_atac_reusit = 0;

  if(index_crt>0)
  {
      individ I_stanga = *tbl_indivizi[index_crt-1];
      if(I_stanga.i >= 0)
      {
          if(strncmp(I_stanga.tip, tip, 1) && I_stanga.energie < energie)
          {
              i_atac_reusit = 1;
              energie -= I_stanga.energie;
              I_stanga.moare();
              I_stanga.energie = 0;
              *tbl_indivizi[index_crt-1] = I_stanga;
              cout << endl << "       Atacare : Individul de la pozitia " << index_crt <<
                                                   " a atacat si a omorat pozitia = " << index_crt-1 <<
                                                   ", ramanand cu energia = " << energie;
          }
      }
  }


  if(index_crt<NR_MAX_INDIVIZI-1)
  {
      individ I_dreapta = *tbl_indivizi[index_crt+1];
      if(I_dreapta.i >= 0)
      {
          if(strncmp(I_dreapta.tip, tip, 1) && I_dreapta.energie < energie)
          {
              i_atac_reusit = 1;
              energie -= I_dreapta.energie;
              I_dreapta.moare();
              I_dreapta.energie = 0;
              *tbl_indivizi[index_crt+1] = I_dreapta;
              cout << endl << "       Atacare : Individul de la pozitia " << index_crt <<
                                                   " a atacat si a omorat pozitia = " << index_crt+1 <<
                                                   ", ramanand cu energia = " << energie;
          }
      }
  }

  if(!i_atac_reusit)
      cout << endl << "       Atacare : Individul nu a putut ataca pozitiile alaturate.";
}

void individ::imbatraneste()
{
    varsta += 1;
    energie -= en_minus;
    energie = max(energie, 0.0);

    if(varsta >= varsta_max || energie <= 0)
    {
        moare();
    }

    if(esteviu())
        cout << endl << "       Imbatranire : Individul de la pozitia " << i <<
                                                   " a imbatranit si a ajuns la varsta = " << varsta <<
                                                   ", ramanand cu energia = " << energie;
    else
        cout << endl << "       Imbatranire : Individul de la pozitia " << i <<
                                                   " a ajuns la varsta = " << varsta <<
                                                   " si energia = " << energie << " si a murit.";
}

void individ::moare()
{
    viu = 0;
}

istream& operator >> (istream  &in, individ &I)
{
     in>> I.i;
     in>> I.tip;
     return in;
}

ostream& operator << (ostream &out, const individ &I)
{
     out<< endl <<  "Poz = " << I.i << ". Tip = " << I.tip << ". Varsta = " << I.varsta <<
                        ". Energie = " << I.energie << ". Viu = " << (int)I.viu << ".";
     return out;
}

void citeste_indivizi(individ * tbl_indivizi[NR_MAX_INDIVIZI], int &nr_indivizi_init)
{
    cout << endl << " Citire initiala indivizi : " << endl;
    cout << endl << "     Numar initial indivizi (maxim 30) = ";
    cin >> nr_indivizi_init;

    for (int i=0; i<nr_indivizi_init; i++)
    {
        individ I;

        cout << endl << "     Citire individ " << i+1 << "/" << nr_indivizi_init
             << " : <pozitie (max. " << NR_MAX_INDIVIZI-1 << ")> <tip ('+' sau '0'> : ";
        cin >> I;

        *tbl_indivizi[I.getpozitie()] = I;
        cout << endl << "     Creat individ la pozitia " << I.getpozitie() << ". Tip = " << I.gettip() << endl << endl;
    }
}

void meniu(individ * tbl_indivizi[NR_MAX_INDIVIZI])
{
    char c_opt[2];
    int i_opt = -1;

    while(1)
    {
        menu_output();

        cin >> c_opt;

        if(!strncmp(c_opt,"0",1))
        {
            cout << endl << " --QUIT-- " << endl << endl;
            return;
        }
        else if(!strncmp(c_opt,"4",1))
        {
            cout << endl << endl << endl << endl <<        "            -- Tabel indivizi --           " << endl;
            for(int i = 0; i<NR_MAX_INDIVIZI; i++)
           {
               individ I = *tbl_indivizi[i];
               if(I.getpozitie() >= 0)
               cout << I;
           }
           continue;

        }

        cin >> i_opt;

        //verificari
        if(strncmp(c_opt,"1",1) && strncmp(c_opt,"2",1) && strncmp(c_opt,"3",1) && strncmp(c_opt,"4",1))
        {
            cout << endl << "Eroare citire optiune : " << c_opt << endl;
            continue;
        }
        if(i_opt < 0 || i_opt >= NR_MAX_INDIVIZI)
        {
            cout << endl << "Eroare citire pozitie individ : " << i_opt << endl;
            continue;
        }

        individ I = *tbl_indivizi[i_opt];

        if(!strncmp(c_opt,"1",1))
        {
            if(I.esteviu())
            {
                 I.actualizare(tbl_indivizi);

                *tbl_indivizi[I.getpozitie()] = I;
            }
            else
            {
                cout << endl << " Eroare: Individul din pozitia " << i_opt << " nu mai este viu." << endl;
                continue;
            }
        }
        else if(!strncmp(c_opt,"2",1))
        {
            if(I.esteviu())
                cout << endl << "       Individul de la pozitia : " << I.getpozitie() << ": ESTE viu.";
            else
                cout << endl << "       Individul de la pozitia : " << I.getpozitie() << ": NU este viu.";
        }
        else if(!strncmp(c_opt,"3",1))
        {
            if(I.esteviu())
                cout << endl << "       Individul de la pozitia : " << I.getpozitie() <<
                                " are tipul = '" << I.gettip() << "'.";
            else
                cout << endl << "       Individul de la pozitia : " << I.getpozitie() <<
                                " a avut tipul = '" << I.gettip() << "'.";
        }

    }

     system("pause");
     system("cls");
}

int main()
{
    static int nr_indivizi_init;
    static individ * tbl_indivizi[NR_MAX_INDIVIZI];

    for(int i=0; i<NR_MAX_INDIVIZI; i++)
    {
        tbl_indivizi[i] = new individ();
    }

    citeste_indivizi(tbl_indivizi, nr_indivizi_init);

    meniu(tbl_indivizi);

    return 0;
}
