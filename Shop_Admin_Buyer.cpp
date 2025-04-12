#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Wallet {
private:
	int balance;

public:

	Wallet() {

		balance = 0;

	}



	void addMoney(int amount) {
		ofstream file("wallet.txt");
		if (amount > 0) {

			balance += amount;
			file << balance;
			file.close();
			cout << "-----|Added " << amount << " to wallet.\n";
		}
		else {
			cout << "Amount must be positive!\n";
		}
	}


	void withdrawMoney(int amount) {
		if (amount > balance) {
			cout << "Not enough funds!\n";
		}
		else {
			balance -= amount;
			ofstream file("wallet.txt");
			file << balance;
			file.close();
			cout << "Withdrawn " << amount << " from wallet.\n";


		}
	}
	int getBalance() const {
		return balance;
	}

	int getBalance(Wallet& w) const {
		ifstream file("wallet.txt");
		file >> w.balance;
		file.close();
		return balance;
	}


};	  
class Product {
private:

	string ProductName;
	int value;
	int amount;


public:
	Product(string name, int value, int n) : ProductName(name), value(value), amount(n) {}

	void add(Product& p) {

		cout << "\nProduct name: ";
		cin >> ProductName;
		cout << "\nProduct value: ";
		cin >> value;
		cout << "\nProduct amount: ";
		cin >> amount;

		ofstream file("products.txt", ios::app);
		if (file.is_open()) {
			file << p.ProductName << " " << p.value << " " << p.amount << endl;
			file.close();
		}
	}

	void ShowInfo() {
		ifstream readfile("products.txt");
		string line;
		int num = 1;
		if (readfile.is_open()) {
				cout << "-----| id |  name  | price | amount |------------------|" << endl;
			while (getline(readfile, line)) {


				cout << "-----| " << num << ". |" << line << endl;
				num++;
			}
			readfile.close();
		}
	}

	void deleteLine(int lineToDelete) {
		ifstream input("products.txt");
		vector<string> lines;
		string line;
		int currentLine = 1;


		while (getline(input, line)) {
			if (currentLine != lineToDelete) {
				lines.push_back(line);
			}
			currentLine++;
		}
		input.close();


		ofstream output("products.txt");
		for (const auto& l : lines) {
			output << l << endl;
		}
		output.close();

		cout << "-----|row #" << lineToDelete << " was deleted." << endl;
	}

	void editProduct(int lineToEdit,Product p) {
		ifstream input("products.txt");
		vector<string> lines;
		string line;
		int currentLine = 1;

		
		cout << "\nProduct name: ";
		cin >> p.ProductName;
		cout << "\nProduct value: ";
		cin >> p.value;
		cout << "\nProduct amount: ";
		cin >> p.amount;

		
		while (getline(input, line)) {
			if (currentLine == lineToEdit) {
				
				stringstream ss;
				ss << p.ProductName << " " << p.value << " " << p.amount;
				lines.push_back(ss.str());
			}
			else {
				lines.push_back(line); 
			}
			currentLine++;
		}
		input.close();

		
		ofstream output("products.txt");
		for (const string& l : lines) {
			output << l << endl;
		}
		output.close();

		cout << "Product in row #" << lineToEdit << " greatfully edited!" << endl;
	}

	void show(Product& p) {
		cout << p.ProductName << " " << p.value << " " << p.amount << endl;

	}

	void getQuantity(int lineToGet,Product& p,Wallet& w) {
		ifstream input("products.txt");
		string line;
		int currentLine = 1;

		
		while (getline(input, line)) {
			if (currentLine == lineToGet) {
				
				input >> p.ProductName >> p.value >> p.amount;
			}
			currentLine++;
		}
		input.close();
		
		
		int quantity;
		w.getBalance(w);
		
		cout << "\n-----|quantity of the product: ";
		cin >> quantity;
		int res;
		res = quantity * p.value;
		w.withdrawMoney(res);
		if (res <= w.getBalance()) {
			ofstream file("history.txt", ios::app);
			file << "\n-----|-------------------------------------------------|"
				<< "\n-----|Name of purchase: " << p.ProductName
				<< "\n-----|Price of purchase: " << p.value
				<< "\n-----|Quantity of purchase: " << quantity
				<< "\n-----|-------------------------------------------------|";
			file.close();
		}
		

	}
	void ViewHistory(Product& p) {
		ifstream file("history.txt");
		if (!file.is_open()) {
			cout << "Do not open the history.txt file!" << endl;
			return;
		}

		string line;
		while (getline(file, line)) {
			cout << line << endl;
		}

		file.close();
	}
};



static void menu(Product p,Wallet w) { 
	
	int num;
	cout << " -|1. Administrator (adds, edits and issues products)\n "
		<< "-|2. Buyer (views products, buys them)\n"
		<< " -|3. Exit" << endl;
	cout << " -|Your choise: ";
	cin >> num;

	

	while (num != 3) {

			switch (num) {
			case 1:
						int num1;
						cout << "\n ---|1. add new products\n "
							<< "---|2. edit existent product\n"
							<< " ---|3. delete existent product\n"
							<< " ---|4. View the entire store assortment\n"
							<< " ---|5. Exit\n" << endl;
						cout << " ---|Your choise: ";
						cin >> num1;

						switch (num1) {
							case 1:
								int num_3;
								cout << "-----|1. Exit"
									<< "\n-----|2. Continue" << endl;
								cout << " -----|Your choise: ";
								cin >> num_3;
								
								
									switch (num_3)
									{
									case 1:
										break;
									case 2:
										cout << "\n|------------------------------------------------------|" << endl;

										p.add(p);

										cout << "\n|------------------------------------------------------|" << endl;
										break;


									default:
										cout << "_Try again_" << endl;
										break;
									}
									
									
								
								break;
							
							case 2:
								int variant;
								cout << "-----|1.Exit" 
									 << "\n-----|2. continue ";
								cout << "\n -----|Your choise: ";
								cin >> variant;
								switch (variant)
								{
								case 1:
									break;
								case 2:
									int line;
									cout << "\n|------------------------------------------------------|" << endl;
									p.ShowInfo();
									cout << "|------------------------------------------------------|" << endl;
									cout << "\n-----|2. Enter the row to edit ";
									cout << "\n -----|Your choise: ";
									cin >> line;
									
									p.editProduct(line,p);
									p.show(p);
									cout << "\n|------------------------------------------------------|" << endl;
									break; 

								default:
									break;
								}
								break;

								
							case 3:
								int variant1;
								cout << "-----|1.Exit" 
									 << "\n-----|2. continue";
								cout << "\n -----|Your choise: ";
								cin >> variant1;
								switch (variant1)
								{
								case 1:
									break;
								case 2:
									int line1;
									cout << "-----|Enter the row to delete(start count #0 for #1 row): ";
									cout << "\n -----|Your choise: ";
									cin >> line1;
									cout << "\n|------------------------------------------------------|" << endl;
									p.deleteLine(line1);
									p.ShowInfo();
									cout << "\n|------------------------------------------------------|" << endl;
									break;

								default:
									break;
								}
								break;

							case 4:
								cout << "\n|------------------------------------------------------|" << endl;
								p.ShowInfo();
								cout << "\n|------------------------------------------------------|" << endl;
								break;
							case 5:
								break;
							default:
								cout << "try again,please.\n" << endl;
								break;

						}

			break;
			
			case 2:
						int num2;
						cout << "\n ---|1. View products in the store\n "
							 << "---|2. Purchase of goods\n"
							 << " ---|3. View purchase history \n"
							 << " ---|4. Exit\n" << endl;
						cout << " ---|Your choise: ";
						cin >> num2;

						switch (num2) {
						case 1:
									cout << "\n|------------------------------------------------------|" << endl;
									p.ShowInfo();
									cout << "\n|------------------------------------------------------|" << endl;
									break;
									
						case 2:

									int purchase;
									cout << "\n-----|1. replenish the balance"
										<< "\n-----|2. purchase of goods"
										<< "\n-----|3. exit" << endl;
									cout << "-----|Your choise: ";
									cin >> purchase;
							
									switch (purchase)
									{
									case 1:
										int amount;
										cout << "\n-----|How much do you want to top up your balance: ";
										cin >> amount;
										w.addMoney(amount);
										break;

									case 2:
										cout << "\n|------------------------------------------------------|" << endl;
										p.ShowInfo();
										cout << "\n|------------------------------------------------------|" << endl;
										int line;
										cout << "\n-----|specify the line and quantity of the product you want to buy";
										cout << "\n-----| your balance: " << w.getBalance(w) << " |-----" << endl;
										cout << "\n-----|line of the product: ";
										cin >> line;

										p.getQuantity(line, p, w);
										cout << "-----| your balance: " << w.getBalance(w) << " |-----" << endl;
										break;
									case 3:
										break;
									default:
										cout << "try again,please.\n" << endl;
										break;
									
									}
									break;
						case 3:
							
							p.ViewHistory(p);
							
							break;
						
						case 4:

							break;
						break;
						default:
							cout << "try again,please.\n" << endl;
							break;
						
						}

						break;
			
			case 3:
				cout << "closing the program..." << endl;
				break;
			default:
				cout << "try again,please.\n" << endl;
				break;
			
		    }

		
		cout << " -|1. Administrator (adds, edits and issues products)\n "
			<< "-|2. Buyer (views products, buys them)\n"
			<< " -|3. Exit" << endl;
		cout << " -|Your choise: ";
		cin >> num;
	}
	
}




int main() {
	
	Product product("",0,0);
	Wallet wallet_1{};
	menu(product,wallet_1);



	return 0;
	
}