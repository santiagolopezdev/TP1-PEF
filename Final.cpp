#include <iostream>
#include <fstream>

using namespace std;

struct dato
{
  char nombre[30];
  int n;
  int otro;
  int v[50][50];
};

int Abrir(struct dato *d);
void Valor(struct dato *d);
int Guardar(struct dato *d);

int main(void)
{

  dato d;
  int error = 0;
  d.v[0][0] = 0;

  error = Abrir(&d); //funcion
  if (error == 1)
  {
    cout << "\nNo se pudo abrir el archivo";
    return 0;
  } /*
error=Comprirmir (&d);
if (error==2){
              cout << "\nFallo la descomprecion";
              return 0;
              }*/

  Valor(&d);
  error = Guardar(&d);
  if (error == 3)
  {
    cout << "\nFallo la descomprecion";
    return 0;
  }

  return 0;
}

int Abrir(struct dato *d)
{

  int i, v[1000], s = 0, n = 0, j;
  ifstream archivo;

  cout << endl
       << "Ingrese el nombre de archivo ";
  cin >> d->nombre;
  archivo.open(d->nombre);

  while (!archivo.eof())
  {
    for (i = 0; i <= 9999; i++)
    {

      archivo >> v[i];
      // if(!archivo.eof());
      //n++;
    }
  }
  d->n = n / 50;

  s = v[0];

  for (j = 0; j <= d->n; j++)
  {
    d->v[j][0] = v[j * 50];
    for (i = 0; i <= 48; i++)
    {
      d->v[j][i + 1] = d->v[j][i] + v[i + 1];
    }
    //d->v[j][50]=v[j][50];/*
    for (j = 0; j <= d->n; j++)
    {
      for (i = 50; i <= 49; i++)
      {
        d->v[j][i + 1] = d->v[j][i] + v[i + 1];
      }
    }
  }

  return 0;
}
void Valor(struct dato *d)
{

  int i, j, m;
  int e;

  float s = 0;
  for (j = 0; j <= d->n; j++)
  {
    m = d->v[j][0];
    e = d->v[j][0];
    for (i = 0; i <= 49; i++)
    {

      s = d->v[j][i] + s;
    }

    for (i = 1; i <= 49; i++)
    {
      if (m > d->v[j][i])
      {
        m = d->v[j][i];
      }
      if (e < d->v[j][i])
      {
        e = d->v[j][i];
      }
    }
  }
  cout << s << "/100= " << s / 100 << " || " << m << "  " << e;
}

int Guardar(struct dato *d)
{

  int i, j;
  char nombre[30];

  ofstream guarda;
  cout << "\nComo guardar el archivo ";
  cin >> nombre;
  guarda.open(nombre);
  for (j = 0; j <= (d->n + 1); j++)
  {
    for (i = 0; i <= 49; i++)
    {
      guarda << d->v[j][i] << " ";
    }
    guarda << "\n";
  }
  guarda.close();
  return 0;
}
