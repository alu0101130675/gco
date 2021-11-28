#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>
#include <stdio.h>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::make_pair;
using std::string;
using std::vector;

void PrediccionSimple(std::vector<std::vector<int>> matrix, std::vector<float> correlacioens, std::vector<std::vector<int>> matrixvacios)
{
  float prediccionum = 0;
  float predicciondenom = 0;

  for (int j = 0; j < matrixvacios[0].size(); j++)
  {
    cout << "iteraciones: " << j << endl;
    for (int i = 1; i < matrix.size(); i++)
    {
      prediccionum += correlacioens[i] * matrix[i][matrixvacios[0][j]];
      predicciondenom += correlacioens[i];
    }
    float resultado = prediccionum / predicciondenom;
    cout << "resultaod" << resultado;
  }
}
void Prediccionmedia(std::vector<std::vector<int>> matrix, std::vector<float> correlacioens, std::vector<std::vector<int>> matrixvacios,
                     std::vector<float> medias)
{
  float prediccionum = 0;
  float predicciondenom = 0;
  int k = 0;
  for (int j = 0; j < matrixvacios[0].size(); j++)
  {
    cout << "iteraciones: " << j << endl;
    for (int i = 1; i < matrix.size(); i++)
    {
      prediccionum += correlacioens[i] * (matrix[i][matrixvacios[0][j]] - medias[i - 1]);
      predicciondenom += correlacioens[i];
    }
    float resultado = prediccionum / predicciondenom;
    cout << "resultaod" << resultado;
  }
}
//Diferencia con la media.
float media(std::vector<int> fila, std::vector<int> noUsar)
{
  float media = 0.0;
  float suma = 0.0;
  for (int i = 0; i < fila.size(); i++)
  {
    auto flag = std::find(noUsar.begin(), noUsar.end(), i);
    if (flag == noUsar.end())
    {
      suma += fila[i];
    }
  }
  media = suma / (fila.size() - noUsar.size());
  return media;
}
float distanciaEuclidia(std::vector<int> a, std::vector<int> b, std::vector<int> vaciosA,
                        std::vector<int> vaciosB)
{
  float sumatorio = 0;
  //calculo todos los vacios
  std::vector<int> interseccionVacios;

  if (vaciosB.size() != 0)
  {
    for (int i = 0; i < vaciosA.size(); i++)
    {
      for (int j = 0; j < vaciosB.size(); j++)
      {
        if (vaciosA[i] == vaciosB[j])
        {
          interseccionVacios.push_back(vaciosA[i]);
        }
      }
    }
  }
  else
  {
    interseccionVacios = vaciosA;
  }
  for (int i = 0; i < a.size(); i++)
  {
    auto flag = std::find(interseccionVacios.begin(), interseccionVacios.end(), i);
    if (flag == interseccionVacios.end())
      sumatorio += pow(a[i] - b[i], 2);
  }
  float resultado = sqrt(sumatorio);
  return resultado;
}
float distanciaCoseno(std::vector<int> a, std::vector<int> b, std::vector<int> vaciosA,
                      std::vector<int> vaciosB)
{
  float numerador = 0;
  float sumatorio = 0;
  float sumatorioB = 0;
  float denominador = 0;
  //calculo todos los vacios
  std::vector<int> interseccionVacios;
  if (vaciosB.size() != 0)
  {
    for (int i = 0; i < vaciosA.size(); i++)
    {
      for (int j = 0; j < vaciosB.size(); j++)
      {
        if (vaciosA[i] == vaciosB[j])
        {
          interseccionVacios.push_back(vaciosA[i]);
        }
      }
    }
  }
  else
  {
    interseccionVacios = vaciosA;
  }
  for (int i = 0; i < a.size(); i++)
  {
    auto flag = std::find(interseccionVacios.begin(), interseccionVacios.end(), i);
    if (flag == interseccionVacios.end())
    {
      numerador += (a[i]) * (b[i]);
      sumatorio += pow(a[i], 2);
      sumatorioB += pow(b[i], 2);
      denominador = sqrt(sumatorio) * sqrt(sumatorioB);
    }
  }
  float resultado = numerador / denominador;
  return resultado;
}
float pearson(std::vector<int> a, std::vector<int> b, std::vector<int> vaciosA,
              std::vector<int> vaciosB, std::vector<float> &medias)
{
  float media_A = 0.0;
  float media_B = 0.0;
  float numerador = 0;

  float sumatorio = 0;
  float sumatorioB = 0;
  //calculo todos los vacios
  std::vector<int> interseccionVacios;

  if (vaciosB.size() != 0)
  {
    for (int i = 0; i < vaciosA.size(); i++)
    {
      for (int j = 0; j < vaciosB.size(); j++)
      {
        if (vaciosA[i] == vaciosB[j])
        {
          interseccionVacios.push_back(vaciosA[i]);
        }
      }
    }
  }
  else
  {
    interseccionVacios = vaciosA;
  }

  cout << "interseccion vacios" << interseccionVacios.size() << endl;
  media_A = media(a, interseccionVacios);
  media_B = media(b, interseccionVacios);
  cout << "meddia a: " << media_A << endl;
  cout << "meddia b: " << media_B << endl;
  medias.push_back(media_B);
  for (int i = 0; i < 4; i++)
  {
    auto flag = std::find(interseccionVacios.begin(), interseccionVacios.end(), i);
    if (flag == interseccionVacios.end())
    {
      numerador += (a[i] - media_A) * (b[i] - media_B);
      sumatorio += pow(a[i] - media_A, 2);
      sumatorioB += pow(b[i] - media_B, 2);
    }
  }
  cout << "numerador : " << numerador << endl;
  cout << "sumatorio : " << sumatorio << endl;
  cout << "sumatoriob : " << sumatorioB << endl;
  float denominador = sqrt(sumatorio) * sqrt(sumatorioB);
  cout << "denominador : " << denominador << endl;
  float resultado_final = numerador / (denominador);
  cout << resultado_final;
  return resultado_final;
}
std::vector<int> calcularVacios(string str)
{
  std::vector<int> vacios;
  int j = 0;
  for (int i = 0; i < str.size(); i++)
  {
    if (str[i] == ' ')
    {
      j++;
    }
    if (str[i] == '-')
    {
      vacios.push_back(j);
    }
  }
  return vacios;
}
void chompBack(std::vector<int> &vectorfila, string &str)
{
  vectorfila.clear();
  int k = 0;
  int i = str.length() - 1;
  string cadena = "";
  while (i >= 0)
  {
    if (str[i] == '-')
    {
      vectorfila.insert(vectorfila.begin(), 0);
    }
    if (str[i] != '\t' && str[i] != '\r' && str[i] != ' ' && str[i] != '-')
    {
      cadena = cadena + str[i];
      if ((str[i - 1] == '\t' || str[i - 1] == '\r' || str[i - 1] == ' ') || i - 1 == -1)
      {
        int num;
        std::stringstream ss; //variable para hacer enteor a tring
        ss << cadena;
        ss >> num; //convertir a entero
        vectorfila.insert(vectorfila.begin(), num);
        cadena = "";
      }
    }
    i--;
  }
}
void writeMatrix(std::vector<std::vector<int>> matrix)
{
  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[i].size(); j++)
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}
int main(int argc, char *argv[])
{
  cout << "argumwntooooooooooooooooooooooooooooooooooooooooo" << argv[1] << endl;
  string filename("input.txt");
  vector<string> lines;
  string line;
  int filas = 0;

  ifstream input_file(filename);
  if (!input_file.is_open())
  {
    cerr << "Could not open the file - '"
         << filename << "'" << endl;
    return EXIT_FAILURE;
  }

  while (getline(input_file, line))
  {

    lines.push_back(line);
    filas++;
  }
  std::vector<std::vector<int>> matrix;
  std::vector<std::vector<int>> vaciosMatrix;
  /**
   * matrices con las que trabajemos definitivamente
    **/
  for (int i = 0; i < filas; i++)
  {
    std::vector<int> vectorfila; //vector de valoraciones
    std::vector<int> vacios;     // vector de vacios

    chompBack(vectorfila, lines[i]);
    matrix.push_back(vectorfila);                     //matriz de valoracios
    vaciosMatrix.push_back(calcularVacios(lines[i])); // matriz de vacios
  }
  std::vector<float> correlacion;
  std::vector<float> coseno;
  std::vector<float> euclidia;
  std::pair<string, int> x;
  std::vector<float> medias; // vector de vacios

  for (int i = 1; i < matrix.size(); i++)
  {

    correlacion.push_back(pearson(matrix[0], matrix[i], vaciosMatrix[0], vaciosMatrix[i], medias));
    //correlacion.push_back(make);
    coseno.push_back(distanciaEuclidia(matrix[0], matrix[i], vaciosMatrix[0], vaciosMatrix[i]));
    euclidia.push_back(distanciaEuclidia(matrix[0], matrix[i], vaciosMatrix[0], vaciosMatrix[i]));
  }
  //PrediccionSimple(matrix, correlacion, vaciosMatrix);
  //media
  cout << "medias: " << medias.size() << endl;
  if (argv[1] == "p")
  {
    if (argv[2] == "s")
    {

      PrediccionSimple(matrix, correlacion, vaciosMatrix);
    }
    else
      Prediccionmedia(matrix, correlacion, vaciosMatrix, medias);
  }
  ///codicion euclidia
    if (argv[1] == "e")
  {
    if (argv[2] == "s")
    {

      PrediccionSimple(matrix, correlacion, vaciosMatrix);
    }
    else
      Prediccionmedia(matrix, correlacion, vaciosMatrix, medias);
  }
  //coseno
    if (argv[1] == "c")
  {
    if (argv[2] == "s")
    {

      PrediccionSimple(matrix, correlacion, vaciosMatrix);
    }
    else
      Prediccionmedia(matrix, correlacion, vaciosMatrix, medias);
  }

  Prediccionmedia(matrix, correlacion, vaciosMatrix, medias);

  input_file.close();

  return EXIT_SUCCESS;
}
