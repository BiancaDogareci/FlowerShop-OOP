#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <exception>
#include <limits>
#include <stdlib.h>
#include <algorithm>
#include <random>
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
	vector<unique_ptr<Product>> v_product_code;
    vector<double> v_prices;
    Customer customer;
public:
	ShoppingCart() : customer() {}

	void add_to_cart(double price, unique_ptr<Product> product) {
        v_product_code.push_back(move(product));
        v_prices.push_back(price);
    }

	double show_cart() {
        cout << endl;
        cout << "***************************************************************************************" << endl;
        cout << "Cosul dumneavoastra de cumparaturi:" << endl << endl;

        double total_price = 0;
        for (size_t i = 0; i < v_prices.size(); i++) {
            total_price += v_prices[i];
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

class PaymentException : public std::exception
{
private:
    const char* message;

public:
    PaymentException(const char* msg) : message(msg) {}

    const char* getMessage() const
    {
        return message;
    }
};

class CreditCard {
private:
	char card_nr[20];
	int expiration_year;
	int expiration_month;
	char cardholder_name[30];
	int CVC;
public:
	CreditCard() : card_nr(), expiration_year(), expiration_month(), cardholder_name(), CVC()
	{
	}
	CreditCard(char Card_nr[20], int Expiration_year, int Expiration_month, char Cardholder_name[30], int cvc) {
		strcpy(card_nr, Card_nr);
		expiration_year = Expiration_year;
		expiration_month = Expiration_month;
		strcpy(cardholder_name, Cardholder_name);
		CVC = cvc;
	}
	~CreditCard() {
	}
	bool process_payment(){
        int ok = 1;
        if (strlen(card_nr) != 16)
            throw PaymentException("Numarul cardului trebuie sa contina 16 cifre.");
        for (int ch=0; ch<strlen(card_nr); ch++)
            if (card_nr[ch]<'0' || card_nr[ch]>'9')
                throw PaymentException("Numarul cardului trebuie sa contina numai cifre.");
        if (expiration_year < 23)
            throw PaymentException("Card expirat.");
        else if (expiration_year == 23)
            if (expiration_month < 4)
                throw PaymentException("Card expirat.");
        if (expiration_month < 1 || expiration_month >12)
            throw PaymentException("Luna trebuie sa fie intre 1-12.");
        if (CVC <100 || CVC>999)
            throw PaymentException("CVC trebuie sa aiba 3 cifre.");
        return true;
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
		card.expiration_year = creditcard.expiration_year;
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
		cout << "Data expirarii: " << card.expiration_year << "/" << card.expiration_month << endl;
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

template<typename T>
class Feedback {
private:
    size_t size;
    T* data;

public:
    Feedback() {
        data = nullptr;
        size = 0;
    }

    Feedback(const T& value) {
        size = 1;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = value;
    }

    Feedback(const Feedback& other) {
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    void operator=(const Feedback& other) {
        if (data != nullptr)
            delete[] data;
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    template<typename U>
    void showFeedback(const Feedback<U>& feedback) const {
        cout << "Feedback: " << feedback.data[0] << endl;
    }

    ~Feedback() {
        if (data != nullptr)
            delete[] data;
    }

};


class Bouquet {
public:
    Bouquet(string wrapping_color_,string wrapping_pattern_){
        wrapping_color=wrapping_color_;
        wrapping_pattern=wrapping_pattern_;
    }
    string getwrapping_color(){return wrapping_color;}
    string getwrapping_pattern(){return wrapping_pattern;}
    virtual ~Bouquet() {}
protected:
    virtual double compute_price_with_sale() const=0;
    virtual double compute_number_of_flowers() const=0;
    virtual double show_price() const=0;
    string wrapping_color;
    string wrapping_pattern;

    friend void print_bouquet_details(Bouquet& bouquet);
};

class Spring_Bouquet:public Bouquet{
private:
    double price;
    int Sunflowers;
    int Red_Alstroemeria;
    int Green_Button_Poms;
    int Purple_Monte_Casino;
    static int num_spring_bouquets_created;
public:
    Spring_Bouquet(double price_, int Sunflowers_, int Red_Alstroemeria_, int Green_Button_Poms_, int Purple_Monte_Casino_, string wrapping_color_, string wrapping_pattern_)
        : Bouquet(wrapping_color_, wrapping_pattern_), price(price_), Sunflowers(Sunflowers_), Red_Alstroemeria(Red_Alstroemeria_), Green_Button_Poms(Green_Button_Poms_), Purple_Monte_Casino(Purple_Monte_Casino_) {
            num_spring_bouquets_created++;
        }

    virtual double compute_price_with_sale() const override{
        return price-(price*5/100);
    }
    virtual double compute_number_of_flowers() const override{
        return Sunflowers+Red_Alstroemeria+Green_Button_Poms+Purple_Monte_Casino;
    }
    virtual double show_price() const override{
        return price;
    }
    void set_wrapping_color(string wrapping_color_){
        wrapping_color=wrapping_color_;
    }
    void set_wrapping_pattern(string wrapping_pattern_){
        wrapping_pattern=wrapping_pattern_;
    }
    static int get_num_spring_bouquets_created() {
      return num_spring_bouquets_created;
    }
};

class Summer_Bouquet:public Bouquet{
private:
    double price;
    int Purple_Aster;
    int Yellow_Santini_Chrysanthemum;
    int Yellow_Alstroemeria;
    int Pink_Carnation;
    int Robusta;
    static int num_summer_bouquets_created;
public:
    Summer_Bouquet(double price_, int Purple_Aster_, int Yellow_Santini_Chrysanthemum_, int Yellow_Alstroemeria_, int Pink_Carnation_, int Robusta_, string wrapping_color_, string wrapping_pattern_)
        : Bouquet(wrapping_color_, wrapping_pattern_), price(price_), Purple_Aster(Purple_Aster_), Yellow_Santini_Chrysanthemum(Yellow_Santini_Chrysanthemum_), Yellow_Alstroemeria(Yellow_Alstroemeria_), Pink_Carnation(Pink_Carnation_), Robusta(Robusta_) {
        num_summer_bouquets_created++;
    }

    virtual double compute_price_with_sale() const override{
        return price-(price*5/100);
    }
    virtual double compute_number_of_flowers() const override{
        return Purple_Aster+Yellow_Alstroemeria+Yellow_Santini_Chrysanthemum+Pink_Carnation+Robusta;
    }
    virtual double show_price() const override{
        return price;
    }
    void set_wrapping_color(string wrapping_color_){
        wrapping_color=wrapping_color_;
    }
    void set_wrapping_pattern(string wrapping_pattern_){
        wrapping_pattern=wrapping_pattern_;
    }
    static int get_num_summer_bouquets_created() {
      return num_summer_bouquets_created;
    }
};

int Spring_Bouquet::num_spring_bouquets_created = 0;

int Summer_Bouquet::num_summer_bouquets_created = 0;

void print_bouquet_details(Bouquet& bouquet)
{
    cout << "***************************************************************************************" << endl<<endl;
    cout<<"Buchetul ales contine "<< bouquet.compute_number_of_flowers()<<" flori si este redus 5%. Dupa reducere el costa "<<bouquet.compute_price_with_sale()<<" lei, iar inainte costa "
    <<bouquet.show_price()<<" lei."<<endl<<endl;
}

void show_wrapping_details(Bouquet& bouquet){
        cout<<"Ati ales culoarea -"<<bouquet.getwrapping_color()<<"- si modelul -"<<bouquet.getwrapping_pattern()<<"- pentru folie."<<endl<<endl;
    }

class text{
protected:
    string name;
    string font;
    string message;
public:
    text(string name_, string font_, string message_) : name(name_), font(font_), message(message_) {}
    string get_name() { return name; }
    string get_font() { return font; }
    string get_message() { return message; }
};

class details{
protected:
    string shape;
    string color;
public:
    details(string shape_, string color_) : shape(shape_), color(color_) {}
    string get_shape() { return shape; }
    string get_color() { return color; }
};

class Greeting_Card:public text,public details{
public:
    Greeting_Card(string name_, string font_, string message_, string shape_, string color_)
        : text(name_, font_, message_), details(shape_, color_) {}
    void print_card_details(){
        cout<<endl;
        cout << "***************************************************************************************" << endl;
        cout<<"     Informatii pentru felicitare:"<<endl;
        cout << "Numele celui pentru care e felicitarea: " << get_name() << endl;
        cout << "Fontul textului: " << get_font() << endl;
        cout << "Continut: " << get_message() << endl;
        cout << "Forma: " << get_shape() << endl;
        cout << "Culoare: " << get_color() << endl;
    }
    static void Greetings(){
        cout<<endl<<"Niste alegeri minunate!"<<endl<<endl;
        cout << "***************************************************************************************" << endl;
    }
};

class Founders {
public:
    virtual void show_name() = 0;
    virtual void story()=0;
    virtual ~Founders() {} // Destructor virtual
};

class Founder_1 : public Founders {
private:
    string name;
    int years_of_experience;
    static Founder_1* instance; // Static instance variable

    // Private constructor to prevent direct instantiation
    Founder_1(string n, int y) : name(n), years_of_experience(y) {}

public:
    static Founder_1* getInstance(string n, int y) {
        if (instance == nullptr) {
            instance = new Founder_1(n, y);
        }
        return instance;
    }

    void show_name() override { cout << "    1. " << name << endl; }
    void story() override {
        cout << endl
             << "\"Am iubit florile de cand eram inca un copil. Imi amintesc de zilele de vara in care admiram florile din gradina bunicii si invatam cum sa le ingrijesc. Aceasta florarie a fost un vis al meu inca de atunci.\""
             << endl;
    }

    static void destroyInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
};

Founder_1* Founder_1::instance = nullptr;

class Founder_2 : public Founders {
private:
    string name;
    int years_of_experience;
public:
    Founder_2(string n, int y) : name(n), years_of_experience(y) {}
    void show_name() override { cout <<"    2. "<<name<<endl; }
    void story() override{
        cout<<endl<<"\"Am inceput sa admir florile cand m-am mutat prima oara de acasa de la parinti. Simteam ca locuintei mele ii lipseste ceva si mi-am dat seama ca acest lucru erau florile. Cu delicatetea si frumusetea lor ele fac orice loc primitor.\""<<endl;
    }
};

class Founder_3 : public Founders {
private:
    string name;
    int years_of_experience;
public:
    Founder_3(string n, int y) : name(n), years_of_experience(y) {}
    void show_name() override { cout <<"    3. "<<name<<endl; }
    void story() override{
        cout<<endl<<"\"Iubirea pentru flori a inceput de cand stateam in parc dupa scoala si admiram florile. Am mers acolo o data, de doua ori... pana ce a devenit un obicei. Ele mi-au adus intotdeauna liniste si fericire in suflet si mi-am dorit sa impartasesc aceste sentimente si cu alte persoane printr-o florarie.\""<<endl;
    }
};

class Founder_4 : public Founders {
private:
    string name;
    int years_of_experience;
public:
    Founder_4(string n, int y) : name(n), years_of_experience(y) {}
    void show_name() override { cout << "    4. "<<name<< endl; }
    void story() override{
        cout<<endl<<"\"Inca imi amintesc cum mama mea ingrijea zilnic toate florile din gradina si din casa, cum trebuia sa o ajut si eu uneori si nu imi placea la inceput. Dupa ce am crescut si eram la liceu, incepuse sa imi faca placere sa ingrijesc florile. Aceasta placere s-a transformat in visul de a infiinta aceasta florarie.\""<<endl;
    }
};

void show_title(){
    cout << "***************************************************************************************" << endl;
	cout << "**                               Bianca's Flower Shop                                **" << endl;
	cout << "***************************************************************************************" << endl;
	cout << endl;
}

void show_menu() {
	cout << endl;
	cout << "Alege produsul (in functie de cod):" << endl;
	cout << "1. Lalea rosie (cod=1)" << endl;
	cout << "2. Lalea galbena (cod=2)" << endl;
	cout << "3. Trandafir rosu (cod=3)" << endl;
	cout << "4. Trandafir alb (cod=4)" << endl;
	cout << "5. Bujor roz (cod=5)" << endl;
	cout << "6. Frezie galbena (cod=6)" << endl;
	cout << "7. Narcisa (cod=7)" << endl;
	cout << "8. Crin alb (cod=8)" << endl;
	cout << "9. Liliac mov (cod=9)" << endl << endl;
	cout << "" << endl;
}

void show_types_of_bouquets(){
    cout<<"Alege buchetul dorit din cele de mai jos:"<<endl;
    cout<<endl;
    cout << "1. Buchet flori de primavara (cod=1)" << endl;
    cout<<"    Contine:"<<endl;
    cout<<"      -5 fire de floarea soarelui"<<endl;
    cout<<"      -5 fire de alstroemeria rosie"<<endl;
    cout<<"      -5 fire de dianthus verde"<<endl;
    cout<<"      -6 fire de aster monte casino mov"<<endl;
	cout << "2. Buchet flori de vara (cod=2)" << endl;
	cout<<"    Contine:"<<endl;
    cout<<"      -4 fire de aster mov"<<endl;
    cout<<"      -5 fire de crizantema santini galbena"<<endl;
    cout<<"      -5 fire de alstroemeria galbena"<<endl;
    cout<<"      -4 fire de garoafa roz"<<endl;
    cout<<"      -5 fire de floare robusta"<<endl;
	cout << endl;
}

int get_code(const size_t nrProduse) {
    int code;
    bool ok = false;
    do {
        try {
            cout << "Cod: ";
            cin >> code;
            if (cin.fail()) { // daca citirea nu a reusit, se arunca o exceptie
                throw runtime_error("Input invalid: trebuie sa introduceti un numar intreg.");
            } else if (code < 1 || code > nrProduse) { // daca codul este in afara intervalului specificat, se arunca o exceptie
                throw out_of_range("Input invalid: codul trebuie sa fie intre 1 si " + to_string(nrProduse) + ".");
            } else {
                ok = true;
            }
        } catch (const exception& e) {
            cin.clear(); // se reseteaza flag-urile de eroare ale fluxului de intrare
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // se ignora input-ul curent pana la sfarsitul randului
            cout << "Eroare: " << e.what() << endl; // se afiseaza mesajul de eroare
        }
    } while (!ok); // repetam pana cand un cod valid este introdus

    cout << "***************************************************************************************" << endl;
    cout << endl;
    return code;
}

int main()
{
	Product produse[] = {
		Product("Lalea rosie",1,5.00,100),
		Product("Lalea galbena",2,5.00,100),
		Product("Trandafir rosu",3,15.00,150),
		Product("Trandafir alb",4,15.00,135),
		Product("Bujor roz",5,10.00,55),
		Product("Frezie galbena",6,6.00,200),
		Product("Narcisa",7,10.00,65),
		Product("Crin alb",8,15.00,30),
		Product("Liliac mov",9,12.00,40)
	};
	const size_t nrProduse = sizeof(produse) / sizeof(Product);

	double price;
	ShoppingCart cart;
	Customer customer;
	Order order;

	show_title();
	int answer5;
    cout<<"Alegeti '1' pentru un buchet personalizat sau '0' pentru unul standard: ";
    cin>>answer5;

	if(answer5 == 1){
        do {
            show_menu();
            int code = get_code(nrProduse);

            for (int i = 0; i < nrProduse; i++) {
                if (code == produse[i].get_code())
                    cout << produse[i];
            }
            cout << endl;
            cout << "***************************************************************************************" << endl;
            cout << endl;
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
                            unique_ptr<Product> productPtr = make_unique<Product>(produse[i]);
                            cart.add_to_cart(price, move(productPtr));
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
                system("cls");
                double total_price = cart.show_cart();
                ShoppingCart::sale(total_price);
                cout << endl << "Plasati comanda?(da/nu)" << endl;
                char answer3[5];
                cin >> answer3;
                if (strcmp(answer3, "da\0") == 0) {
                    system("cls");
                    cout << "***************************************************************************************" << endl;
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
                        system("cls");
                        bool payment_processed = false;
                        do {
                            char Card_nr[20];
                            int Expiration_day;
                            int Expiration_month;
                            char Cardholder_name[30];
                            int cvc;
                            cout << "Numarul cardului: ";
                            cin >> Card_nr;
                            cout << endl << "Anul in care expira: ";
                            cin >> Expiration_day;
                            cout << endl << "Luna in care expira: ";
                            cin >> Expiration_month;
                            cout << endl << "Numele posesorului: ";
                            cin >> Cardholder_name;
                            cout << endl << "CVC: ";
                            cin >> cvc;
                            CreditCard creditcard(Card_nr, Expiration_day, Expiration_month, Cardholder_name, cvc);
                            try {
                                payment_processed = creditcard.process_payment();
                                if (payment_processed) {
                                    cout << "Datele sunt corecte!" << endl;
                                }
                            }
                            catch (PaymentException &ex) {
                                cout << "Datele nu sunt corecte: " << ex.getMessage() << endl;
                                }
                            if(payment_processed==true){
                                order.add_details(creditcard);
                            }
                        } while (!payment_processed);

                    }
                    char country[10];
                    char city[10];
                    char street[10];
                    int number;
                    system("cls");
                    cout<<endl<<"Itroduceti informatii despre adresa:"<<endl;
                    cout << endl << "Tara: ";
                    cin >> country;
                    cout << endl << "Orasul: ";
                    cin >> city;
                    cout << endl << "Strada: ";
                    cin >> street;
                    cout << endl << "Numar: ";
                    cin >> number;
                    system("cls");
                    Adress adress(country, city, street, number);
                    order.add_details(adress);
                    order.add_shoppingcart_details(&cart);
                    cout << endl;
                    cout << "***************************************************************************************" << endl;
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
                    Feedback<int> program(nota);

                    vector<int> note_pt_feedback;
                    note_pt_feedback.push_back(nota);

                    cout << "Vreti sa dati aceeasi nota pentru varietatea produselor si pentru preturi?(da/nu)" << endl;
                    char answer5[5];
                    cin >> answer5;
                    if (strcmp(answer5, "da\0") == 0) {
                        Feedback<int> products;
                        products = program;
                        Feedback<int> prices;
                        prices=program;

                        cout<<endl<<"Note introduse: "<<endl;
                        program.showFeedback(program);
                        products.showFeedback(products);
                        prices.showFeedback(prices);
                        cout<<endl<<"Multumim pentru feedback!"<<endl<<endl;
                    }
                    else if(strcmp(answer5, "nu\0") == 0){
                        int nota;
                        cout << endl << "Dati o nota pentru varietatea produselor: " << endl;
                        cin >> nota;
                        note_pt_feedback.push_back(nota);

                        cout << endl << "Dati o nota pentru preturi: " << endl;
                        cin >> nota;
                        note_pt_feedback.push_back(nota);

                        sort(note_pt_feedback.begin(), note_pt_feedback.end());

                        cout<<"Notele introduse ordonate: "<<endl;
                        for (auto it = note_pt_feedback.begin(); it != note_pt_feedback.end(); ++it) {
                            cout << *it << " ";
                        }
                        cout << endl;

                    }

                    cout << "Vreti sa si scrieti un feedback pe langa notele date?(da/nu)" << endl;
                    cin >> answer5;
                    if (strcmp(answer5, "da\0") == 0){
                        cin.ignore();
                        string feedback;
                        cout << "Introduceti feedback-ul: ";
                        getline(cin,feedback);
                        Feedback<string> ftext(feedback);

                        cout<<endl<<"Multumim pentru feedback!"<<endl;
                        ftext.showFeedback(ftext);
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
            system("cls");

        } while (true);
	}
	else{
        char answer6[5];

        vector<Founders*> founders;
        founders.push_back(Founder_1::getInstance("Elvira Angelica", 20));
        founders.push_back(new Founder_2("Anastasia Florescu", 5));
        founders.push_back(new Founder_3("Otilia Radu", 18));
        founders.push_back(new Founder_4("Stefan Lazar", 4));
        do{
            show_types_of_bouquets();
            int code = get_code(2);
            system("cls");
            cout<<"Ce culoare vreti sa aiba folia buchetului? ";
            string wrapping_color;
            cin>>wrapping_color;
            cout<<endl<<endl;
            cout << "***************************************************************************************" << endl<<endl;
            cout<<"Ce model vreti sa aiba folia buchetului? "<<endl;
            cout<<"Alegeti din: inimi, dungi, buline, simplu, abstract, coffee stained -> ";
            string wrapping_pattern;
            cin>>wrapping_pattern;
            cout<<endl;
            if(code==1){
                system("cls");

                Spring_Bouquet spring(150.0,5,5,5,6,"","");
                spring.set_wrapping_color(wrapping_color);
                spring.set_wrapping_pattern(wrapping_pattern);
                print_bouquet_details(spring);

                cout << "***************************************************************************************" << endl<<endl;
                show_wrapping_details(spring);
                cout << "***************************************************************************************" << endl<<endl;
            }
            else if(code==2){
                system("cls");

                Summer_Bouquet summer(200.0,4,5,5,4,5,"","");
                summer.set_wrapping_color(wrapping_color);
                summer.set_wrapping_pattern(wrapping_pattern);
                print_bouquet_details(summer);

                cout << "***************************************************************************************" << endl<<endl;
                show_wrapping_details(summer);
                cout << "***************************************************************************************" << endl<<endl;
            }
            cout<<"Doriti si o felicitare personalizata?(da/nu):"<<endl;
            cin >> answer6;
            system("cls");
            if(strcmp(answer6,"da\0")==0){
                string name_,font_,message_,shape_,color_;
                cout<<"Numele celui pentru care e felicitarea: ";
                cin>>name_;
                cin.ignore(); // ignora caracterul newline din buffer
                cout<<endl<<"Fontul textului: ";
                getline(cin,font_);
                cout<<endl<<"Continutul felicitarii: ";
                getline(cin, message_);
                cout<<endl<<"Forma felicitarii: ";
                cin>>shape_;
                cout<<endl<<"Culoarea felicitarii: ";
                cin>>color_;
                Greeting_Card greeting_card(name_,font_,message_,shape_,color_);
                greeting_card.print_card_details();
                greeting_card.Greetings();
            }
            cout << "Alege alt produs?(da/nu): " << endl;
            cin >> answer6;
            system("cls");
        }while(strcmp(answer6, "da\0") == 0);
        if(Summer_Bouquet::get_num_summer_bouquets_created()+Spring_Bouquet::get_num_spring_bouquets_created()!=1)
            cout<<endl<<"Ati ales "<<Summer_Bouquet::get_num_summer_bouquets_created()+Spring_Bouquet::get_num_spring_bouquets_created()<<" buchete."<<endl<<endl;
        else
            cout<<endl<<"Ati ales "<<Summer_Bouquet::get_num_summer_bouquets_created()+Spring_Bouquet::get_num_spring_bouquets_created()<<" buchet."<<endl<<endl;

        cout<<endl<<"Fondatorii acestei florarii: "<<endl<<endl;
        for(auto emp : founders) {
            emp->show_name();
        }
        cout<<endl<<"De unde a venit pasiunea fiecaruia pentru flori?"<<endl;
        int e=1;
        while(e!=0){
            cout<<endl<<"     Alege cod sau random? (alege/random) "<<endl;
            char answer7[10];
            cin >> answer7;
            if(strcmp(answer7,"random\0")==0){
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<int> dist(1, 4);
                int randomNumber = dist(gen);
                e=randomNumber;
            }
            else{
                cout<<endl<<"     Alege codul unuia dintre ei pentru a afla sau 0 pentru a da skip: ";
                cin>>e;
            }

            while(e<0 || e>4){
                cout<<endl<<"    Cod gresit! Introduceti altul: ";
                cin>>e;
            }
            if(e==1){
                Founder_1* founder = dynamic_cast<Founder_1*>(founders[0]);
                founder -> story();
            }
            else if(e==2){
                Founder_2* founder = dynamic_cast<Founder_2*>(founders[1]);
                founder -> story();
            }
            else if(e==3){
                Founder_3* founder = dynamic_cast<Founder_3*>(founders[2]);
                founder -> story();
            }
            else if(e==4){
                Founder_4* founder = dynamic_cast<Founder_4*>(founders[3]);
                founder -> story();
            }
        }

        for(auto emp : founders) {
            delete emp;
        }
        founders.clear();
	}
	return 0;
}
