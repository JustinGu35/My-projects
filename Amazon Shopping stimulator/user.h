#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include "review.h"

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type,unsigned long long hashcode);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);

    //function for hash
    unsigned long long getHashcode() const;
    void setHashcode(unsigned long long newHashcode);
    unsigned long long hashFunction(std::string password);

    //function for reveiw list
    void addReviewTo(Review inReview);
    std::vector<Review> getUserReviewList() const;



private:
    unsigned long long hashcode_;
    std::string name_;
    double balance_;
    int type_;

    //data member for reveiew list for easier accessing in problem3
    std::vector<Review> userReviewList;
};
#endif
