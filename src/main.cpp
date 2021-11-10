#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <Matrix.h>

void suma();
void multiplicar_dos_matrices();
void multiplicar_con_escalar();
void determinante();
void matriz_transpuesta();
void matriz_adjunta();
void matriz_invesa();
unsigned long get_unsigned();
double get_double();

int main() {
	std::cout << "Operaciones con matrices" << std::endl;
	unsigned long option;
	do {
		std::cout << "Opciones" << std::endl;
		std::cout << "[1] - Sumar dos Matrices" << std::endl;
		std::cout << "[2] - Multiplicar dos Matrices" << std::endl;
		std::cout << "[3] - Multiplicar una matriz con un escalar" << std::endl;
		std::cout << "[4] - Determinante de una matriz" << std::endl;
		std::cout << "[5] - Obtener la matriz transpuesta" << std::endl;
		std::cout << "[6] - Obtener la matriz adjunta" << std::endl;
		std::cout << "[7] - Obtener la matriz inversa" << std::endl;
		std::cout << "[8] - Salir" << std::endl;

		std::cout << "opcion? ";
		option = get_unsigned();

		switch (option) {
			case 1: suma(); break;
			case 2: multiplicar_dos_matrices(); break;
			case 3: multiplicar_con_escalar(); break;
			case 4: determinante(); break;
			case 5: matriz_transpuesta(); break;
			case 6: matriz_adjunta(); break;
			case 7: matriz_invesa(); break;
			case 8: break;
			default: std::cout << "Escribe un numero entre 1-8" << std::endl;
		}
	} while(option != 8);
}

void suma() {
	unsigned rows, columns;
	std::cout << "Orden de las matrices:" << std::endl;
	std::cout << "filas? ";
	rows = static_cast<unsigned>(get_unsigned());
	std::cout << "columnas? ";
	columns = static_cast<unsigned>(get_unsigned());

	Matrix a(rows, columns);
	Matrix b(rows, columns);

	std::cout << "Ingresa los datos de la primer matriz:" << std::endl;
	std::cin >> a;
	std::cout << "Ingresa los datos de la segunda matriz:" << std::endl;
	std::cin >> b;
	std::cout << "\nResultado\n" << std::endl;
	std::cout << (a + b) << std::endl;
}
void multiplicar_dos_matrices() {
	unsigned m,n,p;
	std::cout << "Orden de la primer matriz." << std::endl;
	std::cout << "filas? ";
	m = static_cast<unsigned>(get_unsigned());
	std::cout << "columnas? ";
	n = static_cast<unsigned>(get_unsigned());
	Matrix a(m, n);
	
	std::cout << "Orden de la segunda matriz." << std::endl;
	std::cout << "columnas? ";
	p = static_cast<unsigned>(get_unsigned());
	Matrix b(n, p);

	std::cout << "Ingresa los datos de la primer matriz:" << std::endl;
	std::cin >> a;
	std::cout << "Ingresa los datos de la segunda matriz:" << std::endl;
	std::cin >> b;
	std::cout << "\nResultado\n" << std::endl;
	std::cout << (a * b) << std::endl;
}
void multiplicar_con_escalar() {
	unsigned m,n;
	double escalar;
	std::cout << "Orden de la matriz." << std::endl;
	std::cout << "filas? ";
	m = static_cast<unsigned>(get_unsigned());
	std::cout << "columnas? ";
	n = static_cast<unsigned>(get_unsigned());
	Matrix a(m, n);

	std::cout << "escalar?";
	escalar = get_double();

	std::cout << "Ingresa los datos para la matriz" << std::endl;
	std::cin >> a;
	std::cout << "\nResultado\n" << std::endl;
	std::cout << (a * escalar) << std::endl;
}
void determinante() {
	unsigned n;
	std::cout << "Orden de la matriz" << std::endl;
	std::cout << "filas? ";
	n = static_cast<unsigned>(get_unsigned());
	Matrix a(n, n);

	std::cout << "Ingresa los datos para la matriz" << std::endl;
	std::cin >> a;
	std::cout << "Determinante = " << a.determinant() << std::endl;
}
void matriz_transpuesta() {
	unsigned m,n;
	std::cout << "Orden de la matriz" << std::endl;
	std::cout << "filas? ";
	m = static_cast<unsigned>(get_unsigned());
	std::cout << "columnas? ";
	n = static_cast<unsigned>(get_unsigned());
	Matrix a(m, n);

	std::cout << "Ingresa los datos para la matriz" << std::endl;
	std::cin >> a;
	std::cout << "\nMatriz transpuesta\n" << std::endl;
	a.transposed();
	std::cout << a << std::endl;
}
void matriz_adjunta() {
	unsigned n;
	std::cout << "Orden de la matriz" << std::endl;
	std::cout << "filas? ";
	n = static_cast<unsigned>(get_unsigned());
	Matrix a(n, n);

	std::cout << "Ingresa los datos para la matriz" << std::endl;
	std::cin >> a;
	std::cout << "\nMatriz adjunta\n" << std::endl;
	std::cout << a.adjunta() << std::endl;
}
void matriz_invesa() {
	unsigned n;
	std::cout << "Orden de la matriz" << std::endl;
	std::cout << "filas? ";
	n = static_cast<unsigned>(get_unsigned());
	Matrix a(n, n);

	std::cout << "Ingresa los datos para la matriz" << std::endl;
	std::cin >> a;
	std::cout << "\nMatriz inversa\n" << std::endl;
	std::cout << a.inverse() << std::endl;
}

unsigned long get_unsigned() {
	std::string str_input;
	bool is_incorrect = true;
	unsigned long value;
	do {
		std::cin >> str_input;
		try {
			value = std::stoul(str_input);
			if (value == 0)
				std::cout << "?";
			else
				is_incorrect = false;
		} catch(const std::invalid_argument &e) {
			std::cout << "ingresa solo numeros\n?";
		} catch(const std::out_of_range &e) {
			std::cout << "numero demasiado grande para almacenar\n?";
		}
	} while(is_incorrect);
	return value;
}
double get_double() {
	std::string str_input;
	bool is_incorrect = true;
	double value;
	do {
		std::cin >> str_input;
		try {
			value = std::stod(str_input);
			is_incorrect = false;
		} catch(const std::invalid_argument &e) {
			std::cout << "ingresa solo numeros\n?";
		} catch(const std::out_of_range &e) {
			std::cout << "numero demasiado grande para almacenar\n?";
		}
	} while(is_incorrect);
	return value;
}