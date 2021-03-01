#include <iostream>;
#include "Matrix.h";

using namespace std;

// вывод 2х матриц
void output_bouth_matrix(const Matrix& m1, const Matrix& m2) {
	cout << "\nМатрица №1\n";
	m1.output_matrix();

	cout << "\nМатрица №2\n\n";
	m2.output_matrix();
}

// изменение параметра, который задает единый размер матриц
void change_resize_param(int& param, const pair<int, int>& size_of_mat1, const pair<int, int>& size_of_mat2) {
	while (param < size_of_mat1.first || param < size_of_mat1.second ||
		param < size_of_mat2.first || param < size_of_mat2.second)
		param *= 2;
}

int main() {
	srand(time(NULL));
	system("chcp 65001");
	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";


	int n1, m1, n2, m2;			// переменные для создания матриц (строки и столбцы)
	int manual_or_auto;			// выбор варианта заполнения матриц
	int resize_param = 2;		// параметр для приведения матриц к требуемому размеру

	// ввод данных для создания матриц
	do
	{
		cout << "Введите размеры первой матрицы\n";
		cin >> n1 >> m1;
	} while (n1 <= 0 || m1 <= 0);
	do
	{
		cout << "Введите размеры второй матрицы\n";
		cin >> n2 >> m2;
	} while (n2 <= 0 || m2 <= 0);

	Matrix first_matrix(n1, m1);
	Matrix second_matrix(n2, m2);

	// заполнение матриц
	do {
		cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> manual_or_auto;
	} while (manual_or_auto < 1 || manual_or_auto > 2);

	if (manual_or_auto == 1) {
		cout << "Введите данные матрицы №1:\n";
		first_matrix.creating_matrix_manually();
		cout << "Введите данные матрицы №2:\n";
		second_matrix.creating_matrix_manually();

		output_bouth_matrix(first_matrix, second_matrix);
	}
	else if (manual_or_auto == 2) {
		first_matrix.creating_matrix_automatically();
		second_matrix.creating_matrix_automatically();

		output_bouth_matrix(first_matrix, second_matrix);
	}

	// изменение параметра для приведения матриц
	change_resize_param(resize_param, first_matrix.size(), second_matrix.size());
	// создание приведеных к требуемому размеру матриц
	Matrix resized_first_matrix(resize_param, resize_param);
	Matrix resized_second_matrix(resize_param, resize_param);

	resized_first_matrix.fill_matrix_zero();
	resized_second_matrix.fill_matrix_zero();

	resized_first_matrix.set_data_for_smaller_matrix(first_matrix);
	resized_second_matrix.set_data_for_smaller_matrix(second_matrix);

	cout << "Приведенные матрицы\n";
	output_bouth_matrix(resized_first_matrix, resized_second_matrix);


	// данные для разделения матрицы на 4 секции
	pair<int, int> section_one{ 0, 0 };
	pair<int, int> section_two{ 0, resize_param / 2 };
	pair<int, int> section_three{ resize_param / 2, 0 };
	pair<int, int> section_four{ resize_param / 2, resize_param / 2 };

	// 4 матрицы, на которые была поделена 1я исходная матрица
	Matrix first_matrix_1_1(Matrix::splitting_matrix_by_quarters(first_matrix, section_one));		//mat1
	Matrix first_matrix_1_2(Matrix::splitting_matrix_by_quarters(first_matrix, section_two));		//mat2
	Matrix first_matrix_2_1(Matrix::splitting_matrix_by_quarters(first_matrix, section_three));		//mat3
	Matrix first_matrix_2_2(Matrix::splitting_matrix_by_quarters(first_matrix, section_four));		//mat4

	// 4 матрицы, на которые была поделена 2я исходная матрица
	Matrix second_matrix_1_1(Matrix::splitting_matrix_by_quarters(second_matrix, section_one));		//mat5
	Matrix second_matrix_1_2(Matrix::splitting_matrix_by_quarters(second_matrix, section_two));		//mat6
	Matrix second_matrix_2_1(Matrix::splitting_matrix_by_quarters(second_matrix, section_three));	//mat7
	Matrix second_matrix_2_2(Matrix::splitting_matrix_by_quarters(second_matrix, section_four));	//mat8

	int tmpr_size = resize_param / 2;		// размер промежуточных матриц
	// промежуточные матрицы (Р1, ... , Р6)
	Matrix intermediate_matrix_1(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_2(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_3(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_4(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_5(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_6(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_7(tmpr_size, tmpr_size);

	// вычисление промежуточнцых матриц по формулам
	for (int i = 0; i < tmpr_size; ++i) {
		for (int j = 0; j < tmpr_size; ++j) {

			for (int k = 0; k < tmpr_size; ++k) {
				intermediate_matrix_1(i, j) = (first_matrix_1_1(i, k) + first_matrix_2_2(i, k)) *
					(second_matrix_1_1(k, j) + second_matrix_2_2(k, j));
			}

			for (int k = 0; k < tmpr_size; ++k) {
				intermediate_matrix_2(i, j) = (first_matrix_2_1(i, k) + first_matrix_2_2(i, k)) *
					second_matrix_1_1(k, j);
			}

			for (int k = 0; k < tmpr_size; ++k) {
				intermediate_matrix_3(i, j) = first_matrix_1_1(i, k) *
					(second_matrix_1_2(k, j) - second_matrix_2_2(k, j));
			}

			for (int k = 0; k < tmpr_size; ++k) {
				intermediate_matrix_4(i, j) = first_matrix_2_2(i, k) *
					(second_matrix_2_1(k, j) - second_matrix_1_1(k, j));
			}

			for (int k = 0; k < tmpr_size; ++k) {
				intermediate_matrix_5(i, j) = (first_matrix_1_1(i, k) + first_matrix_1_2(i, k)) *
					second_matrix_2_2(k, j);
			}

			for (int k = 0; k < tmpr_size; ++k) {
				intermediate_matrix_6(i, j) = (first_matrix_2_1(i, k) - first_matrix_1_1(i, k)) *
					(second_matrix_1_1(k, j) + second_matrix_1_2(k, j));
			}

			for (int k = 0; k < tmpr_size; ++k) {
				intermediate_matrix_7(i, j) = (first_matrix_1_2(i, k) - first_matrix_2_2(i, k)) *
					(second_matrix_2_2(k, j) + second_matrix_2_1(k, j));
			}
		}
	}

	// создание 4х секций результирующей матрицы
	Matrix result_matrix_1_1(tmpr_size, tmpr_size);
	Matrix result_matrix_1_2(tmpr_size, tmpr_size);
	Matrix result_matrix_2_1(tmpr_size, tmpr_size);
	Matrix result_matrix_2_2(tmpr_size, tmpr_size);

	// подсчет значений секций результирующей матрицы из промежуточных
	for (int i = 0; i < tmpr_size; ++i) {
		for (int j = 0; j < tmpr_size; ++j) {
			result_matrix_1_1(i, j) = intermediate_matrix_1(i, j) + intermediate_matrix_4(i, j) -
				intermediate_matrix_5(i, j) + intermediate_matrix_7(i, j);

			result_matrix_1_2(i, j) = intermediate_matrix_3(i, j) + intermediate_matrix_5(i, j);

			result_matrix_2_1(i, j) = intermediate_matrix_2(i, j) + intermediate_matrix_4(i, j);

			result_matrix_2_2(i, j) = intermediate_matrix_1(i, j) - intermediate_matrix_2(i, j) +
				intermediate_matrix_3(i, j) + intermediate_matrix_6(i, j);
		}
	}

	// создание результирующий матрицы из секций
	Matrix result_matrix(resize_param, resize_param);
	for (int i = 0; i < resize_param / 2; ++i) {
		for (int j = 0; j < resize_param / 2; ++j) {
			result_matrix(i, j) = result_matrix_1_1(i, j);
			result_matrix(i, j + resize_param / 2) = result_matrix_1_2(i, j);
			result_matrix(i + resize_param / 2, j) = result_matrix_2_1(i, j);
			result_matrix(i + resize_param / 2, j + resize_param / 2) = result_matrix_2_2(i, j);
		}
	}
	// выравнивание границ результирующей матрицы
	Matrix aligned_matrix(Matrix::alignment_matrix_borders(result_matrix));
	cout << "\nРезультирующая матрица\n\n";
	aligned_matrix.output_matrix();
	system("pause");

	return 0;
}