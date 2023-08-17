module database;
import <stdexcept>;

using namespace std;

namespace Records {
	//添加员工
	Employee& Database::addEmployee(const string& firstName,
		const string& lastName) {
		//创建员工对象
		Employee theEmployee{ firstName,lastName };
		//员工数量+1
		theEmployee.setEmployeeNumber(m_nextEmployeeNumber++);

		theEmployee.hire();
		m_employees.push_back(theEmployee);
		//返回最新员工的引用
		return m_employees.back();
	}

	Employee& Database::getEmployee(int employeeNumber) {
		for (auto& employee : m_employees) {
			if (employee.getEmployeeNumber() == employeeNumber) {
				return employee;
			}
		}
		throw logic_error{ "No employee found." };
	}

	void Database::displayAll()const {
		for (const auto& employee : m_employees) {
			employee.display();
		}
	}

	void Database::displayCurrent()const {

		for (const auto& employee : m_employees) {
			if (employee.isHired()) {
				employee.display();
			}
		}
	}

	void Database::displayFormer()const {

		for (const auto& employee : m_employees) {
			if (!employee.isHired()) {
				employee.display();
			}
		}
	}
}