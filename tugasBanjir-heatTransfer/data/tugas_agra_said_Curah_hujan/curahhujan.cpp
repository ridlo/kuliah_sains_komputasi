/**
Program Simulasi Hujan
agra barecasco 20911014
Program ini menirukan pola curah hujan dalam 4 tahun sekali, dimulai pada tahun 1997
untuk disimulasikan pada tahun lain dengan curah per tahun sebagai input.
**/


#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<ctype.h>
#include<math.h>
#include<ctime>
#define PI 3.14

using namespace std;

FILE* gp;
FILE* fp;
int nkelas, nkelasbulan, range,bulan, titik, cacahTotal = 0;
int k[50];
double  curah,
        curahbulan,
        sebulan = 1.0,
        a1 = 173.7,
        b1 = 84.73,
        c1 = 0.2939,
        a2 = 71.32,
        b2 = 87.77,
        c2 = 4.763,
        a3 = 61.37,
        b3 = 104.3,
        c3 = 8.418,
        a4 = 60.11,
        b4 = 74.91,
        c4 = 3.969,
        a5 = 41.2,
        b5 = 117.5,
        c5 = 4.347 ;

double grand() // generator versi C++ dengan rand_max standar dari 0 sampai 1
{
    double hasil = rand()/(RAND_MAX + 1.0);
    return hasil;
}

double rejdist(double x) //Fungsi penghasil bilangan acak dengan distribusi yang diinginkan dengan metode rejection
{
    /*Pola persamaan hasil ekstrapolasi dari data hujan*/
    double cekrho = a1*exp( - pow(((x-b1)/c1),2)) +  a2*exp(-pow(((x-b2)/c2),2)) +  a3*exp(-pow(((x-b3)/c3),2)) +  a4*exp(-pow(((x-b4)/c4),2)) +  a5*exp(-pow(((x-b5)/c5),2));
    if(grand()*250.0 < cekrho)
    {
        cacahTotal++;
        return x;
    }
}

void gnuplot_condition()
{
    fprintf(gp,"unset key; unset border\n");
    fprintf(gp,"set zeroaxis 7\n");
    fprintf(gp,"set ylabel 'Curah Hujan' \n");
    fprintf(gp,"set xlabel 'Bulan' \n");
    fprintf(gp,"set xtics 1 \n");
    //fprintf(gp,"set ytics 0,20,1000 \n");
    fprintf(gp,"set grid \n");
    fflush(gp);
}

void plotdata(int nkelas)
{
    fprintf(gp,"plot [1:%d] 'distribusiacak.txt' w linespoints 3 \n", nkelas);
    fflush(gp);
    getchar();getchar();
}

void openplot()
{
    if (fopen("gnuplot\\README-TM.txt","r") == 0) //mengecek os apa yang bisa digunakan
    {
       gp = popen("gnuplot","w");
    }
    else gp = popen("gnuplot\\binary\\gnuplot","w");
}

void closeplot()
{
    fprintf(gp,"quit\n");
    fflush(gp);
    pclose(gp);
}



//Modul Tahun
void masukkelas(double acak)// Jika nilai acak lolos dari fungsi rejdist, maka akan dimasukkan kesini untuk dicari kelasnya.
{
    double j = 72+(range-1)*nkelas;
    int h = 0;
    double batasbwh;
    double batasats;
    while(j < 72+range*nkelas)//Fungsi penentu bilangan acak yang diperoleh masuk kelas mana
    {
        h += 1;
        batasbwh = j;
        batasats = (j+1.0);
        if (acak > batasbwh && acak < batasats)
        {
            k[h] += 1;
        }
        j += 1.0;
    }
}

void ambildata()
{
    double acak;

    fp = fopen("distribusiacak.txt","w");
    srand(time(0));

    for(int i =0;i<titik;i++)//Mencoba untuk tiap tembakan, lalu ditentukan tembakan tersebut masuk di kelas mana
    {
        acak = 72+((range-1)*nkelas)+nkelas*grand();
        acak = rejdist(acak);//Menggunakan metode rejection untuk menghasilkan distribusi yang diinginkan
        masukkelas(acak);
    }
    double sums = 0;
    for(int h = 1;h<=nkelas;h++)
    {
        fprintf(fp,"%d %lf \n", h, curah*k[h]/cacahTotal);
        sums +=  curah*k[h]/cacahTotal;
    }
    fclose(fp);
}

void disttahun()
{
        cout<<"\n# Masukan tipe distribusi [1-4] : "; scanf("%d",&range);
        nkelas = 12;
        cout<<"\n# Curah/tahun ? "; cin>>curah;
        cout<<"\n# Cacah bilangan acak ? "; cin>>titik;
        cacahTotal = 0;
        for(int h = 1;h<=nkelas;h++)
        {
            k[h] = 0;
        }
        double s = clock();
            ambildata();
        double t = clock();
        cout<<"\n[] perhitungan dalam "<<t-s<<" ms\n";
        plotdata(nkelas);
}



//Modul Bulan

void gnuplot_condition_bulan()
{
    fprintf(gp,"unset key; unset border\n");
    fprintf(gp,"set zeroaxis 7\n");
    fprintf(gp,"set ylabel 'Curah Hujan' \n");
    fprintf(gp,"set xlabel 'Hari' \n");
    fprintf(gp,"set xtics 1 \n");
    fprintf(gp,"set grid \n");
    fflush(gp);
}

void masukkelasbulan(double acak)// Jika nilai acak lolos dari fungsi rejdist, maka akan dimasukkan kesini untuk dicari kelasnya.
{
    double j = 72+((range-1)*nkelas) - 0.5 + bulan;
    int h = 0;
    double batasbwh;
    double batasats;
    while(j < 72+((range-1)*nkelas) + 0.5 + bulan)//Fungsi penentu bilangan acak yang diperoleh masuk kelas mana
    {
        h += 1;
        batasbwh = j;
        batasats = (j+(sebulan/nkelasbulan));
        if (acak > batasbwh && acak < batasats)
        {
            k[h] += 1;
        }
        j += (sebulan/nkelasbulan);
    }
}

void ambildatabulan()
{
    double acak;
    cout<<"\n# curah dalam bulan ini :"<<curahbulan<<endl;
    fp = fopen("distribusiacak.txt","w");
    srand(time(0));

    for(int i =0;i<titik;i++)//Mencoba untuk tiap tembakan, lalu ditentukan tembakan tersebut masuk di kelas mana
    {
        acak = (72+((range-1)*nkelas) - 0.5 + bulan)+sebulan*grand();

        acak = rejdist(acak);//Menggunakan metode rejection untuk menghasilkan distribusi yang diinginkan
        masukkelasbulan(acak);
    }
    double sums = 0;
    for(int h = 1;h<=nkelasbulan;h++)
    {
        fprintf(fp,"%d %lf \n", h, curahbulan*k[h]/cacahTotal);
        sums +=  curahbulan*k[h]/cacahTotal;
    }
    fclose(fp);
}

void distbulan()
{
    gnuplot_condition_bulan();
    cout<<"\n# Pilih bulan yang akan disimulasikan : ";cin>>bulan;
    nkelasbulan = 30;
    curahbulan = curah*k[bulan]/cacahTotal;
        cout<<"\n# Cacah bilangan acak ? "; cin>>titik;
        cacahTotal = 0;
        for(int h = 1;h<=nkelas;h++)
        {
            k[h] = 0;
        }

        double s = clock();
            ambildatabulan();
        double t = clock();
        cout<<"\n[] perhitungan dalam "<<t-s<<" ms\n";
        plotdata(nkelasbulan);
        cout<<"______________________________________________________|\n\n";

}





main()
{
    cout<<"|======================================================================\n";
    cout<<"|            \t\tSIMULATOR CURAH HUJAN\n|\n";
    cout<<"| Agra Barecasco 20911014\n";
    cout<<"|======================================================================\n\n";
    cout<<"[] Program ini mensimulasikan  bagaimana  distribusi curah hujan, yang\n"
        <<"   dimulai dari distribusi per tahun dilanjutkan dengan distribusi per\n"
        <<"   bulan. Input yang  dimasukkan  berupa  tipe fungsi distribusi (1-4), \n"
        <<"   perkiraan  curah  hujan  tahun yang akan  disimulasikan  dan jumlah\n"
        <<"   bilangan monte carlo yang digunakan untuk menentukan seberapa besar\n"
        <<"   keacakan data yang akan dihasilkan.\n\n"
        <<"[] Gunakan Ctrl-C untuk keluar.\n\n";

    openplot();
    gnuplot_condition();
    while(true)
    {
        disttahun();

        distbulan();
    }
    closeplot();
}
