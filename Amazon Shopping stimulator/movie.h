#include"product.h"
#include"util.h"
#include<sstream>

class Movie : public Product
{
public:
    Movie(const std::string category, const std::string name, double price,
         int qty, const std::string inGenre, const std::string inRating);
    ~Movie();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:
    std::string genre;
    std::string rating;

};