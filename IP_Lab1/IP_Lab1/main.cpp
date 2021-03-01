#include <iostream>;
#include "Matrix.h";

using namespace std;

// ����� 2� ������
void output_bouth_matrix(const Matrix& m1, const Matrix& m2) {
	cout << "\n������� �1\n";
	m1.output_matrix();

	cout << "\n������� �2\n\n";
	m2.output_matrix();
}

// ��������� ���������, ������� ������ ������ ������ ������
void change_resize_param(int& param, const pair<int, int>& size_of_mat1, const pair<int, int>& size_of_mat2) {
	while (param < size_of_mat1.first || param < size_of_mat1.second ||
		param < size_of_mat2.first || param < size_of_mat2.second)
		param *= 2;
}

int main() {
	srand(time(NULL));
	system("chcp 65001");
	cout << "��� ������������ ���������" << endl <<
		"�������� ������������ ������ ������� ���������\n\n";


	int n1, m1, n2, m2;			// ���������� ��� �������� ������ (������ � �������)
	int manual_or_auto;			// ����� �������� ���������� ������
	int resize_param = 2;		// �������� ��� ���������� ������ � ���������� �������

	// ���� ������ ��� �������� ������
	do
	{
		cout << "������� ������� ������ �������\n";
		cin >> n1 >> m1;
	} while (n1 <= 0 || m1 <= 0);
	do
	{
		cout << "������� ������� ������ �������\n";
		cin >> n2 >> m2;
	} while (n2 <= 0 || m2 <= 0);

	Matrix first_matrix(n1, m1);
	Matrix second_matrix(n2, m2);

	// ���������� ������
	do {
		cout << "�������� ������ ���������� ������\n" <<
			"1 - ������� \n2 - ��������� �������\n";
		cin >> manual_or_auto;
	} while (manual_or_auto < 1 || manual_or_auto > 2);

	if (manual_or_auto == 1) {
		cout << "������� ������ ������� �1:\n";
		first_matrix.creating_matrix_manually();
		cout << "������� ������ ������� �2:\n";
		second_matrix.creating_matrix_manually();

		output_bouth_matrix(first_matrix, second_matrix);
	}
	else if (manual_or_auto == 2) {
		first_matrix.creating_matrix_automatically();
		second_matrix.creating_matrix_automatically();

		output_bouth_matrix(first_matrix, second_matrix);
	}

	// ��������� ��������� ��� ���������� ������
	change_resize_param(resize_param, first_matrix.size(), second_matrix.size());
	// �������� ���������� � ���������� ������� ������
	Matrix resized_first_matrix(resize_param, resize_param);
	Matrix resized_second_matrix(resize_param, resize_param);

	resized_first_matrix.fill_matrix_zero();
	resized_second_matrix.fill_matrix_zero();

	resized_first_matrix.set_data_for_smaller_matrix(first_matrix);
	resized_second_matrix.set_data_for_smaller_matrix(second_matrix);

	cout << "����������� �������\n";
	output_bouth_matrix(resized_first_matrix, resized_second_matrix);


	// ������ ��� ���������� ������� �� 4 ������
	pair<int, int> section_one{ 0, 0 };
	pair<int, int> section_two{ 0, resize_param / 2 };
	pair<int, int> section_three{ resize_param / 2, 0 };
	pair<int, int> section_four{ resize_param / 2, resize_param / 2 };

	// 4 �������, �� ������� ���� �������� 1� �������� �������
	Matrix first_matrix_1_1(Matrix::splitting_matrix_by_quarters(first_matrix, section_one));		//mat1
	Matrix first_matrix_1_2(Matrix::splitting_matrix_by_quarters(first_matrix, section_two));		//mat2
	Matrix first_matrix_2_1(Matrix::splitting_matrix_by_quarters(first_matrix, section_three));		//mat3
	Matrix first_matrix_2_2(Matrix::splitting_matrix_by_quarters(first_matrix, section_four));		//mat4

	// 4 �������, �� ������� ���� �������� 2� �������� �������
	Matrix second_matrix_1_1(Matrix::splitting_matrix_by_quarters(second_matrix, section_one));		//mat5
	Matrix second_matrix_1_2(Matrix::splitting_matrix_by_quarters(second_matrix, section_two));		//mat6
	Matrix second_matrix_2_1(Matrix::splitting_matrix_by_quarters(second_matrix, section_three));	//mat7
	Matrix second_matrix_2_2(Matrix::splitting_matrix_by_quarters(second_matrix, section_four));	//mat8

	int tmpr_size = resize_param / 2;		// ������ ������������� ������
	// ������������� ������� (�1, ... , �6)
	Matrix intermediate_matrix_1(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_2(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_3(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_4(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_5(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_6(tmpr_size, tmpr_size);
	Matrix intermediate_matrix_7(tmpr_size, tmpr_size);

	// ���������� �������������� ������ �� ��������
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

	// �������� 4� ������ �������������� �������
	Matrix result_matrix_1_1(tmpr_size, tmpr_size);
	Matrix result_matrix_1_2(tmpr_size, tmpr_size);
	Matrix result_matrix_2_1(tmpr_size, tmpr_size);
	Matrix result_matrix_2_2(tmpr_size, tmpr_size);

	// ������� �������� ������ �������������� ������� �� �������������
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

	// �������� �������������� ������� �� ������
	Matrix result_matrix(resize_param, resize_param);
	for (int i = 0; i < resize_param / 2; ++i) {
		for (int j = 0; j < resize_param / 2; ++j) {
			result_matrix(i, j) = result_matrix_1_1(i, j);
			result_matrix(i, j + resize_param / 2) = result_matrix_1_2(i, j);
			result_matrix(i + resize_param / 2, j) = result_matrix_2_1(i, j);
			result_matrix(i + resize_param / 2, j + resize_param / 2) = result_matrix_2_2(i, j);
		}
	}
	// ������������ ������ �������������� �������
	Matrix aligned_matrix(Matrix::alignment_matrix_borders(result_matrix));
	cout << "\n�������������� �������\n\n";
	aligned_matrix.output_matrix();
	system("pause");

	return 0;
}