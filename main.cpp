#include <stdio.h>
#include <iostream>

#include <cerrno>
#include <exception>

#include "number.hpp"
/**
 * @file main.hpp
 *
 * @brief main file program
 *
 * @ingroup PackageName
 *
 * @author Michal Ruzicka Ruzicka
 * Contact: alu0101305561@ull.edu.es
 */

int main(int argc, char *argv[])
{
    try
    {
        //Prueba con hexadecimales
        Number<16, 2, int> n_hx1(16);
        Number<16, 2, int> n_hx2(15);

        std::cout << "Numero hexadecimal1:  ";
        n_hx1.write(std::cout);
        std::cout << "Numero hexadecimal2:  ";
        n_hx2.write(std::cout);
        std::cout << std::endl;

        std::cout << "Suma de numeros decimales: ";
        std::cout << n_hx1 + n_hx2;

        std::cout << "Resta de numeros decimales: ";
        std::cout << n_hx1 - n_hx2;

        std::cout << "Producto de numeros decimales: ";
        std::cout << n_hx1 * n_hx2;

        
        // Prueba con binarios
        Number<2, 4, int> n_bn1(5);
        Number<2, 4, int> n_bn2(5);

        std::cout << "Numero binario1:  ";
        n_bn1.write(std::cout);
        std::cout << "Numero binario2:  ";
        n_bn2.write(std::cout);
        std::cout << std::endl;

        std::cout << "Suma de numeros binarios: ";
        std::cout << n_bn1 + n_bn2;
/*
        std::cout << "Resta de numeros binarios: ";
        std::cout << n_bn1 - n_bn2;
        

        // Prueba con decimales
        
        Number<10, 2, int> n_dc1(5);
        Number<10, 2, int> n_dc2(-6);

        std::cout << "Numero decimal1:  ";
        n_dc1.write(std::cout);
        std::cout << "Numero decimal2:  ";
        n_dc2.write(std::cout);
        std::cout << std::endl;

        std::cout << "Suma de numeros decimales: ";
        std::cout << n_dc1 + n_dc2;

        std::cout << "Resta de numeros decimales: ";
        std::cout << n_dc1 - n_dc2;

        std::cout << "Producto de numeros decimales: ";
        std::cout << n_dc1 * n_dc2;
        
        std::cout << "Probando contructor copia: " << std::endl;
        Number <2, 5, int> a;
        a = n_bn1;
        std::cout << "Copia del numero ";
        a.write(std::cout); */
        
    }
    catch (const std::system_error &e)
    {
        std::cerr << e.what() << '\n';
    }
}
