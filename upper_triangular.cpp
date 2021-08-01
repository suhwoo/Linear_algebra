#include <iostream>
#include <vector>
using namespace std;
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
int main() {
	int n, m;
	double element;
	cout << "�Է��ϰ����ϴ� matrix�� ���� ���� �Է��Ͻÿ�:";
	cin >> n;
	cout<< "�Է��ϰ����ϴ� matrix�� ���� ���� �Է��Ͻÿ�:";
	cin >> m;
	cout << "matrix component�� �Է��Ͻÿ�\n";
	vector<vector<double>> first;
	vector<double> temp;
	for (int i = 0; i < n; i++) {
		temp.clear();
		for (int j = 0; j < m; j++) {
			cin >> element;
			temp.push_back(element);
			
		}
		first.push_back(temp);
	}
	double point = 0;
	vector<double>pointRow;
	for (int i = 0; i < m; i++) {
		
		for (int j = i + 1; j < n; j++) {
			point = first[i][i];
			if (point == 0&& i+1!=n) {
				
				for (int f = i + 1; f < n; f++) {
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
			double mul = -(first[j][i]/point);
			
			//pointR�� mul���ϰ� �װ� first[j]�� ���Ѵ�.
			first[j]=addvec(first[j], mulvec(pointRow, mul));
			
			//���
			cout << "\n";
			cout << mul << "R" << i+1 << "+" << "R" << j+1 << "->" << "R" << j+1 << endl;
			cout << "[" << endl;
			for (int q = 0; q < n; q++) {
				for (int w = 0; w < m; w++) {
					//printf("%3.2f", first[q][w]);
					cout << first[q][w] << " ";
				}
				cout << "\n";
			}
			cout << "]\n" << endl;
		}
		
	}

	
	cout << "[" << endl;
	for (int q = 0; q < n; q++) {
		for (int w = 0; w < m; w++) {
			cout << first[q][w] << " ";
		}
		cout << "\n";
	}
	cout << "]" << endl;


	return 0;
}