#include <iostream>
#include <cstring>

using namespace std;

class Book{
protected:
    char ISBN[21];
    char title[51];
    char author[31];
    float price;
public:
    Book(char *ISBN,char *title, char *author,float price){
        strcpy(this->ISBN,ISBN);
        strcpy(this->author,author);
        strcpy(this->title,title);
        this->price=price;
    }
    Book(const Book &other){
        strcpy(this->ISBN,other.ISBN);
        strcpy(this->author,other.author);
        strcpy(this->title,other.title);
        this->price=other.price;
    }
     bool operator > (const Book &other){
        return (this->price>other.price);
    }
    virtual float bookPrice(){
        return price;
    }
    friend ostream &operator<<(ostream &os, Book &book) {
        os  << book.ISBN << ": " << book.title << ", " << book.author << " " << book.bookPrice()<<endl;
        return os;
    }

    const char *getISBN() const {
        return ISBN;
    }
    void setISBN(char *ISBN){
        strcpy(this->ISBN,ISBN);
    }
   virtual bool isOnlineBook(){
       return false;
    }

    const char *getTitle() const {
        return title;
    }

    const char *getAuthor() const {
        return author;
    }
};
class OnlineBook : public Book{
private:
    char *url;
    int size;
public:
    OnlineBook(char *ISBN,char *title,char *author,float price,char *url,int size) : Book(ISBN,title,author,price){
        this->url=new char[strlen(url)+1];
        strcpy(this->url,url);
        this->size=size;
    }
    OnlineBook(const OnlineBook &other) : Book(other){
        this->url=new char[strlen(other.url)+1];
        strcpy(this->url,other.url);
        size=other.size;
    }
    float bookPrice(){
        if(size>20){
            return (price+price*0.2);
        }
        return price;
    }
    friend ostream &operator<<(ostream &os,OnlineBook &book) {
        os  << book.ISBN << ": " << book.title << ", " << book.author << " " << book.bookPrice() <<endl;
        return os;
    }
    bool isOnlineBook(){
            return true;
    }
    /*~OnlineBook(){
     //Ne trebat destruktori valjda oti u main se unistuva
        //   delete [] url;
    }*/
};
class PrintBook : public Book{
private:
    float weight;
    bool stock;
public:
    PrintBook(char *ISBN,char *title,char *author,float price,float weight,bool stock) : Book(ISBN,title,author,price){
        this->weight=weight;
        this->stock=stock;
    }
    PrintBook(const PrintBook &other) : Book(other){
        this->weight=other.weight;
        this->stock=other.stock;
    }
    float bookPrice(){
        if(this->weight>0.7){
            return (price+price*0.15);
        }
        return price;
    }

    friend ostream &operator<<(ostream &os, PrintBook &book) {
        os  << book.ISBN << ": " << book.title << ", " << book.author << " " << book.bookPrice()<<endl;
        return os;
    }
    ~PrintBook(){}

};

void mostExpensiveBook(Book **book, int n);

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}

void mostExpensiveBook(Book **book, int n) {
int count,maxi=0,online=0,printb=0;
float maxprice=0.0;
    for (int i = 0; i < n; ++i) {
        if(book[i]->isOnlineBook()){
            online++;
        }else {
            printb++;
        }
        if(book[i]->bookPrice()>maxprice){
            maxprice=book[i]->bookPrice();
            maxi=i;
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<printb<<endl;
    cout<<"The most expensive book is: \n"<<book[maxi]->getISBN()<<":"<<" "<<book[maxi]->getTitle()<< ", " <<book[maxi]->getAuthor()<<" "<<book[maxi]->bookPrice()<<endl;
}
