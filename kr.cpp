#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex sync;

class Account {
public:
	Account(int _sum) {
		sum = _sum;
	}

	int getSum() {
		//std::lock_guard<std::mutex> lock(sync);
		return sum;
	}

	void changeSum(int operation) {
		std::lock_guard<std::mutex> lock(sync);

		std::cout << "Was: " << getSum() << " ";
		sum += operation;
		std::cout << "Operation: " << operation << ". New balance: " << getSum() << "\n";
	}

	bool ableToChange(int operation) {
		std::lock_guard<std::mutex> lock(sync);
		int currentSum = getSum();
		if (currentSum + operation >= 0) {
			return true;
		}
		return false;
	}

private:
	int sum;
};

void calculate(Account& account, std::vector<int> operations) {
	std::vector<int> unperformedOperations;
	for (int i = 0; i < operations.size(); i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		if (account.ableToChange(operations[i])) {
			account.changeSum(operations[i]);
		}
		else {
			unperformedOperations.push_back(operations[i]);
			std::cout << "Operation " << operations[i] << " not done." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(850 + rand() % 300));
		}
	}
	for (int i = 0; i < unperformedOperations.size(); i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		if (account.ableToChange(unperformedOperations[i])) {
			account.changeSum(unperformedOperations[i]);
		}
		else {
			std::cout << "Operation " << unperformedOperations[i] << " unable to happen." << std::endl;
		}
	}
}

int main() {
	Account acc(100);

	std::vector<int> v1 = { -130, 10, 20 };
	std::vector<int> v2 = { 1, 2, 3 };

	std::thread t1(calculate, std::ref(acc), v1);
	std::thread t2(calculate, std::ref(acc), v2);

	t1.join();
	t2.join();

	std::cout << "Total balance is " << acc.getSum() << ".";
}