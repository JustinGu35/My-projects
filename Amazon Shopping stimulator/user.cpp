#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type,unsigned long long hashcode) :
    name_(name), balance_(balance), type_(type), hashcode_(hashcode)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}

unsigned long long User::getHashcode() const
{
    return hashcode_;
}

void User::setHashcode(unsigned long long newHashcode)
{
    hashcode_=newHashcode;
}

unsigned long long User::hashFunction(std::string password)
{
    //check if the length is right
    if(password.size()>8 || password.size()==0)
    {
       cout<<"incorrect password length"<<endl;
       return -1; 
    }
    unsigned long long total=0;
    //calculate the total number 
    for(int i=0;i<(int)password.size();i++)
    {
        total*=128;
        total+=(unsigned long long)password[i];
    }
    //get the four digit
    unsigned int four[4];
    for(int i=3;i>=0;i--)
    {
        unsigned long long temp=total;
        for(int j=3;j>i;j--)
        {
            temp=temp/65521;
        }
        unsigned long long result=temp%65521;
        four[i]=result;
    }

    unsigned long long endResult=(unsigned long long)((45912*four[0]+35511*four[1]+
        65169*four[2]+4625*four[3])%65521);

    return endResult;
}

void User::addReviewTo(Review inReview)
{
    if(inReview.username==this->name_)
    {
        userReviewList.push_back(inReview);
    }
}

std::vector<Review> User::getUserReviewList() const
{
    return userReviewList;
}