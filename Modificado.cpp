#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct dato {
  char nombre[30];
  vector<vector<int>> matriz;
  int min;
  int max;
  float promedio;
  int cantMuestras = 0;
};

int AbrirArchivo(struct dato *d);
int Decodificar(struct dato *d);
int ValorMaxMinProm(struct dato *d);
int GuardarArchivo(struct dato *d);
void ImprimirPorConsola(struct dato *d);
void LiberarMemoria(struct dato *d);

int main(void) {
  dato* d = new struct dato;
  int error = 0;

  error = AbrirArchivo(d); // Funcion que carga los datos del archivo
  if (error == 1) {
    cout << "\nNo se pudo abrir el archivo \n";
    return 0;
  }

  error = Decodificar(d); // Funcion que comprime los datos del archivo
  if (error == 1) {
    cout << "\nFallo comprimiendo el texto";
    return 0;
  }
  // ImprimirPorConsola(&d);
  error = ValorMaxMinProm(d);
  if (error == 1) {
    cout << "\nFallo obteniendo el maximo/min/promedio";
    return 0;
  }
  error = GuardarArchivo(d);
  if (error == 1) {
    cout << "\nFallo guardando el archivo";
    return 0;
  }
  delete d;
  return 0;
}

int AbrirArchivo(struct dato *d) {
  ifstream archivo;
  cout << endl << "Ingrese el nombre de archivo: \n";
  cin >> d->nombre;

  archivo.open(d->nombre);
  if (!archivo) {
    return 1;
  }
  string *palabra = new string;
  int *contadorInterno = new int;
  *contadorInterno = 0;
  vector<int> *temp = new vector<int>;
  while (archivo >> *palabra) {
    *contadorInterno = *contadorInterno + 1;
    d->cantMuestras++;
    int num = stoi(*palabra);
    if (*contadorInterno <= 50) {
      temp->push_back(num);

    } else {
      *contadorInterno = 1;
      d->matriz.push_back(*temp);
      temp = new vector<int>;
      temp->push_back(num);
    }
  }
  if (temp->size() != 0) {
    d->matriz.push_back(*temp);
  }
  delete palabra;
  delete contadorInterno;
  delete temp;
  archivo.close();
  return 0;
}

int ValorMaxMinProm(struct dato *d) {
  d->max = d->matriz[0][0];
  d->min = d->matriz[0][0];
  d->promedio = 0;
  int* i = new int;
  int* j = new int;
  
  for (*i = 0; *i < d->matriz.size(); *i = *i+1) {
    for (*j = 0; *j < d->matriz[*i].size(); *j = *j+1) {
      if (d->max < d->matriz[*i][*j]) {
        d->max = d->matriz[*i][*j];
      }
      if (d->min > d->matriz[*i][*j]) {
        d->min = d->matriz[*i][*j];
      }
      d->promedio = d->promedio + d->matriz[*i][*j];
    }
  }
  cout << "La matriz tiene " << d->cantMuestras << " Elementos" << endl;
  d->promedio = d->promedio / d->cantMuestras;
  cout << "Promedio: " << d->promedio << " || Maximo:" << d->max << " || Minimo:" << d->min;
  delete i;
  delete j;
  return 0;
}

int GuardarArchivo(struct dato *d) {
  ofstream guarda;
  cout << "\nIngrese nombre del archivo a guardar \n";
  cin >> d->nombre;
  guarda.open(d->nombre);
  guarda << "Cantidad de cuadros almacenados: " << d->matriz.size() << " - "<< d->cantMuestras << " muestras contenidas en total\n";
  int* i = new int;
  int* j = new int;
  for (*i = 0; *i < d->matriz.size(); *i = *i+1) {
    for (*j = 0; *j < d->matriz[*i].size(); *j = *j+1) {
      guarda << d->matriz[*i][*j] << " ";
    }
    guarda << "\n";
  }
  guarda.close();
  delete i;
  delete j;
  
  return 0;
}

void ImprimirPorConsola(struct dato *d) {
  int* i = new int;
  int* j = new int;
  for (*i = 0; *i < d->matriz.size(); *i = *i+1) {
    for (*j = 0; *j < d->matriz[*i].size(); *j = *j+1) {
      cout << d->matriz[*i][*j] << " ";
    }
    cout << endl;
  }

  delete i;
  delete j;
}

int Decodificar(struct dato *d) {
  int* i = new int;
  int* j = new int;
  for (*i = 0; *i < d->matriz.size(); *i = *i+1) {
    int valorPrevio = d->matriz[*i][0];
    for (*j = 1; *j < d->matriz[*i].size(); *j = *j+1) {
      d->matriz[*i][*j] = valorPrevio + d->matriz[*i][*j];
      valorPrevio = d->matriz[*i][*j];
    }
  }
  delete i;
  delete j;
  return 0;
}