#include"clothing.h"

Clothing::Clothing(const std::string category, const std::string name, double price,
         int qty, const std::string inBrand, const std::string inSize):
         Product(category,name,price,qty),brand(inBrand), size(inSize)
{

}


Clothing::~Clothing()
{

}
std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> result;
    //convert to lower case
    std::string nameLow=convToLower(getName());
    std::string brandLow=convToLower(brand);
    std::string inputS=nameLow+" "+brandLow;
    //get the keywords
    result=parseStringToWords(inputS);
    return result;
}
std::string Clothing::displayString() const
{
    std::string output;
    std::stringstream temp;

    output=getName();
    output+="\n";
    output+="Size: "+ size+" Brand: "+brand+"\n";
    temp<<getPrice()<<" "<<getQty()<<" left."<<"\n"<<"Rating: "<<aveRat<<"\n";
    output+=temp.str();
    return output;
}

void Clothing::dump(std::ostream& os) const
{
    os<<"clothing"<<"\n"<<getName()<<"\n"<<getPrice()<<"\n"<<getQty()<<"\n"
            <<size<<"\n"<<brand<<std::endl;
}