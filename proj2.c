// Roman Stepaniuk
// xstepa64

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define U_T 0.0258563
#define I_0 1e-12 // to se rovna powl(10, -12)

double diode(double u0, double r, double eps)
{
  double l_side = 0;
  double r_side = u0;
  double i_p, i_r;
  double center;
  double u_r = u0;
  double u_p = 0;
  double middle;
  while (fabs(l_side - r_side)  > eps) // kontrolujeme jestli absolutni hodnota i_p - i_r > eps 
  {
    center = (r_side + l_side) / 2; // vypocitame center x souradnice
   
    u_p = center; //menime hodnotu centra metodou puleni intervalu, coz znamena, ze menime u_p
    u_r = u0 - u_p; //hledame z toho ur

    i_p = I_0 *(expl(u_p / U_T) - 1);
    i_r = u_r / r;
    if(middle == u_p) //kdyz se zacikli, tak podminka na nekonecny cyklus
    {
      break;
    } 
    if(i_p - i_r < 0) // kdyz hodnota i_r > i_p menime levou stranu na center abychom to spocitali mezi centrem a pravou stranou 
     {
       l_side = center;
     }  else if (i_p - i_r > 0) 
     {
       r_side = center;
     }
    middle = u_p; //promena pro podminku jestlu up na novem cyklu == up z predchoziho ciklu
  }
  return u_p; // vraci to stredni hodnotu 
}

double vypocet_ip(double u_p)
{
  double i_p = I_0 *(expl(u_p / U_T) - 1); //vypocitani i_p podle formule
  return i_p;
}

int kontrola_argumentu(int argc, char *argv[], int kontrola_vstupu)
{
  if(argc != 4)
  { 
     kontrola_vstupu++;
  } else
  {
    if(atof(argv[2]) == 0) //kontrolujeme hodnoty argumentu
    {
       kontrola_vstupu++;
    } else 
    {  
     for (int i = 1; i <= 3; i++)
      {
        char *sym_var = NULL;
        double value = strtod(argv[i], &sym_var); //kontrolujeme na cokoliv krome cislovych hodnot
        if(*sym_var != '\0')
         {
           kontrola_vstupu++;
         }
        if(value < 0) //kontrola na zaporne hodnoty
         {
           kontrola_vstupu++; 
         }
      }
    }
  }
  return kontrola_vstupu;
}

int main(int argc, char *argv[])
{
  int kontrola_vstupu = 0;
  kontrola_vstupu = kontrola_argumentu(argc, argv, kontrola_vstupu); // kontrola argumentu
  if(kontrola_vstupu == 0) 
   {
    double u0 = atof(argv[1]); // bereme hodnoty argumentu a davame je do promenne
    double r = atof(argv[2]);
    double eps = atof(argv[3]); 
    double u_p = diode(u0, r, eps); // vypocitame up (pouzivame metodu intervalu)
    double i_p =  vypocet_ip(u_p); // pocitame ip
    printf("Up=%g V\nIp=%g A\n", u_p, i_p);
   } else 
   {
    fprintf(stderr, "error: invalid arguments\n"); //vypis chybneho vstupu
   }
  return 0;
}