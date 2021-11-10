#include <iostream>
#include <stdexcept>
#include <Matrix.h>
#include <string>
#include <cmath>

Matrix::Matrix(unsigned rows, unsigned columns)
   : data(nullptr)
{
   // Validation inputs
   if (rows == 0)
      throw std::invalid_argument("Rows must be greater than zero");
   if (columns == 0)
      throw std::invalid_argument("Columns must be greater than zero");

   this->rows = rows;
   this->columns = columns;

   // Asigning dinamic memory
   const unsigned elements = get_elements();
   data = new double[elements];

   // Initialization matrix with zero
   for (unsigned i = 0; i < elements; i++)
      data[i] = 0;
}

Matrix::~Matrix() { delete[] data; }

// Constructro de copia
Matrix::Matrix(const Matrix &m_copy)
   : data(nullptr), rows(m_copy.rows), columns(m_copy.columns)
{
   // Asigning dinamic memory to matrix
   const unsigned elements = get_elements();
   data = new double[elements];

   for (unsigned i = 0; i < elements; i++)
      data[i] = m_copy.data[i];
}

// Sobrecarga del operador de asignación
const Matrix &Matrix::operator=(const Matrix &m_right)
{
   // No permite la autoasignacion
   if (&m_right != this)
   {
      // Desasignar la memoria de esta matriz.
      delete[] data;

      /**
       * Asignar la memora necesaria para almacenar
       * los nuevos datos
      */
      const unsigned elements = m_right.get_elements();
      data = new double[elements];

      // Copiando datos
      for (unsigned i = 0; i < elements; i++)
         data[i] = m_right.data[i];
   }

   return *this;
}

unsigned Matrix::get_rows() const { return rows; }
unsigned Matrix::get_columns() const { return columns; }
unsigned Matrix::get_elements() const { return rows * columns; }
double Matrix::get_elmentij(const unsigned i, const unsigned j) const
{
   if (i >= rows || j >= columns)
      throw std::out_of_range("Fuera de rango");
   return data[i * columns + j];
}
void Matrix::set_elementij(const unsigned i, const unsigned j, double value)
{
   if (i >= rows || j >= columns)
      throw std::out_of_range("Fuera de rango");
   data[i * columns + j] = value;
}

/**
 * Sobrecarga el operador +
 * Recive: Una referencia del tipo Matriz, debe ser del mismo
 *   orden que esta matriz.
 * Devuelve: Una instancia de Matriz del mismo orden que
 *  las matrices sumadas
*/
Matrix Matrix::operator+(const Matrix &m_right) const
{
   if (!((rows == m_right.rows) && (columns == m_right.columns)))
      throw std::domain_error("Las matrices deben ser del mismo orden");

   // Crear una matriz para guardar la suma
   Matrix m_sum(rows, columns);

   // Sumando
   const unsigned elements = m_sum.get_elements();
   for (unsigned i = 0; i < elements; i++)
      m_sum.data[i] = data[i] + m_right.data[i];

   return m_sum;
}

/**
 * Sobrecarga del operador * para Matrix * Matrix
 * Recive: Una referencia del tipo Matriz, solo permite
 *   la multiplicacion de matrices de orden ( [m,n] * [n,p] )
 * Devuelve: Una instancia del tipo Matrix
*/
Matrix Matrix::operator*(const Matrix &m_right) const
{
   if (columns != m_right.rows)
      throw std::domain_error(
          "La matriz derecha debe ser de orden [" + std::to_string(columns) + "x" + std::to_string(m_right.columns) + "]");

   // Crea una Matriz para almacenar el resultado
   Matrix m_result(rows, m_right.columns);

   // Multiplicando
   const unsigned common_number = columns;
   for (unsigned i = 0; i < m_result.rows; i++)
   {
      for (unsigned j = 0; j < m_result.columns; j++)
      {
         double cij = 0.0;
         for (unsigned n = 0; n < common_number; n++)
         {
            cij += this->get_elmentij(i, n) * m_right.get_elmentij(n, j);
         }
         m_result.set_elementij(i, j, cij);
      }
   }

   return m_result;
}

/**
 * Sobrecarga del operador * para Matrix * double
*/
Matrix Matrix::operator*(double escalar) const
{
   Matrix result(rows, columns);

   const unsigned elements = result.get_elements();
   for (unsigned e = 0; e < elements; ++e)
   {
      result.data[e] = data[e] * escalar;
   }

   return result;
}
/**
 * Sobrecarga del operador * para double * Matrix
*/
Matrix operator*(double escalar, const Matrix &m)
{
   return m.operator*(escalar);
}

void Matrix::transposed()
{
   // Intercambia fila y columna
   {
      const unsigned tem = rows;
      rows = columns;
      columns = tem;
   }

   //> No mueve los datos si es una Matriz fila o columna
   if ((rows != 1) && (columns != 1))
   {
      // Crea una copia temporal de la Matriz original
      Matrix m_tem(*this);

      // Intercambiando datos
      for (unsigned int i = 0; i < rows; i++)
      {
         for (unsigned int j = 0; j < columns; j++)
         {
            set_elementij(i, j, m_tem.get_elmentij(j, i));
         }
      }
   }
}

Matrix Matrix::adjunta() const
{
   if (rows != columns)
      throw std::domain_error("Debe ser una matriz cuadratica");

   Matrix adjunta(rows, columns);

   if (rows == 1)
      return adjunta;

   // Llenar la matriz adjunta con cofactores
   for (unsigned int i = 0; i < adjunta.rows; i++)
   {
      for (unsigned int j = 0; j < adjunta.columns; j++)
      {
         adjunta.set_elementij(i, j, get_cofactorij(i, j, *this));
      }
   }

   return adjunta;
}

/**
 * Calcular la determinante de la matrix,
 * solo para matrices cuadraticas.
*/
double Matrix::determinant() const
{
   if (rows != columns)
      throw std::domain_error("Debe ser una matriz cuadratica");

   if (rows == 1)
      return data[0];
   if (rows == 2)
   {
      double determinant = data[0] * data[3] - data[2] * data[1];
      return determinant;
   }

   // Calcular la determinante por el metodo de la Laplace
   double determinant = 0.0;
   for (unsigned j = 0; j < columns; j++)
   {
      determinant += data[j] * get_cofactorij(0, j, *this);
   }

   return determinant;
}

/**
 * Debe ser llamado con rangos validos y una matriz cuadratica de orden mayor a uno,
 * NO pasar matriz de orden uno.
 * No realiza ninguna validación.
*/
double Matrix::get_cofactorij(unsigned i, unsigned j, const Matrix &m)
{
   int signo = static_cast<int>(std::pow(-1, i + j + 2));

   // Obtener la matriz menor
   Matrix menor(m.rows - 1, m.columns - 1);
   for (unsigned m_i = 0, menor_i = 0; m_i < m.rows; m_i++)
   {
      if (m_i == i)
         continue;
      for (unsigned m_j = 0, menor_j = 0; m_j < m.columns; m_j++)
      {
         if (m_j == j)
            continue;
         menor.set_elementij(menor_i, menor_j, m.get_elmentij(m_i, m_j));
         menor_j++;
      }
      menor_i++;
   }

   // Calcular cofactor segun caso
   double determinant_menor = 0.0;
   switch (menor.rows)
   {
   case 1:
      determinant_menor = menor.data[0];
      break;
   case 2:
      determinant_menor = menor.data[0] * menor.data[3] - menor.data[2] * menor.data[1];
      break;
   default:
      for (unsigned j = 0; j < menor.columns; j++)
      {
         determinant_menor += menor.data[j] * get_cofactorij(0, j, menor);
      }
   }
   return signo * determinant_menor;
}

/**
 * Devuelve la matriz inversa de esta matriz (solo una cuadratica),
 * si es que lo tiene.
*/
Matrix Matrix::inverse()
{
   if (rows != columns)
      throw std::domain_error("Debe ser una matriz cuadratica");

   Matrix adjunta = this->adjunta();
   /**
    * Calcular la determinante a partir de la adjunta para
    * ahorar tiempo de ejecutión
   */
   double determinant = 0.0;
   for (unsigned j = 0; j < adjunta.columns; j++)
   {
      determinant += data[j] * adjunta.data[j];
   }

   if (determinant == 0.0)
      throw std::domain_error("No tiene inversa. Determinante 0");

   // Convertirlo en transpuesta
   adjunta.transposed();
   return adjunta * (1 / determinant);
}

std::istream &operator>>(std::istream &input, const Matrix &m)
{
   bool is_incorrect;
   std::string str_input;
   for (unsigned i = 0; i < m.rows; i++)
   {
      std::cout << "fila[" << (i + 1) << "] -> {";
      for (unsigned j = 0; j < m.columns; j++)
      {
         is_incorrect = true;
         do
         {
            std::cin >> str_input;
            try
            {
               m.data[i * m.columns + j] = std::stod(str_input);
               is_incorrect = false;
            }
            catch (const std::invalid_argument &e)
            {
               std::cout << "[" << (i + 1) << ", " << (j + 1) << "] -> ";
            }
            catch (const std::out_of_range &e)
            {
               std::cout << "[" << (i + 1) << ", " << (j + 1) << "] -> ";
            }
         } while (is_incorrect);
      }
   }
   return input;
}

std::ostream &operator<<(std::ostream &output, const Matrix &m)
{
   std::ios_base::fmtflags format = output.flags();
   output.precision(2);
   output << std::fixed;

   for (unsigned r = 0; r < m.rows; r++)
   {
      output << "|";
      for (unsigned c = 0; c < m.columns; c++)
         output << m.data[r * m.columns + c] << ' ';
      output << "|";
      output << std::endl;
   }

   // Restaura el formato
   output.flags(format);
   return output;
}