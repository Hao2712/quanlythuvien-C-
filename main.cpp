#include <iostream>
#include <string>
#include <vector>

class Book {
    protected:
        std::string title;
        std::string author;
        int pubYear;
        float price;

    public:
        Book(std::string t, std::string a, int pY, float p) : title(t), author(a), pubYear(pY), price(p) {}
        virtual void displayBookInfo();
        std::string getTitle() const {
            return title;
        }
};

void Book::displayBookInfo() {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author:  " << author << std::endl;
    std::cout << "Publication year: " << pubYear << std::endl;
    std::cout << "Price " << price << std::endl;
}

class Library {
    private:
        std::vector<Book*> books; // danh sách sách trong thư viện

    public:
        void addBook(Book* book);
        void displayBooks();
        void searchBookByTitle(std::string title);

        ~Library() {
            for(auto book : books) {
                delete book;
            }
            books.clear();
        }
};

void Library::addBook(Book* book) {
    books.push_back(book);
}

void Library::displayBooks() {
    std::cout << "Danh sach cac sach trong thu vien:\n" << std::endl;
    for(auto book : books) {
        book->displayBookInfo();
        std::cout << "---------------------\n";
    }
}

void Library::searchBookByTitle(std::string title) {
    bool found = false;
    for(auto book : books) {
        if(book->getTitle() == title) {
            std::cout << "Thong tin sach tim duoc" << std::endl;
            book->displayBookInfo();
            std::cout << "---------------------\n";
            found = true;
        }
    }
    if(!found) {
        std::cout << "Khong tim thay sach" << std::endl;
    }
}

class DigitalBook : public Book {
    private:
        float fileSize;

    public:
        DigitalBook(std::string t, std::string a, int pY, float p, float fs) : Book(t, a, pY, p), fileSize(fs) {}
        void displayBookInfo() override;
};

void DigitalBook::displayBookInfo() {
    Book::displayBookInfo();
    std::cout << "File size: " << fileSize << std::endl;
}

int main() {
    Library library;
    int choice;

    do {
        // Hiển thị menu
        std::cout << "Menu:\n";
        std::cout << "1. Them sach\n";
        std::cout << "2. Them sach dien tu\n";
        std::cout << "3. Hien thi tat ca sach\n";
        std::cout << "4. Tim kiem sach theo ten\n";
        std::cout << "5. Thoat\n";
        std::cout << "Chon chuc nang: ";
        std::cin >> choice;
        std::cin.ignore();  // Dùng để loại bỏ ký tự '\n' còn lại trong bộ đệm

        switch (choice) {
            case 1: {
                // Thêm sách mới
                std::string title, author;
                int pubYear;
                float price;

                std::cout << "Nhap tieu de sach: ";
                std::getline(std::cin, title);
                std::cout << "Nhap tac gia: ";
                std::getline(std::cin, author);
                std::cout << "Nhap nam xuat ban: ";
                std::cin >> pubYear;
                std::cout << "Nhap gia sach: ";
                std::cin >> price;
                std::cin.ignore();  // Loại bỏ ký tự '\n' còn lại trong bộ đệm

                Book* newBook = new Book(title, author, pubYear, price);
                library.addBook(newBook);
                std::cout << "Sach đa đuoc them vao thu vien.\n";
                break;
            }
            case 2: {
                // Thêm sách mới
                std::string title, author;
                int pubYear;
                float price, fileSize;

                std::cout << "Nhap tieu de sach: ";
                std::getline(std::cin, title);
                std::cout << "Nhap tac gia: ";
                std::getline(std::cin, author);
                std::cout << "Nhap nam xuat ban: ";
                std::cin >> pubYear;
                std::cout << "Nhap gia sach: ";
                std::cin >> price;
                std::cout << "Nhap dung luong file sach: ";
                std::cin >> fileSize;
                std::cin.ignore();  // Loại bỏ ký tự '\n' còn lại trong bộ đệm

                DigitalBook* newDigitalBook = new DigitalBook(title, author, pubYear, price, fileSize);
                library.addBook(newDigitalBook);
                std::cout << "Sach đa đuoc them vao thu vien.\n";
                break;
            }
            case 3: {
                // Hiển thị tất cả sách trong thư viện
                library.displayBooks();
                break;
            }
            case 4: {
                // Tìm kiếm sách theo tên
                std::string searchTitle;
                std::cout << "Nhap ten sach can tim: ";
                std::getline(std::cin, searchTitle);
                library.searchBookByTitle(searchTitle);
                break;
            }
            case 5:
                std::cout << "Thoat chuong trinh.\n";
                break;
            default:
                std::cout << "Lua chon không hop le. Vui long thu lai.\n";
        }
    } while (choice != 5);  // Tiếp tục hiển thị menu cho đến khi người dùng chọn thoát

    return 0;
}