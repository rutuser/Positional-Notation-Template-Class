#include <stdio.h>
#include <iostream>
#include <fstream>

#include <vector>
#include <math.h>
#include <locale>
#include <string>

#include <exception>
#include <cerrno>

#include "NumberException.hpp"

/**
 * @file number.hpp
 *
 * @brief Class Number to represent binary, decimal and hexadecimal numbers with
 * the use of templates to generate dinamyc classes
 *
 * @ingroup PackageName
 *
 * @author Michal Ruzicka Ruzicka
 * Contact: alu0101305561@ull.edu.es
 */

//   Clase Number a partir de un template de tres parametros, B = Base, N = Logitud
//   y T = tipo de dato.
//   Declaramos la clase y sus funciones en el mismo archivo ya que en un .cpp a parte
//   la plantilla no funcionaria.

template <size_t B, size_t N, typename T = char>
class Number
{

private:
  T main_number = NULL;
  bool signo;
  void toBase(int valor);

public:
  T *v;
  Number(int valor); // Constructor
  Number();
  ~Number();

  Number<B, N, T> operator+(const Number<B, N, T> &operando);
  Number<B, N, T> operator-(const Number<B, N, T> &operando);
  Number<B, N, T> operator*(const Number<B, N, T> &operando);
  void operator=(const Number<B, N, T> &a);

  Number<B, N, T> suma(const Number<B, N, T> &sumando) const;
  Number<B, N, T> resta(const Number<B, N, T> &sumando) const;
  Number<B, N, T> producto(const Number<B, N, T> &sumando) const;

  bool get_signo() const;

  std::ostream &write(std::ostream &os) const;
  friend std::ostream &operator<<(std::ostream &, Number<B, N, T> &);
};

template <int B, int N, typename T = char>
void testNumber(int v1, int v2)
{
  Number<B, N, T> N1(v1), N2(v2);
  std::cout << "Suma: " << N1 + N2 << std::endl;
  std::cout << "Resta: " << N1 - N2 << std::endl;
  std::cout << "Producto: " << N1 * N2 << std::endl;
}

// METODOS DE CLASE

// Constructor de clase

/**
 * @param valor numero que se le pasará a toBase() para
 * ser tranformado
*/
template <size_t B, size_t N, typename T>
Number<B, N, T>::Number(int valor)
{
  try
  {
    signo = valor < 0; // 1 si es negativo, 0 si es positivo
    v = new T[N];
    if (v == NULL)
    {
      throw NumberException("Failed to reserve memory for the vector");
    }
  }
  catch (NumberException &Ne)
  {

    std::cout << "Exception catched => " << Ne.getMessage() << std::endl;
  }

  //check exception if the memory cant be reserved
  //signo = (valor[0]) ? -1 : +1;
  //Para plantillas de base 2 valor *= signo;
  //toBase(valor);

  toBase(valor);
}

template <size_t B, size_t N, typename T>
Number<B, N, T>::Number()
{
  try
  {
    v = new T[N];
    if (v == NULL)
    {
      throw NumberException("Failed to reserve memory for the vector");
    }
  }
  catch (NumberException &Ne)
  {
    std::cout << "Exception catched => " << Ne.getMessage() << std::endl;
  }
}

// Destructor de clase
template <size_t B, size_t N, typename T>
Number<B, N, T>::~Number()
{
  try
  {
    if (v != NULL)
    {
      delete[] v;
    }
    else
    {
      throw NumberException("The vector is already null");
    }
  }
  catch (NumberException &Ne)
  {
    std::cout << "Exception catched => " << Ne.getMessage() << std::endl;
  }
}

// Metodo toBase "privado". Este desglozara el numero
// segun su base y lo almacenara en nuestro vector v

/**
 * @param valor numero que se cambiará segun la base proporcionada
*/
template <size_t B, size_t N, typename T>
void Number<B, N, T>::toBase(int valor)
{
  int _valor = valor;
  valor = fabs(valor);
  try
  {
    for (int i = 0; i < N; i++)
    {
      T aux = valor % B;
      valor = valor / B;
      v[i] = aux;
    }
    if (valor > 0)
    {
      throw NumberException("Insufients bits");
    }
    for (int i = 0; i < N; i++)
    {
      main_number += v[(N - 1) - i] * pow(B, (N - 1) - i);

      //std::cout << v[(N-1)-i] << " * " << B << " ^ " << (N-1)-i << std::endl;
    }

  }
  catch (NumberException &Ne)
  {
    std::cout << "Exception catched => " << Ne.getMessage()
              << " to represent the number: " << _valor << std::endl;
  }
}

// METODOS DE OPERACION CON FUNCIONES

// Suma

/**
 * @param operando numero tipo Number
*/
template <size_t B, size_t N, typename T>
Number<B, N, T> Number<B, N, T>::suma(const Number<B, N, T> &operando) const
{
  if (signo > operando.signo)
  {
    return Number<B, N, T>(-(main_number - operando.main_number));
  }
  else if (signo < operando.signo)
  {
    return Number<B, N, T>(main_number - operando.main_number);
  }
  else
  {
    return signo ? Number<B, N, T>(-(main_number + operando.main_number))
                 : Number<B, N, T>(main_number + operando.main_number);
  }
}

// Resta

/**
 * @param operando numero tipo Number
*/
template <size_t B, size_t N, typename T>
Number<B, N, T> Number<B, N, T>::resta(const Number<B, N, T> &operando) const
{
  if (signo > operando.signo)
  {
    return Number<B, N, T>(-(main_number + operando.main_number));
  }
  else if (signo < operando.signo)
  {
    return Number<B, N, T>(main_number + operando.main_number);
  }
  else
  {
    return signo ? Number<B, N, T>(-(main_number - operando.main_number))
                 : Number<B, N, T>(main_number - operando.main_number);
  }
}

// Producto

/**
 * @param operando numero tipo Number
*/
template <size_t B, size_t N, typename T>
Number<B, N, T> Number<B, N, T>::producto(const Number<B, N, T> &operando) const
{
  if (signo == operando.signo)
  {
    return Number<B, N, T>(main_number * operando.main_number);
  }
  else
  {
    return Number<B, N, T>(-(main_number * operando.main_number));
  }
}

// METODOS DE OPERACION CON SOBRECARGA DE OPERADORES

// Suma

/**
 # @overload Number<B, N, T> Number<B, N, T>::operator+(const Number<B, N, T> &operando)
 * @param operando numero de tipo Number
 */
template <size_t B, size_t N, typename T>
Number<B, N, T> Number<B, N, T>::operator+(const Number<B, N, T> &operando)
{
  if (signo > operando.signo)
  {
    return Number<B, N, T>(-(main_number - operando.main_number));
  }
  else if (signo < operando.signo)
  {
    return Number<B, N, T>(main_number - operando.main_number);
  }
  else
  {
    return signo ? Number<B, N, T>(-(main_number + operando.main_number))
                 : Number<B, N, T>(main_number + operando.main_number);
  }
}

// Resta

/**
 # @overload Number<B, N, T> Number<B, N, T>::operator-(const Number<B, N, T> &operando)
 * @param operando numero de tipo Number
 */
template <size_t B, size_t N, typename T>
Number<B, N, T> Number<B, N, T>::operator-(const Number<B, N, T> &operando)
{
  if (signo > operando.signo)
  {
    return Number<B, N, T>(-(main_number + operando.main_number));
  }
  else if (signo < operando.signo)
  {
    return Number<B, N, T>(main_number + operando.main_number);
  }
  else
  {
    return signo ? Number<B, N, T>(-(main_number - operando.main_number))
                 : Number<B, N, T>(main_number - operando.main_number);
  }
}

// Producto

/**
 # @overload Number<B, N, T> Number<B, N, T>::operator*(const Number<B, N, T> &operando)
 * @param operando numero de tipo Number
 */
template <size_t B, size_t N, typename T>
Number<B, N, T> Number<B, N, T>::operator*(const Number<B, N, T> &operando)
{
  if (signo == operando.signo)
  {
    return Number<B, N, T>(main_number * operando.main_number);
  }
  else
  {
    return Number<B, N, T>(-(main_number * operando.main_number));
  }
}

template <size_t B, size_t N, typename T>
bool Number<B, N, T>::get_signo() const
{
  return signo;
}

// Contructor copia

/**
 # @overload Number<B, N, T> Number<B, N, T>::operator=(const Number<B, N, T> &a)
 * @param a numero de tipo Number
 */

template <size_t B, size_t N, typename T>
void Number<B, N, T>::operator=(const Number<B, N, T> &a)
{
  for (int i = 0; i < N; i++)
  {
    v[i] = a.v[i];
  }
}

// FLUJO DE SALIDA

// Por metodo de clase

/**
 # @overload Number<B, N, T> Number<B, N, T>::operator*(const Number<B, N, T> &operando)
 *
 * @param os variable para formato de flujo de salida
 */
template <size_t B, size_t N, typename T>
std::ostream &Number<B, N, T>::write(std::ostream &os) const
{
  if (B == 16)
  {
    os << (signo ? "-" : "+");
    for (int i = 0; i < N; i++)
    {
      os << std::uppercase << std::hex << v[(N - 1) - i]; //std::hex para convertir en hexadecimal
    }
    os << std::dec << " [" << B << "]" << std::endl; //std::dec para convertir en decimal
  }
  else
  {
    os << (signo ? "-" : "+");
    for (int i = 0; i < N; i++)
    {
      os << v[(N - 1) - i];
    }
    os << " [" << B << "]" << std::endl;
  }
  return os;
}

// Por sobrecarga de operadores

/**
 # @overload std::ostream &operator<<(std::ostream &os, const Number<B, N, T> &class_number)
 *
 * @param os variable para formato de flujo de salida
 *
 * @param class_number indica el clase de tipo Number para insertar en el flujo de salida
 */
template <size_t B, size_t N, typename T>
std::ostream &operator<<(std::ostream &os, const Number<B, N, T> &class_number)
{
  bool n_signo = class_number.get_signo();

  if (B == 16)
  {
    os << (n_signo ? "-" : "+");
    for (int i = 0; i < N; i++)
    {
      os << std::uppercase << std::hex << class_number.v[(N - 1) - i]; //std::hex para convertir en hexadecimal
    }
    os << std::dec << " [" << B << "]" << std::endl; //std::dec para convertir en decimal
    os << std::endl;
  }
  else
  {
    os << (n_signo ? "-" : "+");
    for (int i = 0; i < N; i++)
    {
      os << class_number.v[(N - 1) - i];
    }
    os << " [" << B << "]" << std::endl;
    os << std::endl;
  }
  return os;
}


// Especializacion de la plantilla para numeros binarios

template<size_t N, typename T>
class Number <2, N, T>
{
  private:
    T main_number = NULL;
    void toBase(int valor);

  public:
    T *v;
    Number(int valor); // Constructor
    Number();
    ~Number();

    Number<2, N, T> operator+(const Number<2, N, T> &operando);
    Number<2, N, T> operator-(const Number<2, N, T> &operando);
    Number<2, N, T> operator*(const Number<2, N, T> &operando);
    void operator=(const Number<2, N, T> &a);

    Number<2, N, T> suma(const Number<2, N, T> &sumando) const;
    Number<2, N, T> resta(const Number<2, N, T> &sumando) const;
    Number<2, N, T> producto(const Number<2, N, T> &sumando) const;

    bool get_signo() const;
    void set_inverse();

    std::ostream &write(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &, Number<2, N, T> &);
};

// METODOS DE CLASE

// Constructor de clase

/**
 * @param valor numero que se le pasará a toBase() para
 * ser tranformado
*/
template <size_t N, typename T>
Number<2, N, T>::Number(int valor)
{
  try
  {
    v = new T[N];
    if (v == NULL)
    {
      throw NumberException("Failed to reserve memory for the vector");
    }
  }
  catch (NumberException &Ne)
  {

    std::cout << "Exception catched => " << Ne.getMessage() << std::endl;
  }

  //check exception if the memory cant be reserved
  //signo = (valor[0]) ? -1 : +1;
  //Para plantillas de base 2 valor *= signo;
  //toBase(valor);

  toBase(valor);
}

template <size_t N, typename T>
Number<2, N, T>::Number()
{
  try
  {
    v = new T[N];
    if (v == NULL)
    {
      throw NumberException("Failed to reserve memory for the vector");
    }
  }
  catch (NumberException &Ne)
  {
    std::cout << "Exception catched => " << Ne.getMessage() << std::endl;
  }
}

// Destructor de clase
template <size_t N, typename T>
Number<2, N, T>::~Number()
{
  try
  {
    if (v != NULL)
    {
      delete[] v;
    }
    else
    {
      throw NumberException("The vector is already null");
    }
  }
  catch (NumberException &Ne)
  {
    std::cout << "Exception catched => " << Ne.getMessage() << std::endl;
  }
}

// Metodo toBase "privado". Este desglozara el numero
// segun su base y lo almacenara en nuestro vector v

/**
 * @param valor numero que se cambiará segun la base proporcionada
*/
template <size_t N, typename T>
void Number<2, N, T>::toBase(int valor)
{
  int _valor = valor;
  valor = fabs(valor);
  try
  {
    for (int i = 0; i < N; i++)
    {
      T aux = valor % 2;
      valor = valor / 2;
      v[i] = aux;
    }
    if (valor > 0)
    {
      throw NumberException("Insufients bits");
    }

    for (int i = 0; i < N; i++)
    {
      main_number += v[(N - 1) - i] * pow(2, (N - 1) - i);

      //std::cout << v[(N-1)-i] << " * " << B << " ^ " << (N-1)-i << std::endl;

    }

  }
  catch (NumberException &Ne)
  {
    std::cout << "Exception catched => " << Ne.getMessage()
              << " to represent the number: " << _valor << std::endl;
  }
}
 template <size_t N, typename T>
 void Number<2, N, T>::set_inverse()
	{
		for(int i = 0; i < N; i++)
      v[i] = 1 - v[i];
    
	}


// METODOS DE OPERACION CON SOBRECARGA DE OPERADORES

// Suma

/**
 # @overload Number<B, N, T> Number<B, N, T>::operator+(const Number<B, N, T> &operando)
 * @param operando numero de tipo Number
 */
template <size_t N, typename T>
Number<2, N, T> Number<2, N, T>::operator+(const Number<2, N, T> &operando)
{
  return Number<2, N, T>(main_number + operando.main_number);
}

// FLUJO DE SALIDA

// Por metodo de clase

/**
 # @overload Number<B, N, T> Number<B, N, T>::operator*(const Number<B, N, T> &operando)
 *
 * @param os variable para formato de flujo de salida
 */
template <size_t N, typename T>
std::ostream &Number<2, N, T>::write(std::ostream &os) const
{
    for (int i = 0; i < N; i++)
    {
      os << v[(N - 1) - i];
    }
    os << " [" << 2 << "]" << std::endl;

  return os;
}

// Por sobrecarga de operadores

/**
 # @overload std::ostream &operator<<(std::ostream &os, const Number<B, N, T> &class_number)
 *
 * @param os variable para formato de flujo de salida
 *
 * @param class_number indica el clase de tipo Number para insertar en el flujo de salida
 */
template <size_t N, typename T>
std::ostream &operator<<(std::ostream &os, const Number<2, N, T> &class_number)
{
  //bool n_signo = class_number.get_signo();
    for (int i = 0; i < N; i++)
    {
      os << class_number.v[(N - 1) - i];
    }
    os << " [" << 2 << "]" << std::endl;
    os << std::endl;

  return os;
}