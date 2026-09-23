#include <iostream>
#include <string>

using namespace std;

int caracterAEntero(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

char enteroACaracter(int n)
{
    if (n < 10) return char('0' + n);
    return char('A' + (n - 10));
}

double aDecimal(string numero, int base, bool &error)
{
    double resultado = 0;
    int punto = numero.find('.');

    if (punto == -1) 
        punto = (int)numero.length();

    // Parte entera
    for (int i = 0; i < punto; i++)
    {
        int digito = caracterAEntero(numero[i]);

        // Validación: revisa que el dígito sea válido y menor a la base de origen
        if (digito == -1 || digito >= base)
        {
            cout << "\n[Error] El digito '" << numero[i] << "' no es valido para la base " << base << ".\n";
            error = true;
            return 0;
        }

        resultado = resultado * base + digito;
    }

    // Parte decimal
    if (numero.find('.') != string::npos)
    {
        double potencia = base;

        for (int i = punto + 1; i < (int)numero.length(); i++)
        {
            int digito = caracterAEntero(numero[i]);

            if (digito == -1 || digito >= base)
            {
                cout << "\n[Error] El digito '" << numero[i] << "' no es valido para la base " << base << ".\n";
                error = true;
                return 0;
            }

            resultado = resultado + digito / potencia;
            potencia = potencia * base;
        }
    }

    return resultado;
}

string desdeDecimal(double numero, int base)
{
    string resultado = "";
    int entero = (int)numero;

    if (entero == 0) 
        resultado = "0";

    while (entero > 0)
    {
        int residuo = entero % base;
        resultado = enteroACaracter(residuo) + resultado;
        entero = entero / base;
    }

    double decimal = numero - (int)numero;

    if (decimal > 0.000001)
    {
        resultado += ".";
        int limite = 0;

        while (decimal > 0.000001 && limite < 8)
        {
            decimal *= base;
            int digito = (int)decimal;
            resultado += enteroACaracter(digito);
            decimal -= digito;
            limite++;
        }
    }

    return resultado;
}

int main()
{
    string numInput;
    int baseOrigen, baseDestino;
    bool huboError = false;

    cout << "=== CONVERSOR DE BASES NUMERICAS ===\n\n";

    cout << "Ingrese el numero: ";
    cin >> numInput;

    cout << "Base de origen (2-16): ";
    cin >> baseOrigen;

    cout << "Base a convertir (2-16): ";
    cin >> baseDestino;

    // Validación de rango de bases
    if (baseOrigen < 2 || baseOrigen > 16 || baseDestino < 2 || baseDestino > 16)
    {
        cout << "\n[Error] Las bases deben estar en el rango de 2 a 16.\n";
        return 0;
    }

    // Conversión a decimal
    double valorDecimal = aDecimal(numInput, baseOrigen, huboError);

    // Si encontró un dígito no válido, detiene el programa
    if (huboError) 
        return 0;

    // Conversión a la base final
    string resultadoFinal = desdeDecimal(valorDecimal, baseDestino);

    cout << "\n-----------------------------------\n";
    cout << numInput << " (base " << baseOrigen << ") = ";
    cout << resultadoFinal << " (base " << baseDestino << ")\n";
    cout << "-----------------------------------\n";

    return 0;
}