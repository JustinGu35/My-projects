#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) :
    name_(name),
    price_(price),
    qty_(qty),
    category_(category),
    aveRat(0.00),
    reviewList()
{

}

Product::~Product()
{

}


double Product::getPrice() const
{
    return price_;
}

std::string Product::getName() const
{
    return name_;
}

void Product::subtractQty(int num)
{
    qty_ -= num;
}

int Product::getQty() const
{
    return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

void Product::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}

void Product::addReviewIn(Review inReview)
{
    reviewList.push_back(inReview);

    //work for average rate below
    int size=(int)reviewList.size();
    double sum=0.00;
    for(int i=0;i<size;i++)
    {
        sum+=(double)reviewList[i].rating;
    }
    sum=sum/size;
    sum=round(sum*100);
    sum=sum/100;
    aveRat=sum;
}

std::vector<Review> Product::getReviewList() const
{
    return reviewList;
}


void Product::dumpReview(std::ostream& os) const
{
    std::vector<Review> temp=getReviewList();
    CompTime c1;
    mergeSort(temp,c1);
    for(int i=0;i<(int)temp.size();i++ )
    {
        os<<name_<<endl;
        os<<temp[i].rating<<" "<<temp[i].username<<" "<<temp[i].date
            <<" "<<temp[i].reviewText<<endl;
    }

}

double Product::getRat() const
{
    return aveRat;
}