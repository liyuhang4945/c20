import<iostream>;
import<format>;
using namespace std;

//��ֵ����
void test01() {
	cout << "int:\n";
	cout << format("MAX INT VALUE:{}\n", numeric_limits<int>::max());
	cout << format("Min INT VALUE:{}\n", numeric_limits<int>::min());
	cout << format("Lowest INT VALUE:{}\n", numeric_limits<int>::lowest());
	cout << "\ndouble:\n";
	cout << format("Max INT VALUE:{}\n", numeric_limits<double>::max());
	cout << format("min INT VALUE:{}\n", numeric_limits<double>::min());
	cout << format("Lowest INT VALUE:{}\n", numeric_limits<double>::lowest());
}

//���ʼ�� {}  ���ʼ����
void test02() {
	//int uninitialized;
	int num{};
	double num2{};
	int* nptr{};
	//coout << format("uninitialized int:{}\n", uninitialized);
	cout << format("initialized int:{}\n", num);
	cout << format("initialized double:{}\n", num2);
	cout << format("initialized int* ָ������:{}", (int)*nptr);
}
int main() {
	//test01();
	test02();
	return 0;
}