#include"datastore.h"
#include<map>
#include"util.h"
#include<deque>
#include<sstream>
#include<cstdlib>
#include"heap.h"
#include <fstream>

struct CompRate {
  bool operator()(Product* a, Product* b)
  {
    return a->getRat()>b->getRat();
    
  }
};

struct CompName {
  bool operator()(Product* a, Product* b)
  {
    return a->getName()<b->getName();
    
  }
};

struct CompDate {
  bool operator()(Review a, Review b)
  {
    return a.date>b.date;
  }
};

struct CompPair {
  bool operator()(std::pair<std::string,double> a,std::pair<std::string,double> b)
  {
      return a.second >b.second;
  }
};

class MyDataStore: public DataStore 
{
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    //the second int for search is the type of r sort, 0 for rate,1 for name
    std::vector<Product*> search(std::vector<std::string>& terms, int type, int sortType);
    void dump(std::ostream& ofile);
    void addCart(int num,std::vector<Product*> hits);
    void viewCart();
    void buyCart();
    void addReview(const std::string& prodName,
			   int rating,
			   const std::string& username,
			   const std::string& date,
			   const std::string& review_text);
    void logIn(std::string inUser,std::string password);
    void logOut();
    void testADD(std::stringstream& input,std::vector<Product*> hits);//text if the review is valid then add it
    void viewReview(std::vector<Product*> hits,int num);

    //for recommandation
    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);

    double calculateBasicSimilarity(User* user1,User* user2);
    void createAdjacenctList();
    void createRefine();

    void doRecommendation();
private:
    std::map<std::string,Product*> prodMap;
    std::map<std::string,User*> userMap;
    std::map<std::string,std::deque<Product*>* > cart;
    User* logged;

    //new member function for similarity

    // adjacencylist with pair of username and the map of relative basic similarity to other username
    //std::map<std::string,std::map<std::string,double> >* adjacencyList;
    std::map<std::string,double>* refinedDistance;

};