# gco

~~~ c++
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
~~~
Metodo en el cual calculamos la prediccion simple recorriendo los numeros que tienen la misma posicion que la que queremos calcular

~~~ c++
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
~~~
Metodo igual que el anterior pero añadiendo la variante media
~~~ c++
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
~~~
Metodo para calcular la media en el que le pasamos las posiciones que no tiene que usar para calcularla ya que no la sabemos.
~~~c++
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
~~~
Calculamos la distancia euclidia aplicando la formula sin utilizar las posiciones de los elemtnos que no se pueden.
~~~c++
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
~~~
Metodo en el que calculamos la distancia coseno  sin utilizar las posiciones de los elemtnos que no se pueden.
~~~
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
~~~
metodo en el cual calculamos pearson sin utilizar los elemtnos que no se pueden
~~~c++
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
~~~
Metodo en el que calculamos las posiciones de las que no tenemos datos y las guardamos en un vector.
~~~c++
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
~~~
metodo en el cual converitimos la cadena a entero y metemos un 0 donde encontremos g - . Esto no nos supone un problema ya que guardamos la poscion donde esta el guion para que no se realize ninguna operacion con el. Es lo que hacemos en el metodo anterior.
~~~c++
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
~~~
Metodo para imprimir una matriz
~~~c++
int main(int argc, char *argv[])
{
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
  for (int i = 0; i < matrix.size(); i++)
  {
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

std::swap(matrix[0], matrix[i]);
std::swap(vaciosMatrix[0], vaciosMatrix[i]);
  
  }
  writeMatrix(matrix);

  
  input_file.close();

  return EXIT_SUCCESS;
}
~~~ 
En el main basicamente leemos el fichero y llamamos a las distintas funcionalidades implementadas dependiendo de los argumentos que pasemos. Las incognitas solo se calculan en la priemra fila por lo que hay dos swap abajo para que cubran toda la matriz el problema es que los usuarios no salen en el mismo orden pero los datos corresponden a los mimos. Si se quiere comprobar solo comentar los dos swap y ver que la primera fila se realiza de manera correcta.

##Metodo de ejecucion:
compilamos el archivo:
g++ -std=c++11 lectura.cpp -o lectura
ejecutamos con las opciones p e o c dependiendo de lo que queramos es decir: pearson,coseno, euclidia y en la segundo opcion ponemos simple o media con s o m. un ejemplo seria el siguiente
./lectura p m
