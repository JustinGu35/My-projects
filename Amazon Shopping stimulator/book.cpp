#include"book.h"

Book::Book(const std::string category, const std::string name, double price,
         int qty, const std::string inISBN, const std::string inAuthor):
         Product(category,name,price,qty), ISBN(inISBN),author(inAuthor)
{

}

Book::~Book()
{
    
}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> result;
    //get the lower case
    std::string authorLow= convToLower(author);
    std::string nameLow=convToLower(getName());
    std::string inputS=authorLow+" "+nameLow;
    //get the keywords
    result= parseStringToWords(inputS);
    result.insert(ISBN);

    return result;
}

std::string Book::displayString() const
{
    std::string output;
    std::stringstream temp;
    //get name, author and ISBN first
    output=getName();
    output+="\n";
    output+="Author: "+author+ " ISBN: "+ISBN;
    output+="\n";
    //use stringstream to get numbers
    temp<<getPrice()<<" "<<getQty()<<" "<<"left."<<"\n"<<"Rating: "<<aveRat<<"\n";
    output+=temp.str();

    return output;
}

void Book::dump(std::ostream& os) const
{
    os<<"book"<<"\n"<<getName()<<"\n"<<getPrice()<<"\n"<<getQty()
            <<"\n"<<ISBN<<"\n"<<author<<std::endl;
}