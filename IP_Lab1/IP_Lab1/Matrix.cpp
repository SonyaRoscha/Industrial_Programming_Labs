#include "Matrix.h"

void Matrix::fill_matrix_zero() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			data[i][j] = 0;
		}
	}
}

void Matrix::creating_matrix_manually() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; j++)
			cin >> data[i][j];
	}
}

void Matrix::creating_matrix_automatically() {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			data[i][j] = rand() % 10;
	}
}

void Matrix::output_matrix() const {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			cout << data[i][j] << " ";
		cout << "\n";
	}
}

// записывает в матрицу значения из параметра
void Matrix::set_data_for_smaller_matrix(const Matrix& mat) {
	if (mat.get_rows() <= rows && mat.get_columns() <= columns) {
		for (int i = 0; i < mat.get_rows(); ++i) {
			for (int j = 0; j < mat.get_columns(); ++j) {
				data[i][j] = mat(i, j);
			}
		}
	}
}

// разделение матрицы на 4 секции, возвращает 1/4-ю матрицы
Matrix Matrix::splitting_matrix_by_quarters(const Matrix& mat, pair<int, int> section) {
	Matrix new_mat(mat.get_rows() / 2, mat.get_columns() / 2);

	for (int i = 0; i < new_mat.rows; ++i) {
		for (int j = 0; j < new_mat.columns; ++j)
			new_mat(i, j) = mat(i + section.first, j + section.second);
	}

	return new_mat;
}

// выравнивание границ результирующей матрицы
Matrix Matrix::alignment_matrix_borders(Matrix result) {
	int size_of_result = result.get_rows();
	int tmp_x = 0;
	int rows_for_alignment = 100;					// = size_of_result
	int columns_for_alignment = 100;				// = size_of_result

	for (int i = 0; i < size_of_result; ++i) {
		tmp_x = 0;
		for (int j = 0; j < size_of_result; ++j) {
			if (result(i, j) != 0) {
				++tmp_x;
				rows_for_alignment = 100;			// = size_of_result
			}
		}
		if (tmp_x == 0 && i < rows_for_alignment) {
			rows_for_alignment = i;
		}
	}
	for (int i = 0; i < size_of_result; ++i) {
		tmp_x = 0;
		for (int j = 0; j < size_of_result; ++j) {
			if (result(j, i) != 0) {
				++tmp_x;
				columns_for_alignment = 100;
			}
		}
		if (tmp_x == 0 && i < columns_for_alignment) {
			columns_for_alignment = i;
		}
	}

	Matrix aligned_matrix(rows_for_alignment, columns_for_alignment);
	for (int i = 0; i < aligned_matrix.rows; ++i) {
		for (int j = 0; j < aligned_matrix.columns; ++j) {
			aligned_matrix(i, j) = result(i, j);
		}
	}

	return aligned_matrix;
}