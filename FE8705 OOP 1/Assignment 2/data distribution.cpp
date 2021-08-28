#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <string>

using namespace std;

string folder_path = "C:\\Users\\Farhan\\Desktop\\Data\\";

void find_n(string file_name,int* n) {
	string file_path = folder_path + file_name;
	ifstream myfile(file_path);
	vector<double> numbers;
	double number;
	while (!myfile.eof()) {
		myfile >> number;
		numbers.push_back(number);
	}

	sort(numbers.begin(), numbers.end());

	int index = 0;
	for (int i = 0; i < 1000; i++) {
		for (int j = index; j < numbers.size(); j++) {
			if (numbers[j] >= (i + 1)) {
				index = j;
				break;
			}
			else n[i] += 1;
		}
	}
}





void uniform(int* n,double*res) {
	int a;
	for (a = 90;a < 110;a++) {
		int sum = 0;
		for (int j = 0; j < 1000; j++) {
			sum += (a - n[j]) * (a - n[j]);
		}
		if (sum < 100000) {
			res[0] = a;
			res[3] = sum;
			break;
		}
	}
}

void exponential(int* n, double* res) {
	int isBreak = 0;
	for (int a = 700;a < 800;a++) {
		for (int b = 100;b < 150;b++) {
			double sum = 0.0;
			for (int j = 0; j < 1000; j++) {
				double f = a * exp(-j / double(b));
				sum += (f - n[j]) * (f - n[j]);
			}
			if (sum < 100000.0) {
				res[0] = a;
				res[1] = b;
				res[3] = sum;
				isBreak = 1;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
	}
}


void gaussian(int* n, double* res) {
	int isBreak = 0;
	for (int a = 600;a < 700;a++) {
		for (int b = 670;b < 730;b++) {
			for (int c = 7180;c <7220 ;c++) {
				double sum = 0.0;
				for (int j = 0; j < 1000; j++) {
					double f = a * exp(-pow(j -double(b),2)/double(c));
					sum += (f - n[j]) * (f - n[j]);
				}
				if (sum < 100000.0) {
					res[0] = a;
					res[1] = b;
					res[2] = c;
					res[3] = sum;
					isBreak = 1;
				}
				if (isBreak) break;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
	}
}


void logistic(int* n, double* res) {
	int isBreak = 0;
	for (int a = 4900;a < 5100;a++) {
		for (int b = 20;b < 60;b++) {
			double sum = 0.0;
			for (int j = 0; j < 1000; j++) {
				double f = a * exp(-j / double(b))/pow(1+exp(-j/double(b)),2);
				sum += (f - n[j]) * (f - n[j]);
			}
			if (sum < 100000.0) {
				res[0] = a;
				res[1] = b;
				res[3] = sum;
				isBreak = 1;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
	}
}


void Rayleigh(int* n, double* res) {
	int isBreak = 0;
	for (double a = 1.0;a < 5.0;a+=0.5) {
		for (int b = 79000;b < 81000;b++) {
			double sum = 0.0;
			for (int j = 0; j < 1000; j++) {
				
				double f = a * j * exp(- j * j / double(b));
				sum += (f - n[j]) * (f - n[j]);
			}
			if (sum < 100000.0) {
				res[0] = a;
				res[1] = b;
				res[3] = sum;
				isBreak = 1;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
	}
}


void Weibull(int* n, double* res) {
	int isBreak = 0;
	for (double a = 10;a < 20;a+=0.5) {
		for (double b = 1;b < 5;b+=0.5) {
			for (double c = 350;c < 450;c++) {
				double sum = 0.0;
				for (int j = 0; j < 1000; j++) {
					double f = a * pow(j,b-1)*exp(-pow(j / double(c), b));
					sum += (f - n[j]) * (f - n[j]);
				}
				if (sum < 100000.0) {
					res[0] = a;
					res[1] = b;
					res[2] = c;
					res[3] = sum;
					isBreak = 1;
				}
				if (isBreak) break;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
	}
}



int main() {
	double start, end;
	start = clock();
	for (int i = 2;i < 8;i++) {
		string file_name = "data" + to_string(i) + ".txt";
		int n[1000] = { 0 };
		find_n(file_name,n);
		

		double res[4] = { 0.0 };
		if (i == 2) {
			exponential(n, res);
			cout << "data2.txt: Exponential distribution with a=" << res[0] <<", b="<< res[1] << ", S=" << res[3] << endl;
		}
		else if (i == 3) {
			gaussian(n, res);
			cout << "data3.txt: Gaussian distribution with a=" << res[0] << ", b=" << res[1] << ", c=" << res[2] << ", S=" << res[3] << endl;
		}
		else if (i == 4) {
			logistic(n, res);
			cout << "data4.txt: Logistic distribution with a=" << res[0] << ", b=" << res[1]<<" S=" << res[3] << endl;
		}
		else if (i == 5) {
			Rayleigh(n, res);
			cout << "data5.txt: Rayleigh distribution with a=" << res[0] << ", b=" << res[1] << " S=" << res[3] << endl;
		}
		else if (i == 6) {
			uniform(n, res);
			cout << "data6.txt: Uniform distribution with a=" << res[0] << " S=" << res[3] << endl;
		}
		else if (i == 7) {
			Weibull(n, res);
			cout << "data7.txt: Weibull distribution with a=" << res[0] << ", b=" << res[1] << ", c=" << res[2] << ", S=" << res[3] << endl;
		}
		
	}

	end = clock();
	cout <<endl << "Time Cost:  " << (end - start)/1000 <<"s";
	return 0;
}