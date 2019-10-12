#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"


#include "mydatastore.h"



using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;
    ReviewSectionParser* reviewSectionParser=new ReviewSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);
    parser.addSectionParser("reviews",reviewSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  LOGIN username password         "<<endl;
    cout << "  LOGOUT      "<<endl;
    cout << "  AND r/n term term ...                  " << endl;
    cout << "  OR r/n term term ...                   " << endl;
    cout << "  ADD search_hit_number     " << endl;
    cout << "  VIEWCART                  " << endl;
    cout << "  BUYCART                  " << endl;
    cout << "  ADDREV search_hit_number rating date review_text   "<<endl;
    cout << "  VIEWREV search_hit_number     "<<endl;
    cout << "  REC                            "<<endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string sortType;
                ss>>sortType;
                if(sortType=="r")
                {
                    string term;
                    vector<string> terms;
                    while(ss >> term) {
                        term = convToLower(term);
                        terms.push_back(term);
                    }
                    hits = ds.search(terms, 0,0);
                    displayProducts(hits);
                }
                else if(sortType=="n")
                {
                    string term;
                    vector<string> terms;
                    while(ss >> term) {
                        term = convToLower(term);
                        terms.push_back(term);
                    }
                    hits = ds.search(terms, 0,1);
                    displayProducts(hits);
                }
            }
            else if ( cmd == "OR" ) {
                string sortType;
                ss>>sortType;
                if(sortType=="r")
                {
                    string term;
                    vector<string> terms;
                    while(ss >> term) {
                        term = convToLower(term);
                        terms.push_back(term);
                    }
                    hits = ds.search(terms, 1,0);
                    displayProducts(hits);
                }
                else if(sortType=="n")
                {
                    string term;
                    vector<string> terms;
                    while(ss >> term) {
                        term = convToLower(term);
                        terms.push_back(term);
                    }
                    hits = ds.search(terms, 1,1);
                    displayProducts(hits);                    
                }
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if(cmd=="ADD")
            {
                int theHit;
                if(ss>>theHit)
                {
                    ds.addCart(theHit,hits);
                }
            }
            else if(cmd=="VIEWCART")
            {
                ds.viewCart();
            }
            else if(cmd=="BUYCART")
            {
                ds.buyCart();
            }
            else if(cmd=="LOGIN")
            {
                string username;
                string password;
                if(ss>>username)
                {
                    if(ss>>password)
                    {
                        ds.logIn(username,password);
                    }
                }
            }
            else if(cmd=="LOGOUT")
            {
                ds.logOut();
            }
            else if(cmd=="ADDREV")
            {
                ds.testADD(ss,hits);
            }
            else if(cmd=="VIEWREV")
            {
                int hit;
                if(ss>>hit)
                {
                    ds.viewReview(hits,hit);
                }
            }
            else if(cmd=="REC")
            {
                ds.doRecommendation();
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
