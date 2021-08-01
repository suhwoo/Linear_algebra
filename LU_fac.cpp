#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
vector<vector<vector<double>>> E;
vector<double> mulvec(vector<double> p, double m) {
	for (int i = 0; i < p.size(); i++) {
		p[i] = p[i] * m;
	}
	return p;
}
vector<double> addvec(vector<double> a, vector<double> b) {
	for (int i = 0; i < a.size(); i++) {
		a[i] += b[i];
	}

	return a;

}
vector<vector<double>> mulmat(vector<vector<double>>a, vector<vector<double>>b) {
	vector<vector<double>> ans;
	vector<double>onerow;
	int m = a.size();
	
	for (int i = 0; i < m; i++) {
		
		for (int j = 0; j < m; j++) {
			double temp = 0;
			for (int h = 0; h < m; h++) {
				temp += a[i][h] * b[h][j];
			}
			
			onerow.push_back(temp);
		
		}
		
		ans.push_back(onerow);
		onerow.clear();
	}
	return ans;

}
int main() {
	int row, col;
	double element;
	cout << "입력하고자 하는 matrix의 행의 수를 입력하시오: ";
	cin >> row;
	cout << "입력하고자 하는 matrix의 열의 수를 입력하시오: ";
	cin >> col;
	//input matrix
	vector<vector<double>> first;
	vector<vector<double>> A;
	vector<double> temp;
	for (int i = 0; i < row; i++) {
		temp.clear();
		for (int j = 0; j < col; j++) {
			cin >> element;
			temp.push_back(element);

		}
		first.push_back(temp);

	}
	A = first;
	//E matrix
	int Erow = min(col,row);
	vector<vector<double>>t;
	vector<double> Etemp;
	for (int q = 0; q < Erow; q++) {
		Etemp.clear();
		for (int p = 0; p < Erow; p++) {
			if (q == p)Etemp.push_back(1);
			else Etemp.push_back(0);
		}
		t.push_back(Etemp);
	}
	for (int i = 0; i < Erow; i++) {
		E.push_back(t);
	}
	//U로 만들기.
	double point = 0;
	vector<double>pointRow;
	vector<vector<double>>pointE;
	vector<double>EpointRow;
	int Ecnt = 0;
	for (int i = 0; i < col; i++) {

		for (int j = i + 1; j < row; j++) {
			point = first[i][i];

			if (point == 0 && i + 1 != row) {

				for (int f = i + 1; f < row; f++) {
					if (first[f][f] != 0) {
						vector<double> temp1 = first[i];
						first[i] = first[f];
						first[f] = temp1;
						break;
					}

				}
			}
		
			point = first[i][i];
			pointRow = first[i];
			pointE = E[Ecnt];
			
			EpointRow = pointE[i];
			double mul = -(first[j][i] / point);

			//pointR에 mul곱하고 그걸 first[j]에 더한다.
			first[j] = addvec(first[j], mulvec(pointRow, mul));
			pointE[j] = addvec(pointE[j], mulvec(EpointRow, mul));
			E[Ecnt] = pointE;
			Ecnt++;
			//출력
			//cout << "\n";
			//cout << mul << "R" << i + 1 << "+" << "R" << j + 1 << "->" << "R" << j + 1 << endl;
			//cout << "E" << Ecnt << ":" << endl;
			//cout << "[" << endl;
			//for (int q = 0; q < Erow; q++) {
			//	for (int w = 0; w < Erow; w++) {
			//		//printf("%3.2f", first[q][w]);
			//		cout << pointE[q][w] << " ";
			//	}
			//	cout << "\n";
			//}
			//cout << "]\n" << endl;
		}

	}
	//L구하기
	//L=E1(-1)E2(-1)E3(-1)
	for (int i = 0; i < E.size(); i++) {
		vector<vector<double>>hereE = E[i];
		for (int q = 0; q < Erow; q++) {
			for (int p = 0; p < Erow; p++) {
				if (q == p && hereE[q][p] != 1)hereE[q][p] = 1 / hereE[q][p];
				else if (q != p && hereE[q][p] != 0)hereE[q][p] = -hereE[q][p];
			}
		}
		E[i] = hereE;
	
	}
	vector<vector<double>>L=E[0];
	for (int i = 1; i < E.size(); i++) {
		L = mulmat(L, E[i]);
	}
	//결과출력
	cout << "\n\n";
	cout << "A:" << endl;
	cout << "[" << endl;
	for (int q = 0; q < A.size(); q++) {
		for (int w = 0; w < A[0].size(); w++) {
			//printf("%3.2f", first[q][w]);
			cout << A[q][w] << " ";
		}
		cout << "\n";
	}
	cout << "]\n" << endl;
	cout << " = " << endl;
	cout << "L:					U:" << endl;
	cout << "[					[" << endl;
	for (int q = 0; q < Erow; q++) {
		for (int w = 0; w <Erow; w++) {
			//printf("%3.2f", first[q][w]);
			cout << L[q][w] << " ";
		}
		cout << "				";
		for (int w = 0; w < first[0].size(); w++) {
			//printf("%3.2f", first[q][w]);
			cout << first[q][w] << " ";
		}
		cout << "\n";
	}
	cout << "]					]\n" << endl;
}
