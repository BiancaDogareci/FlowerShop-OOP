#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Product {
private:
	char name[20];
	int product_id;
	double price;
	int nr_left;
public:
	Product(const char Name[20], int Product_id, double Price, int Nr_left) {
		strcpy(name, Name);
		product_id = Product_id;
		price = Price;
		nr_left = Nr_left;
	}

	int minus_product(int nr_of_flowers) {
		if (nr_left - nr_of_flowers >= 0) {
			nr_left = nr_left - nr_of_flowers;
			return 1;
		}
		else
			return 2;
	}

	double product_price() {
		return price;
	}

	int get_code() {
		return product_id;
	}

	char* get_name() {
		return name;
	}
	~Product() {
	}
	friend ostream& operator << (ostream& out, const Product P);
	friend class ShoppingCart;
};

ostream& operator << (ostream& out, const Product P) {
	cout << "Nume: " << P.name << endl;
	cout << "Cod: " << P.product_id << endl;
	cout << "Pret pe fir: " << P.price << " lei" << endl;
	cout << "Numar de fire ramase: " << P.nr_left << endl;
	return out;
}

class Customer {
private:
	char last_name[30];
	char first_name[30];
	char email[30];
public:
	Customer() : last_name(), first_name(), email()
	{
	}
	Customer(char* Last_name, char* First_name, char* Email) {
		strcpy(Last_name, last_name);
		strcpy(First_name, first_name);
		strcpy(Email, email);
	}
	char* get_last_name() {
		return last_name;
	}
	char* get_first_name() {
		return first_name;
	}
	char* get_email() {
		return email;
	}
	~Customer() {
	}
	friend istream& operator >> (istream& in, Customer& c);
	friend class ShoppingCart;
};

istream& operator >> (istream& in, Customer& c)
{
	cout << "Nume de familie: ";
	in >> c.last_name;
	cout << "Prenume: ";
	in >> c.first_name;
	cout << "Email: ";
	in >> c.email;
	return in;
}

class ShoppingCart {
private:
	Product** v_product_code;
	size_t size_vpc;
	double* v_prices;
	size_t size_vp;
	Customer customer;
public:
	ShoppingCart() : customer()
	{
		size_vpc = 0;
		size_vp = 0;
		v_product_code = NULL;
		v_prices = NULL;
	}
	void add_to_cart(double price, Product* product) {
		if (v_product_code != NULL) {
			Product** vec;
			vec = new Product*[size_vpc + 1];
			for (int i = 0; i < size_vpc; i++)
			{
				vec[i] = v_product_code[i];
			}
			vec[size_vpc] = product;
			size_vpc++;
			delete[] v_product_code;
			v_product_code = vec;
		}
		else {
			size_vpc++;
			v_product_code = new Product*[size_vpc];
			v_product_code[size_vpc - 1] = product;
		}

		if (v_prices != NULL) {
			double* vec2;
			vec2 = new double[size_vp + 1];
			for (int i = 0; i < size_vp; i++) {
				vec2[i] = v_prices[i];
			}
			vec2[size_vp] = price;
			size_vp++;
			delete[] v_prices;
			v_prices = vec2;
		}
		else {
			size_vp++;
			v_prices = new double[size_vp];
			v_prices[size_vp - 1] = price;
		}
	}

	double show_cart() {
		cout << endl;
		cout << "**********************************" << endl;
		cout << "Cosul dumneavoastra de cumparaturi:" << endl << endl;

		double total_price = 0;
		for (int i = 0; i < size_vp; i++) {
			total_price = total_price + v_prices[i];
			cout << "Produs: " << v_product_code[i]->name << endl;
			cout << "Pret: " << v_prices[i] << " lei" << endl;
		}
		cout << endl;
		cout << "Pretul total este: " << total_price << " lei" << endl;
		return total_price;
	}

	void add_customer_info(char* Last_name, char* First_name, char* Email) {
		strcpy(customer.last_name, Last_name);
		strcpy(customer.first_name, First_name);
		strcpy(customer.email, Email);
	}

	void get_customer_info() {
		cout << "Numele introdus: " << customer.last_name << " " << customer.first_name << endl;
		cout << "Email-ul introdus: " << customer.email << endl;
	}

	static void sale(double total_price) {
		cout << "Reducere 10% de Valentine's Day!" << endl;
		cout << "Noul total: " << endl << total_price - total_price / 10 << " lei";
	}
	~ShoppingCart(){
		if(v_prices!=NULL)
			delete[] v_prices;
		if(v_product_code!=NULL)
			delete[] v_product_code;
	}
	friend class Order;
};


class Adress {
private:
	char country[10];
	char city[10];
	char street[10];
	int number;
public:
	Adress() : country(), city(), street(), number()
	{
	}
	Adress(char Country[10], char City[10], char Street[10], int Number)
	{
		strcpy(country, Country);
		strcpy(city, City);
		strcpy(street, Street);
		number = Number;
	}
	~Adress() {
	}
	friend class Order;
};

class CreditCard {
private:
	char card_nr[20];
	int expiration_day;
	int expiration_month;
	char cardholder_name[30];
	int CVC;
public:
	CreditCard() : card_nr(), expiration_day(), expiration_month(), cardholder_name(), CVC()
	{
	}
	CreditCard(char Card_nr[20], int Expiration_day, int Expiration_month, char Cardholder_name[30], int cvc) {
		strcpy(card_nr, Card_nr);
		expiration_day = Expiration_day;
		expiration_month = Expiration_month;
		strcpy(cardholder_name, Cardholder_name);
		CVC = cvc;
	}
	~CreditCard() {
	}
	friend class Order;
};

class Order {
private:
	Adress adress;
	CreditCard card;
	ShoppingCart* cart;
public:
	Order() {
		cart = nullptr;
	}
	void add_details(CreditCard creditcard) {
		strcpy(card.card_nr, creditcard.card_nr);
		card.expiration_day = creditcard.expiration_day;
		card.expiration_month = creditcard.expiration_month;
		strcpy(card.cardholder_name, creditcard.cardholder_name);
		card.CVC = creditcard.CVC;  //card=creditcard
	}
	void add_details(Adress a) {
		strcpy(adress.country, a.country);
		strcpy(adress.city, a.city);
		strcpy(adress.street, a.street);
		adress.number = a.number;
	}
	void add_shoppingcart_details(ShoppingCart* fullcart) {
		cart = fullcart;
	}
	void get_card_details() {
		cout << "Numarul cardului: " << card.card_nr << endl;
		cout << "Data expirarii: " << card.expiration_day << "/" << card.expiration_month << endl;
		cout << "Numele posesorului: " << card.cardholder_name << endl;
		cout << "CVC: " << card.CVC << endl;
	}
	void get_adress_details() {
		cout << "Tara: " << adress.country << endl;
		cout << "Oras: " << adress.city << endl;
		cout << "Strada: " << adress.street << endl;
		cout << "Numar: " << adress.number << endl;
	}
	~Order() {
	}

};

class feedback {
private:
	size_t size;
	int* data;
public:
	feedback() {
		data = NULL;
		size = 0;
	}
	feedback(int x) {
		size = 1;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = x;
	}

	feedback(const feedback& x) {
		size = x.size;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = x.data[i];
	}

	void operator=(const feedback& x) {
		if (data != NULL)
			delete[] data;
		size = x.size;
		data = new int[size];
		for (int i = 0; i < size; i++)
			data[i] = x.data[i];
	}

	~feedback() {
		if (data != NULL)
			delete[] data;
	}

};

void show_menu() {
	cout << "*********************************************" << endl;
	cout << "**          Bianca's Flower Shop           **" << endl;
	cout << "*********************************************" << endl;
	cout << "" << endl;
	cout << "Alege produsul (in functie de cod):" << endl;
	cout << "1. Lalea rosie (cod:10)" << endl;
	cout << "2. Lalea galbena (cod:11)" << endl;
	cout << "3. Trandafir rosu (cod:12)" << endl;
	cout << "4. Trandafir alb (cod:13)" << endl;
	cout << "5. Bujor roz (cod:14)" << endl;
	cout << "6. Frezie galbena (cod:15)" << endl;
	cout << "7. Narcisa (cod:16)" << endl;
	cout << "8. Crin alb (cod:17)" << endl;
	cout << "9. Liliac mov (cod:18)" << endl << endl;
	cout << "" << endl;
}

int get_code() {
	cout << "Cod:";
	int code;
	cin >> code;
	while (code != 10 && code != 11 && code != 12 && code != 13 && code != 14 && code != 15 && code != 16 && code != 17 && code != 18) {
		cout << "Cod gresit! Introduceti altul:";
		cin >> code;
	}
	cout << "" << endl;
	cout << "**********************************" << endl;
	cout << "" << endl;
	return code;
}

int main()
{
	Product produse[] = {
		Product("Lalea rosie",10,5.00,100),
		Product("Lalea galbena",11,5.00,100),
		Product("Trandafir rosu",12,15.00,150),
		Product("Trandafir alb",13,15.00,135),
		Product("Bujor roz",14,10.00,55),
		Product("Frezie galbena",15,6.00,200),
		Product("Narcisa",16,10.00,65),
		Product("Crin alb",17,15.00,30),
		Product("Liliac mov",18,12.00,40)
	};
	const size_t nrProduse = sizeof(produse) / sizeof(Product);

	double price;
	ShoppingCart cart;
	Customer customer;
	Order order;

	show_menu();
	do {
		int code = get_code();
		for (int i = 0; i < nrProduse; i++) {
			if (code == produse[i].get_code())
				cout << produse[i];
		}
		cout << "" << endl;
		cout << "**********************************" << endl;
		cout << "" << endl;

		cout << "Adauga in cos?(da/nu): " << endl;
		char answer[5];
		char answer2[5];
		cin >> answer;
		if (strcmp(answer, "da\0") == 0) {
			int test;
			cout << "Numar de fire?" << endl;
			int nr_of_flowers;
			cin >> nr_of_flowers;
			for (int i = 0; i < nrProduse; i++) {
				if (code == produse[i].get_code())
					test = produse[i].minus_product(nr_of_flowers);
			}

			if (test == 1) {
				for (int i = 0; i < nrProduse; i++) {
					if (code == produse[i].get_code()) {
						price = produse[i].product_price();
						price = price * nr_of_flowers;
						cart.add_to_cart(price, &produse[i]);
					}
				}
				cout << "S-a adaugat cu succes!" << endl;
			}
			else {
				cout << endl;
				cout << "Nu mai exista destule fire! Reveniti in zilele urmatoare." << endl;
			}

		}
		cout << endl;
		cout << "Alege alt produs?(da/nu): " << endl;
		cin >> answer2;
		if (strcmp(answer2, "nu\0") == 0) {
			double total_price = cart.show_cart();
			ShoppingCart::sale(total_price);
			cout << endl << "Plasati comanda?(da/nu)" << endl;
			char answer3[5];
			cin >> answer3;
			if (strcmp(answer3, "da\0") == 0) {
				cout << "**********************************" << endl << endl;
				cout << "Introduceti informatiile dumneavoastra:" << endl << endl;
				cin >> customer;
				char* last_name = customer.get_last_name();
				char* first_name = customer.get_first_name();
				char* email = customer.get_email();
				cart.add_customer_info(last_name, first_name, email);
				cout << "Metoda de plata?(cash/card)" << endl;
				char answer4[5];
				cin >> answer4;
				if (strcmp(answer4, "card\0") == 0) {
					char Card_nr[20];
					int Expiration_day;
					int Expiration_month;
					char Cardholder_name[30];
					int cvc;
					cout << "Numarul cardului: ";
					cin >> Card_nr;
					cout << endl << "Ziua in care expira: ";
					cin >> Expiration_day;
					cout << endl << "Luna in care expira: ";
					cin >> Expiration_month;
					cout << endl << "Numele posesorului: ";
					cin >> Cardholder_name;
					cout << endl << "CVC: ";
					cin >> cvc;
					CreditCard creditcard(Card_nr, Expiration_day, Expiration_month, Cardholder_name, cvc);
					order.add_details(creditcard);
				}
				char country[10];
				char city[10];
				char street[10];
				int number;
				cout << endl << "Tara: ";
				cin >> country;
				cout << endl << "Orasul: ";
				cin >> city;
				cout << endl << "Strada: ";
				cin >> street;
				cout << endl << "Numar: ";
				cin >> number;
				Adress adress(country, city, street, number);
				order.add_details(adress);
				order.add_shoppingcart_details(&cart);
				cout << endl;
				cout << "**********************************" << endl << endl;
				cout << "Informatiile introduse pentru comanda dumneavoastra:" << endl;
				if (strcmp(answer4, "card\0") == 0) {
					cart.get_customer_info();
					order.get_card_details();
					order.get_adress_details();
				}
				else {
					cart.get_customer_info();
					order.get_adress_details();
				}
				cout << endl << "Comanda va fi livrata in urmatoarele zile." << endl;
				cout << endl << "Dati o nota la interactiunea cu floraria: " << endl;
				int nota;
				cin >> nota;
				feedback program(nota);
				cout << "Vreti sa dati aceeasi nota pentru varietatea produselor si pentru preturi?(da/nu)" << endl;
				char answer5[5];
				cin >> answer5;
				if (strcmp(answer5, "da\0") == 0) {
					feedback products;
					products = program;
					feedback prices;
				}

				cout << "Multumim ca ati cumparat de la noi!" << endl;
				return 0;
			}
			else {
				cout << endl;
				cout << "Cosul dumneavoastra a fost sters. Va mai asteptam pe la noi!" << endl;
				cout << endl;
				return 0;
			}
		}


	} while (true);

	return 0;
}
