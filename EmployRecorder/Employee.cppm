export module employee;
import<string>;
namespace Records {
	//Ĭ����н
	const int DefaultStartingSalary{ 30000 };
	//Ĭ�ϼ�н��
	export const int DefaultRaiseAndDemeritAmount{ 1000 };
	//��Ա��
	export class Employee {
	public:
		Employee(const std::string& firstName,
			const std::string& lastName);
		//��н
		void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);
		//��н
		void demote(int demeritAmount = DefaultRaiseAndDemeritAmount);

		void hire();
		void fire();
		void display()const;


		void setFirstName(const std::string& firstName);
		const std::string& getFirstName()const;

		void setLastName(const std::string& lastName);
		const std::string& getLastName()const;

		void setEmployeeNumber(int employeeNumber);
		int getEmployeeNumber()const;

		void setSalary(int newSalary);
		int getSalary()const;

		bool isHired()const;
	private:
		std::string m_firstName;
		std::string m_lastName;
		int m_employeeNumber{ -1 };
		int m_salary{ DefaultStartingSalary };
		bool m_hired{ false };
	};
}

