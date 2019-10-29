#include <iostream>

using namespace std;

double counting_interpolation ( int n, double xp, double x[], double f[] )
{

   double l[n+1];
   double sum=0;

   for (int i=0; i<n+1;i++)
   {

   l[i]=1;

   for (int k=0;k<n+1;k++ )
   {
       if (i!=k)
        l[i]*=(xp-x[k])/(x[i]-x[k]);

   }

   sum+=l[i]*f[i];

   }
return sum;


}

int main()
{
    int n;
    cout<<"Podaj stopien wielomianu"<<endl;
    cin>>n;
    if (n<=0)
      {
    cerr<<"Stopien musi być dodatni"<<endl;
    return 0;}

    else

    {
        double x[n+1],f[n+1];

      for (int i=0; i<n+1;i++)
      {
          cout<<" Podaj " << i <<"  wspolrzedna wielomianu"<<endl;
          cin>>x[i];
          cout<<" Podaj f[i]" <<endl;
          cin>>f[i];
      }



    for (int i=1; i<n+1; i++)
    {
        if (x[i-1]>=x[i])
            {cout<<"Nieposortowane dane"<<endl;
        return -1;
            }
    }

    double xp;

    cout<<"Podaj xp"<<endl;
    cin>>xp;

    if (xp<x[0] || xp>x[n-1])
        {cerr<<"Wspolrzedna nie nalezy do przedziału"<<endl;
    return -1;}

    cout<<counting_interpolation(n,xp,x,f);

    }

    return 0;
}
