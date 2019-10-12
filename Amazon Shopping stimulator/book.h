#include"product.h"
#include"util.h"
#include<sstream>

class Book : public Product
{
public:
    Book(const std::string category, const std::string name, double price,
         int qty, const std::string inISBN, const std::string inAuthor);
    ~Book();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string ISBN;
    std::string author;

};