#include"mydatastore.h"
#include<limits>
#include<fstream>
#include<iomanip>

using namespace std;

MyDataStore::MyDataStore():logged(NULL)
{
    //adjacencyList=new std::map<std::string,std::map<std::string,double> >;
    refinedDistance=new std::map<std::string,double>;
}
MyDataStore::~MyDataStore()
{
    for(std::map<std::string,Product*>::iterator it=prodMap.begin();
        it!=prodMap.end();++it)
    {
        delete it->second;
    }
    for(std::map<std::string,User*>::iterator it=userMap.begin();
        it!=userMap.end();++it)
    {
        delete it->second;
    }
    if(cart.size()>0)
    {
        for(std::map<std::string,std::deque<Product*>*>::iterator it=cart.begin();
            it!=cart.end();++it)
        {
            delete it->second;
        }
    }
    delete refinedDistance;
    /*if(adjacencyList->size()>0)
    {
        delete adjacencyList;
    }*/

}
void MyDataStore::addProduct(Product* p)
{
    prodMap.insert(make_pair(p->getName(),p));
}
void MyDataStore::addUser(User* u)
{
    userMap.insert(make_pair(u->getName(),u));
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type,int sortType)
{
    std::vector<Product*> result;
    std::set<std::string> inKey;//the set of all keywords entered
    if(terms.size()==0)
    {
        return result;
    }
    for(unsigned int i=0;i<terms.size();i++)
    {
        inKey.insert(terms[i]);
    }
    if(type==0)
    {
        unsigned int size=inKey.size();
        for(std::map<std::string,Product*>::iterator it=prodMap.begin();
            it!=prodMap.end();++it)
        {
            std::set<std::string> compare;//the set of intersection
            std::set<std::string> prodInfo=it->second->keywords();
            compare=setIntersection(inKey,prodInfo);
            if(compare.size()==size)
            {
                result.push_back(it->second);
            }

        }
    }
    else if(type==1)
    {
        for(std::map<std::string,Product*>::iterator it=prodMap.begin();
            it!=prodMap.end();++it)
        {
            std::set<std::string> compare;//the set of intersection
            std::set<std::string> prodInfo=it->second->keywords();
            compare=setIntersection(inKey,prodInfo);
            if(compare.size()>0)
            {
                result.push_back(it->second);
            }
        }
    }
    //start sorting with rate
    if(sortType==0)
    {
        CompRate c1;
        mergeSort(result,c1);
    }
    //sort with name
    else
    {
        CompName c2;
        mergeSort(result,c2);
    }
    return result;
}
void MyDataStore::dump(std::ostream& ofile)
{
    ofile<<"<products>"<<std::endl;
    for(std::map<std::string,Product*>::iterator it=prodMap.begin();
            it!=prodMap.end();++it)
    {
        it->second->dump(ofile);
    }
    ofile<<"</products>"<<std::endl;
    ofile<<"<users>"<<std::endl;
    for(std::map<std::string,User*>::iterator it=userMap.begin();
            it!=userMap.end();++it)
    {
        it->second->dump(ofile);
    }
    ofile<<"</users>"<<std::endl;
    ofile<<"<reviews>"<<std::endl;
    for(std::map<std::string,Product*>::iterator it=prodMap.begin();
            it!=prodMap.end();++it)
    {
        it->second->dumpReview(ofile);
    }
    ofile<<"</reviews>"<<std::endl;
}

void MyDataStore::addCart(int num,std::vector<Product*> hits)
{
    if(logged==NULL)
    {
        std::cout<<"No current user"<<endl;
    }
    else
    {
        if(num>(int)hits.size()||num<=0)
        {
            std::cout<<"Invalid request"<<std::endl;
            return;
        }
        if(cart.find(logged->getName())!=cart.end())
        {
            cart[logged->getName()]->push_back(hits[num-1]);
        }
        else{
            std::deque<Product*>* temp=new std::deque<Product*>;
            temp->push_back(hits[num-1]);
            cart.insert(make_pair(logged->getName(),temp));
        }
    }
}




void MyDataStore::viewCart()
{
    if(logged==NULL)
    {
        std::cout<<"No current user"<<std::endl;
        return;
    }
    if(cart.find(logged->getName())==cart.end())
    {
        std::cout<<"Empty cart"<<std::endl;
        return;
    }
    for(int i=1;i<=(int)(cart[logged->getName()]->size());i++)
        {
            std::cout<<"Item "<<i<<std::endl;
            std::cout<<(*cart[logged->getName()])[i-1]->displayString();
        }
}


void MyDataStore::buyCart()
{
    if(logged==NULL)
    {
        std::cout<<"No current user"<<std::endl;
        return;
    }
    if(cart.find(logged->getName())==cart.end())
    {
        return;
    }
    for(int i=0;i<(int)(cart[logged->getName()]->size());i++)
    {
        if((logged->getBalance() > (*cart[logged->getName()])[i]->getPrice())&&
            (*cart[logged->getName()])[i]->getQty()>0)
        {
            logged->deductAmount((*cart[logged->getName()])[i]->getPrice());
            (*cart[logged->getName()])[i]->subtractQty(1);
            cart[logged->getName()]->erase(cart[logged->getName()]->begin()+i);
            i--;
        }
    }
}

//review adding 
void MyDataStore::addReview(const std::string& prodName,
			   int rating,
			   const std::string& username,
			   const std::string& date,
			   const std::string& review_text)
    {
        Review temp(rating,username,date,review_text,prodName);
        std::map<std::string,Product*>::iterator it;
        for(it=prodMap.begin();it!=prodMap.end();++it)
        {
            if(it->first==prodName)
            {
                std::map<std::string,User*>::iterator itU;
                for(itU=userMap.begin();itU!=userMap.end();++itU)
                {
                    if(itU->first==username)
                    {
                        it->second->addReviewIn(temp);
                        //new added for user,problem 3 hw8
                        itU->second->addReviewTo(temp);
                        break;
                    }
                }
                break;
            }
        }
    }

void MyDataStore::logIn(std::string inUser, std::string password)
{
    std::map<std::string,User*>::iterator it=userMap.find(inUser);
    if(it==userMap.end())
    {
        std::cout<<"Invalid login credentials"<<std::endl;
        return;
    }
    else
    {
        unsigned long long temp=it->second->hashFunction(password);
        if(temp==it->second->getHashcode())
        {
            logged=it->second;
            std::cout<<"User logged in"<<std::endl;
            //createRefine();
        }
        else
        {
            std::cout<<"Invalid login credentials"<<std::endl;
        }
    }
}
void MyDataStore::logOut()
{
    logged=NULL;
    refinedDistance->clear();
}

void MyDataStore::testADD(std::stringstream& input,std::vector<Product*> hits)
{
    int num;
    //check status of hit number
    if(input>>num)
    {
        if(num>(int)hits.size()||num<1)
        {
            std::cout<<"Invalid hit number"<<std::endl;
            return;
        }
        if(logged==NULL)
        {
            std::cout<<"No current user"<<std::endl;
            return;
        }
        //check status of rating
        int inRating;
        if(input>>inRating)
        {
            if(inRating>5||inRating<1)
            {
                std::cout<<"Invalid rating"<<std::endl;
                return;
            }
            //check status of date YYYY-MM-DD
            std::string inDate;
            if(input>>inDate)
            {
                if(inDate.length()==10&&inDate[4]=='-'&&inDate[7]=='-')
                {
                    for(int i=0;i<10;i++)
                    {
                        if(i!=4&&i!=7)
                        {
                            if(inDate[i]>'9'||inDate[i]<'0')
                            {
                                std::cout<<"Invalid date"<<std::endl;
                                return;
                            }
                        }
                    }
                    std::string monthTemp=inDate.substr(5,2);
                    std::string dateTemp=inDate.substr(8,2);
                    std::stringstream monthT(monthTemp);
                    std::stringstream dateT(dateTemp);
                    int MM,DD;
                    monthT>>MM;
                    dateT>>DD;
                    if(MM>12||MM<1)
                    {
                        std::cout<<"Invalid date"<<std::endl;
                        return;
                    }
                    if(MM==1||MM==3||MM==5||MM==7||MM==8||MM==10||MM==12)
                    {
                        if(DD>31)
                        {
                            std::cout<<"Invalid date"<<std::endl;
                            return;
                        }
                    }
                    else if(MM==2)
                    {
                        if(DD>28)
                        {
                            std::cout<<"Invalid date"<<std::endl;
                            return;
                        }
                    }
                    else
                    {
                        if(DD>30)
                        {
                            std::cout<<"Invalid date"<<std::endl;
                            return;
                        }
                    }
                    std::string reviewText;
                    getline(input,reviewText);
                    while(reviewText[0]==' ')
                    {
                        reviewText.erase(0,1);
                    }
                    while(reviewText[reviewText.length()-1]==' ')
                    {
                        reviewText.erase(reviewText.length()-1,1);
                    }
                    addReview(hits[num-1]->getName(),inRating,logged->getName(),inDate,reviewText);
                }
                else
                {
                    std::cout<<"Invalid date"<<std::endl;
                }
            }
        }
    }

}


void MyDataStore::viewReview(std::vector<Product*> hits,int num)
{
    if(num>(int)hits.size())
    {
        std::cout<<"Invalid hit number"<<std::endl;
        return;
    }

    std::vector<Review> temp=hits[num-1]->getReviewList();
    CompDate c3;
    mergeSort(temp,c3);
    for(int i=0;i<(int)temp.size();i++)
    {
        std::cout<<temp[i].date<<" "<<temp[i].rating<<" "
            <<temp[i].username<<" "<<temp[i].reviewText<<std::endl;
    }
}


//hw 8 below

std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser)
{
    createRefine();
    std::vector<Product*> validProducts;
    std::vector<Review>tempList=logged->getUserReviewList();

    for(std::map<std::string,Product*>::iterator it=prodMap.begin();it!=prodMap.end();++it)
    {
        bool find=false;
        for(std::vector<Review>::iterator itV=tempList.begin();itV!=tempList.end();itV++)
        {
            if(it->first==itV->prodname)
            {
                find=true;
                break;
            }
        }
        std::vector<Review> testlist=it->second->getReviewList();
        if(find==false && testlist.size()!=0)
        {
            validProducts.push_back(it->second);
        }
    }
    //the result
    std::vector<std::pair<std::string, double> > result;

    if(validProducts.size()==0)
    {
        return result;
    }

    for(std::vector<Product*>::iterator it=validProducts.begin();it!=validProducts.end();++it)
    {
        double sumR=0;
        double sumW=0;
        std::vector<Review> tempList2=(*it)->getReviewList();
        for(std::vector<Review>::iterator itV=tempList2.begin();itV!=tempList2.end();itV++)
        {
            sumW+=1.0-(*refinedDistance)[itV->username];
            sumR+=(1.0-(*refinedDistance)[itV->username])*((double)itV->rating);
        }
        double ratingForP;
        if(sumW==0.0)
        {
            ratingForP=0.0;
        }
        else
        {
            ratingForP=sumR/sumW;
        }
        result.push_back(make_pair((*it)->getName(),ratingForP));
    }
    CompPair c1;
    std::stable_sort(result.begin(),result.end(),c1);
    return result;
}

double MyDataStore::calculateBasicSimilarity(User* user1,User* user2)
{
    double result=0.0;
    int number=0;
    std::vector<Review> list1=user1->getUserReviewList();
    std::vector<Review> list2=user2->getUserReviewList();
    for(size_t i=0;i<list1.size();i++)
    {
        for(size_t j=0;j<list2.size();j++)
        {
            if(list1[i].prodname==list2[j].prodname)
            {
                double temp=((double)(abs(list1[i].rating-list2[j].rating)))/4.0;
                result=(result*number+temp)/(number+1.0);
                number++;
                break;
            }
        }
    }
    if(number==0)
    {
        result=1.0;
    }
    return result;
}

/*
void MyDataStore::createAdjacenctList()
{
    adjacencyList->clear();
    std::map<std::string,User*>::iterator it;
    for(it=userMap.begin();it!=userMap.end();++it)
    {
        std::map<std::string,double> listBasic;
        adjacencyList->insert(make_pair(it->first,listBasic));
        std::map<std::string,User*>::iterator it2;
        for(it2=userMap.begin();it2!=userMap.end();++it2)
        {
            if(it->first!=it2->first)
            {
                double basicS=calculateBasicSimilarity(it->second,it2->second);
                (*adjacencyList)[it->first].insert(make_pair(it2->first,basicS));
            }
        }
    }
}*/

void MyDataStore::createRefine()
{
    //createAdjacenctList();
    refinedDistance->clear();
    Heap<string> myHeap(2);
    double numStart=0;
    myHeap.push(numStart,logged->getName());
    refinedDistance->insert(make_pair(logged->getName(),numStart));
    for(std::map<string,User*>::iterator it= userMap.begin();it!=userMap.end();++it)
    {
        if(it->first!=logged->getName())
        {
            double tempDis=std::numeric_limits<double>::infinity();//find it in stackflow
            myHeap.push(tempDis,it->first);
            refinedDistance->insert(make_pair(it->first,tempDis));
        }
    }
    while(myHeap.empty()==false)
    {
        std::string min=myHeap.top();
        myHeap.pop();
        for(std::map<string,User*>::iterator it= userMap.begin();it!=userMap.end();++it)
        {
            if(it->first!=min)
            {
                double weight=calculateBasicSimilarity(userMap[min],it->second);
                if((*refinedDistance)[min]+weight < (*refinedDistance)[it->first])
                {
                    (*refinedDistance)[it->first]=(*refinedDistance)[min]+weight;
                }
                myHeap.decreaseKey((*refinedDistance)[it->first],it->first);
            }
        }
    }

}

void MyDataStore::doRecommendation()
{
    if(logged==NULL)
    {
        cout<<"No recommendations available"<<endl;
        return;
    }
    std::vector<std::pair<std::string, double> > result=makeSuggestion(logged->getName());
    if(result.size()==0)
    {
        cout<<"No recommendations available"<<endl;
        return;
    }

    std::stringstream temps;
    temps<<logged->getName()<<endl;
    for(std::vector<std::pair<std::string,double> >::iterator it=result.begin();it!=result.end();++it)
    {
        temps<<std::fixed<<std::setprecision(2)<<it->second<<" "<<it->first<<endl;
    }
    std::string newString=temps.str();
    cout<<newString;

    //to a file
    std::ofstream ofile("rec.txt");
    //ofile.open("rec.txt");
    ofile<<newString;
    ofile.close();
}