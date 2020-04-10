#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <new>
#include <bits/stdc++.h>

using namespace std;

class Complex
{
protected:
    float real;
    float imag;

public:

    Complex (float, float);  //constructor initializare
    Complex (const Complex&); //constructor copiere
    virtual ~Complex ();  //destructor

    void set_real(float);
    void set_imag(float);
    float get_real(){return real;};
    float get_imag(){return imag;};
    virtual void afisare(ostream &out);
    virtual void citire(istream &in);
    friend istream& operator>>(istream &in, Complex& z);
    friend ostream& operator<<(ostream &out, Complex& z);
    double modul();

    Complex& operator=(Complex &z);
    friend Complex& operator+(Complex& z1, Complex& z2);
    friend Complex& operator*(Complex& z1, Complex& z2);
    friend Complex& operator/(Complex& z1, Complex& z2);
    friend Complex& operator-(Complex& z1, Complex& z2);
    friend Complex& z_amplif(float& , Complex& );
    friend int is_zero(Complex &);
};

Complex::Complex(float real=0.0, float imag=0.0)
{
    this->real = real;
    this->imag = imag;
}

Complex::Complex(const Complex &z)
{
    real = z.real;
    imag = z.imag;
}

Complex::~Complex()
{
    this->real=0;
    this->imag=0;
}

void Complex::set_real(float x){
    real = x;
}
void Complex::set_imag(float y){
    imag=y;
}
void Complex::citire(istream &in)
{
    cout<<"    Citeste partea reala: ";
    in>>real;
    cout<<"         Citeste partea imaginara: ";
    in>>imag;
}
void Complex::afisare(ostream &out)
{
    if (imag==0) {
        out<<real;
    }
    else{
        if (imag < 0){
            out<<real<<imag<<"*i";
        }
        else{
            out<<real<<"+"<<imag<<"*i";
        }
    }
}

istream& operator >> (istream  &in, Complex &z)
{
     z.citire(in);
     return in;
}

ostream& operator << (ostream &out, Complex &z)
{
     z.afisare(out);
     return out;
}

double Complex::modul()
{
    return sqrt(real*real+imag*imag);
}

Complex& Complex::operator=(Complex &z)
{
    real=z.real;
    imag=z.imag;
    return *this;
}

inline Complex& operator+(Complex &z1, Complex& z2){
   Complex *z= new Complex;
    z->real = z1.real + z2.real;
    z->imag = z1.imag + z2.imag;
    return *z;
}
inline Complex& operator*(Complex &z1, Complex& z2){
    Complex *z= new Complex;
    z->real = z1.real * z2.real - z1.imag * z2.imag;
    z->imag = z1.real * z2.imag + z2.real * z1.imag;
    return *z;
}
Complex& operator/(Complex &z1, Complex &z2)
{
    Complex *z= new Complex;
    if(is_zero(z1)!=0)
    {
        if(is_zero(z2)!=0)
        {
            z->real = (z1.real*z2.real + z1.imag*z2.imag) / (z2.real*z2.real + z2.imag*z2.imag);
            z->imag = (z2.real*z1.imag - z1.real*z2.imag) / (z2.real*z2.real + z2.imag*z2.imag);
        }
        else
        {
            cout<<"Eroare: impartire la zero. \n";
            exit(EXIT_FAILURE);
        }
    }
    return *z;
}

Complex& operator-(Complex &z1, Complex& z2)
{
   Complex *z= new Complex;
    z->real = z1.real - z2.real;
    z->imag = z1.imag - z2.imag;
    return *z;
}

Complex &z_amplif(float& a, Complex& zin)
{
    Complex *zout= new Complex;
    zout->real = a * zin.real;
    zout->imag = a * zin.imag;

    return *zout;
}

int is_zero(Complex &z)
{
    if(z.real==0 && z.imag==0)
        return 1;

    return 0;
}

////////////////////////MATRICE////////////////////////////////
class Matrice
{
protected:
    Complex **v;
    static int n;

public:
    Matrice(int, int);
    Matrice(const Matrice& );
    virtual ~Matrice();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);

    friend istream& operator>>(istream &in, Matrice&);
    friend ostream& operator<<(ostream &out, Matrice&);
    Complex ** get_pointer()
    {
        return v;
    }
    static void numarObiecte()
    {
        cout<<n;
    }

};

int Matrice::n;

Matrice::Matrice(int lin=1, int col=1)
{
    n++;
    v = new Complex*[lin];
    for(int i=0; i<lin; i++)
        v[i] = new Complex[col];
}

Matrice::Matrice(const Matrice &mat)
{
    Matrice::v = mat.v;
}

Matrice::~Matrice()
{
    delete [] v;
}

void Matrice::citire(istream &in)
{
    cout << endl << endl << " * In 'citire' pt 'Matrice': do nothing. ";
}

void Matrice::afisare(ostream &out)
{
    cout << endl << endl << " * In 'afisare' pt 'Matrice': do nothing. ";
}


istream& operator>>(istream &in, Matrice &mat)
{
    mat.citire(in);

    return in;
}

ostream& operator<<(ostream &out, Matrice &mat)
{
     mat.afisare(out);

     return out;
}


//////////////////////////MATRICE OARECARE///////////////////////////////////////
class Matrice_oarecare:public Matrice
{
private:
    int lin;
    int col;
public:
    Matrice_oarecare(int, int); //constructor
    Matrice_oarecare(const Matrice_oarecare& ); //constructor de copiere
    ~Matrice_oarecare(); //destructor
    void set_col(int);
    void set_lin(int);
    int get_col() {return col;};
    int get_lin() {return lin;};
    void citire(istream &in, Matrice_oarecare&);
    void afisare(ostream &out, Matrice_oarecare&);

    friend istream& operator>>(istream&, Matrice_oarecare&);
    friend ostream& operator<<(ostream&, Matrice_oarecare&);
    Matrice_oarecare& operator=(const Matrice_oarecare &);
    void realocare_matrice(int, int);
    void set_lin_col(int, int);
    int is_square();
    int is_triangular();
    int is_upper();
    int is_lower();
    void is_diagonal();

};

void Matrice_oarecare::realocare_matrice(int newlin, int newcol)
{
    for(int i=0; i<lin; i++)
        delete [] Matrice::v[i];
    delete Matrice::v;

    lin = newlin;
    col = newcol;

    Matrice::v = new Complex *[lin];
    for (int i = 0; i < lin; i++)
        Matrice::v[i] = new Complex[col];
}


Matrice_oarecare::Matrice_oarecare(int nlin=1 , int ncol=1 ): Matrice(nlin, ncol)
{
    lin = nlin;
    col = ncol;
    v = new Complex *[lin];
    for (int i = 0; i < lin; i++)
        v[i] = new Complex[col];
}

Matrice_oarecare::~Matrice_oarecare()
{
    for (int i = 0; i < lin; i++)
    {
        delete v[i];
    }
    delete [] Matrice::v;
    lin = col = 0;
}

Matrice_oarecare::Matrice_oarecare(const Matrice_oarecare &mat)
{
    lin=mat.lin;
    col=mat.col;
    Matrice::v = mat.v;
}

void Matrice_oarecare::set_lin(int nlin)
{
    lin=nlin;
}

void Matrice_oarecare::set_col(int ncol)
{
    col=ncol;
}

void Matrice_oarecare::citire(istream &in, Matrice_oarecare& mat)
{
    int newlin, newcol;
    Matrice::citire(in);

   cout<<endl<<"--CITIRE MATRICE OARECARE--"<<endl;
   cout<<"Introduceti nr de linii : "<<endl;
   in >> newlin;
   cout<<"Introduceti nr de coloane : "<<endl;
   in >> newcol;

   realocare_matrice(newlin, newcol);

   cout<<"Introduceti elementele matricei: "<<endl;
   for ( int i = 0; i < newlin; i++ )
        for ( int j = 0; j < newcol; j++ )
          {
              cout<<"matrice_oarecare["<<i<<"]["<<j<<"]=";
              in >> mat.v[i][j];
          }
}

void Matrice_oarecare::afisare(ostream &out, Matrice_oarecare& mat)
{
    Matrice::afisare(out);

    out<<endl<<"Afisarea matricei oarecare: "<<endl;
    for(int i=0; i<lin; i++)
     {
        for(int j=0; j<col; j++)
            out << mat.v[i][j] << ' ';
        out << endl;
     }
}

istream& operator >> (istream  &in, Matrice_oarecare & mat)
{
    mat.citire(in,mat);
    return in;
}

ostream& operator<<(ostream& out, Matrice_oarecare &mat)
{
    mat.afisare(out,mat);
    return out;
}

Matrice_oarecare& Matrice_oarecare::operator=(const Matrice_oarecare &mat)
{
  realocare_matrice(mat.lin, mat.col);

  for(int i=0; i<lin; i++)
        for(int j=0; j<col; j++)
            Matrice::v[i][j] = mat.v[i][j];

    return *this;
}

void Matrice_oarecare::set_lin_col(int nlin, int ncol)
{
    lin = nlin;
    col = ncol;
}

int Matrice_oarecare::is_square()
{
    return lin==col ? 1:0;
}

int Matrice_oarecare::is_triangular()
{
        if(is_upper())
            return 1;
        if(is_lower())
            return -1;
        return 0;
}

int Matrice_oarecare::is_upper()
{
    for(int i=1; i<lin; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(!is_zero(Matrice::v[i][j]))
            {
                return 0;
            }
        }
    }
    return 1;
}

int Matrice_oarecare::is_lower()
{
    for(int i=0; i<lin-1; i++)
    {
        for(int j=i+1; j<col; j++)
        {
            if(!is_zero(Matrice::v[i][j]))
            {
                return 0;
            }
        }
    }
    return 1;
}

void Matrice_oarecare::is_diagonal()
{
    if(is_upper() && is_lower())
        cout<<"\nMatricea oarecare este diagonala.";
    else
        cout<<"\nMatricea oarecare NU este diagonala.";
}



////////////////////MATRICE PATRATICA////////////////////////////
class Matrice_patratica:public Matrice
{
private:
    int dim;
public:
    Matrice_patratica(int); //constructor
    Matrice_patratica(const Matrice_patratica& ); //constructor de copiere
    ~Matrice_patratica(); //destructor
    void set_dim(int);
    int get_dim() {return dim;};

    void citire(istream &in, Matrice_patratica&);
    void afisare(ostream &out, Matrice_patratica&);

    friend istream& operator>>(istream&, Matrice_patratica&);
    friend ostream& operator<<(ostream&, Matrice_patratica&);
    Matrice_patratica& operator=(const Matrice_patratica &mat);
    void realocare_matrice(int);

    int is_triangular();
    int is_upper();
    int is_lower();
    void is_diagonal();

    Complex &determinant(int n, Complex **mat)
{
        Complex *z= new Complex(0,0);
        Matrice_patratica Submatrice(n);
        Complex ** submat = Submatrice.v;

        int subi, subj;

        if(n==2)
        {
            return ((mat[0][0]*mat[1][1]) - (mat[1][0]*mat[0][1]));
        }

        for(int c=0; c<n; c++)
        {
            subi = 0;
            for(int i=1; i<n; i++)
            {
                subj = 0;
                for(int j=0; j<n; j++)
                {
                    if (j == c)
                        continue;

                    submat[subi][subj] = mat[i][j];
                    subj++;
                }
                subi++;
            }
            Complex zz(mat[0][c]);
            float sign = pow(-1,c);
            zz = z_amplif(sign, zz);
            *z = *z + (zz * determinant(n-1, submat));
        }
        return *z;
}

};

void Matrice_patratica::realocare_matrice(int newdim)
{
    for(int i=0; i<dim; i++)
        delete [] Matrice::v[i];
    delete Matrice::v;

    dim = newdim;

    Matrice::v = new Complex *[dim];
    for (int i = 0; i < dim; i++)
        Matrice::v[i] = new Complex[dim];
}

Matrice_patratica::Matrice_patratica(int n = 1): Matrice(n, n)
{
    dim = n;
    v = new Complex *[dim];
    for (int i = 0; i < dim; i++)
        v[i] = new Complex[dim];
}

Matrice_patratica::Matrice_patratica(const Matrice_patratica &mat)
{
    dim=mat.dim;
    Matrice::v = mat.v;
}

Matrice_patratica::~Matrice_patratica()
{
    for (int i = 0; i < dim; i++)
    {
        delete v[i];
    }
    delete v;
    dim = 0;
}

void Matrice_patratica::set_dim(int newdim)
{
    dim=newdim;
}

void Matrice_patratica::citire(istream &in, Matrice_patratica& mat)
{
    int newdim;
    Matrice::citire(in);

    cout<<endl<<"--CITIRE MATRICE PATRATICA--"<<endl;
    cout<<"Introduceti dimensiunea matricei patratice: "<<endl;
    in >> newdim;
    cout<<"Introduceti elementele matricei: "<<endl;

    realocare_matrice(newdim);

    for ( int i = 0; i < newdim; i++ )
      for ( int j = 0; j < newdim; j++ )
        {
            cout<<"matrice_patratica["<<i<<"]["<<j<<"]=";
            in >> Matrice::v[i][j];
        }
}

void Matrice_patratica::afisare(ostream &out, Matrice_patratica& mat)
{
    Matrice::afisare(out);

    out<<endl<<"Afisarea matricei patratice: "<<endl;
    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim; j++)
            out << Matrice::v[i][j] << '\t';
        out << endl;
    }

    out<<"\nDeterminantul matricei este: ";
    out<<determinant(dim, Matrice::v)<<endl;
}

istream& operator>>(istream& in,Matrice_patratica &mat)
{
    mat.citire(in,mat);
    return in;
}

ostream& operator<<(ostream& out, Matrice_patratica &mat)
{
    mat.afisare(out,mat);
    return out;
}

Matrice_patratica& Matrice_patratica::operator=(const Matrice_patratica &mat)
{
    realocare_matrice(mat.dim);

    for(int i=0; i<dim; i++)
       for(int j=0; j<dim; j++)
            Matrice::v[i][j] = mat.v[i][j];

    return *this;
}


int Matrice_patratica::is_triangular()
{
   if(is_upper())
            return 1;
        if(is_lower())
            return -1;
        return 0;
}

int Matrice_patratica::is_upper()
{
    for(int i=1; i<dim; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(!is_zero(Matrice::v[i][j]))
            {
                return 0;
            }
        }
        }
    return 1;
}

int Matrice_patratica::is_lower()
{
    for(int i=0; i<dim-1; i++)
    {
        for(int j=i+1; j<dim; j++)
        {
            if(!is_zero(Matrice::v[i][j]))
            {
                return 0;
            }
        }
    }
    return 1;
}

void Matrice_patratica::is_diagonal()
{
    if(is_upper() && is_lower())
        cout<<"\nMatricea patratica este diagonala.";
    else
        cout<<"\nMatricea patratica NU este diagonala.";
}

///////////MENIU////////

void menu_output()
{
    printf("\n Popa Laura Ioana 211 - Proiect 2->TEMA 10 - Matrice complexa: \n");
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    printf("1: Citire matrice oarecare "); printf("\n");
    printf("2: Citire matrice patratica "); printf("\n");
    printf("3: Verificare daca matricea patratica este diagonala "); printf("\n");
    printf("4: Verificare daca matricea oarecare este diagonala "); printf("\n");
    printf("5: Afisare matrice oarecare "); printf("\n");
    printf("6: Afisare matrice patratica "); printf("\n");
    printf("q: Iesire."); printf("\n");
}
void menu()
{
    Matrice_oarecare MO;
    Matrice_patratica MP;
    char option[2];

    do
    {
        menu_output();

        printf("\nIntroduceti numarul actiunii: ");
        cin>>option;

        if (!strncmp(option,"1",1))
        {
           cin>>MO;
        }
        if (!strncmp(option,"2",1))
        {
            cin>>MP;
        }
        if (!strncmp(option,"3",1))
        {
            MP.is_diagonal();
        }
        if (!strncmp(option,"4",1))
        {
            MO.is_diagonal();
        }
        if (!strncmp(option,"5",1))
        {
            cout<<MO;
        }
        if (!strncmp(option,"6",1))
        {
            cout<<MP;
        }

        if (!strncmp(option,"q",1))
        {
            cout << endl << " --QUIT-- " << endl << endl;
            return;
        }
         if(strncmp(option,"1",1) && strncmp(option,"2",1) && strncmp(option,"3",1) && strncmp(option,"4",1)
            && strncmp(option,"5",1) && strncmp(option,"6",1) && strncmp(option,"q",1))
        {
            printf("\nSelectie invalida\n");
        }
        printf("\n");
        system("pause");
        system("cls");
    }
    while(option!=0);
}


////////////////////////////////////////
int main()
{
    //menu();

    Matrice::numarObiecte();
    cout<<"\n";

    //CITIREA SI AFISAREA OBIECTELOR
    int nr_ob;
    cout<<"\n Nr obiecte de citit: ";
    cin>>nr_ob;
    Matrice_oarecare A(10,10);
    Matrice_patratica B(10);

    for(int i=0;i<nr_ob;i++)
    {
        cin>>A;
        cin>>B;

        cout<<A;
        cout<<B;

        A.is_diagonal();
        B.is_diagonal();
    }

    A.~Matrice_oarecare();
    B.~Matrice_patratica();


   //DEMONSTRATIE OPERATOR SUPRAINCARCAT "="
    Matrice_patratica MP, MP1;
    cin>>MP;
    cin>>MP1;
    MP=MP1;
    cout<<MP;
    cout<<MP1;


    //UPCAST MATRICE OARECARE
    Matrice *M = new Matrice_oarecare();
    cout << endl<<" *** Demonstratie upcast matrice oarecare ***";
    cin>> *M;
    cout<< *M;
    //END UPCAST

    //DOWNCAST MATRICE OARECARE
    int nlin=2, ncol=2;
    Matrice_oarecare *MO = (Matrice_oarecare*) new Matrice(nlin,ncol);
    cout <<endl<<endl<<" *** Demonstratie downcast matrice oarecare ***";
    MO->set_lin_col(nlin, ncol);
    cin>> *MO;
    cout<< *MO;
    //END DOWNCAST


    cout<<"\n";
    Matrice::numarObiecte();


    return 0;
}
