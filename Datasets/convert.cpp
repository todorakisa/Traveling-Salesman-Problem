#include<iostream>
#include<fstream>
using namespace std;

int main(){
	ofstream out("output.txt");
	if(out.is_open()){
		double num;
		ifstream in("ca4663.txt");
		if(in.is_open()){
			while(in >> num){
				in >> num;
				out << num << " ";
				in >> num;
				out << num << endl;
			}
			in.close();
		}
		out.close();
	}
	
	return 0;
}
