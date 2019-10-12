#include"product.h"
#include"util.h"
#include<sstream>

class Clothing : public Product
{
public:
    Clothing(const std::string category, const std::string name, double price,
         int qty, const std::string inBrand, const std::string inSize);
    ~Clothing();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string brand;
    std::string size;

};