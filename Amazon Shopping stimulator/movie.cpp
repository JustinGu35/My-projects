#include"movie.h"

Movie::Movie(const std::string category, const std::string name, double price,
         int qty, const std::string inGenre, const std::string inRating):
         Product(category,name,price,qty), genre(inGenre),rating(inRating)
{
}

Movie::~Movie()
{
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> result;
    //convert to lower case
    std::string nameLow=convToLower(getName());
    std::string genreLow=convToLower(genre);
    //get the keywords
    result=parseStringToWords(nameLow);
    result.insert(genreLow);
    return result;
}
std::string Movie::displayString() const
{
    std::string output;
    std::stringstream temp;

    output=getName();
    output+="\n";
    output+="Genre: "+ genre+" Rating: "+rating+"\n";
    temp<<getPrice()<<" "<<getQty()<<" left."<<"\n"<<"Rating: "<<aveRat<<"\n";
    output+=temp.str();
    return output;
}
void Movie::dump(std::ostream& os) const
{
    os<<"movie"<<"\n"<<getName()<<"\n"<<getPrice()<<"\n"<<getQty()<<"\n"
            <<genre<<"\n"<<rating<<std::endl;
}