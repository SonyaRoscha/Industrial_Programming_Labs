#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class Matrix {
private:
	int** data;
	int rows;
	int columns;

public:
	Matrix() : rows(0), columns(0), data(nullptr) {}
	Matrix(int r, int c) : rows(r), columns(c) {
		data = new int* [rows];
		for (int i = 0; i < columns; ++i) {
			data[i] = new int[columns];
		}
	}
	~Matrix() {
		for (int i = 0; i < rows; ++i) {
			delete data[i];
		}
		delete[] data;
	}
	Matrix(const Matrix& mat) : rows(mat.rows), columns(mat.columns) {
		data = new int* [rows];
		for (int i = 0; i < rows; ++i) {
			data[i] = new int[columns];
			for (int j = 0; j < columns; ++j) {
				data[i][j] = mat.data[i][j];
			}
		}
	}

	int get_rows() const { return rows; }
	int get_columns() const { return columns; }
	int** get_data() const { return data; }
	pair<int, int> size() {
		return { rows, columns };
	}

	// ��������� ������� ���������� ������
	void fill_matrix_zero();
	void creating_matrix_manually();
	void creating_matrix_automatically();

	// ����� �������
	void output_matrix() const;

	// ���������� � ������� �������� �� ���������
	void set_data_for_smaller_matrix(const Matrix&);

	// ���������� ������� �� 4 ������, ���������� 1/4-� �������
	static Matrix splitting_matrix_by_quarters(const Matrix&, pair<int, int>);

	// ������������ ������ �������������� �������
	static Matrix alignment_matrix_borders(Matrix);

	Matrix& operator= (const Matrix& mat) {
		if (this == &mat) {
			return *this;
		}

		data = mat.data;
		rows = mat.rows;
		columns = mat.columns;

		return *this;
	}

	int& operator()(int i, int j) {
		assert(i >= 0 && i <= rows);
		assert(j >= 0 && j <= columns);

		return data[i][j];
	}

	const int& operator()(int i, int j) const {
		assert(i >= 0 && i <= rows);
		assert(j >= 0 && j <= columns);

		return data[i][j];
	}
};
