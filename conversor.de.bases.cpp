#include <iostream>
#include <string>

using namespace std;

// Convierte un carácter en su valor numérico
int valor(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return -1;
}


// Convierte un valor numérico en carácter
char caracter(int n)
{
    if (n < 10)
        return char('0' + n);

    return char('A' + (n - 10));
}


// Convierte el número de la base original a decimal
double aDecimal(string numero, int base)
{
    double resultado = 0;

    // Busca la posición del punto decimal
    int punto = numero.find('.');

    if (punto == -1)
        punto = (int)numero.length();


    // Convierte la parte entera
    for (int i = 0; i < punto; i++)
    {
        int digito = valor(numero[i]);

        resultado = resultado * base + digito;
    }


    // Convierte la parte decimal
    if (numero.find('.') != string::npos)
    {
        double potencia = base;

        for (int i = punto + 1; i < (int)numero.length(); i++)
        {
            int digito = valor(numero[i]);

            resultado = resultado + digito / potencia;
            potencia = potencia * base;
        }
    }

    return resultado;
}


// Convierte un número decimal a la base elegida
string desdeDecimal(double numero, int base)
{
    string resultado = "";

    int entero = (int)numero;

    if (entero == 0)
        resultado = "0";


    // Convierte la parte entera mediante divisiones sucesivas
    while (entero > 0)
    {
        int residuo = entero % base;

        resultado = caracter(residuo) + resultado;

        entero = entero / base;
    }


    // Convierte la parte decimal mediante multiplicaciones sucesivas
    double decimal = numero - (int)numero;

    if (decimal > 0.000001)
    {
        resultado = resultado + ".";

        int contador = 0;

        // Limita la cantidad de cifras decimales a 10
        while (decimal > 0.000001 && contador < 10)
        {
            decimal = decimal * base;

            int digito = (int)decimal;

            resultado = resultado + caracter(digito);

            decimal = decimal - digito;

            contador++;
        }
    }

    return resultado;
}


int main()
{
    string numero;
    int baseOrigen, baseDestino;
    double decimal;

    cout << "*************************************\n";
    cout << "       CONVERSOR DE BASES\n";
    cout << "*************************************\n";

    cout << "\nEste programa permite convertir numeros\n";
    cout << "entre bases desde 2 hasta 16.\n";
    cout << "Tambien permite numeros con decimales.\n";

    cout << "\nIngrese el numero: ";
    cin >> numero;

    cout << "Ingrese la base de origen (2 - 16): ";
    cin >> baseOrigen;

    cout << "Ingrese la base de destino (2 - 16): ";
    cin >> baseDestino;


    // Comprueba que las bases estén dentro del límite permitido
    if (baseOrigen < 2 || baseOrigen > 16 ||
        baseDestino < 2 || baseDestino > 16)
    {
        cout << "\n*************************************\n";
        cout << "ERROR: Las bases deben estar entre 2 y 16.\n";
        cout << "*************************************\n";

        return 0;
    }


    // Primero convierte el número a decimal
    decimal = aDecimal(numero, baseOrigen);

    // Después convierte el decimal a la base elegida
    string resultado = desdeDecimal(decimal, baseDestino);


    cout << "\n*************************************\n";
    cout << "Resultado:\n";
    cout << numero << " (base " << baseOrigen << ") -> ";
    cout << resultado << " (base " << baseDestino << ")\n";
    cout << "*************************************\n";

    return 0;
}

