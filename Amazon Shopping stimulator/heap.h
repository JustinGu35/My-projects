#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below
    void trickleUp(size_t loc);
    void heapify(size_t idx);



    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::trickleUp(size_t loc)
{
    if(loc==0)
    {
        return;
    }
    size_t parent = (loc-1)/2;
    while(parent>=0&& c_(store_[loc].first,store_[parent].first))
    {
        std::pair<double, T> temp=store_[loc];
        store_[loc]=store_[parent];
        store_[parent]=temp;
        keyToLocation_[store_[loc].second]=loc;
        keyToLocation_[store_[parent].second]=parent;

        loc=parent;
        parent=(loc-1)/2;
    }
}


template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::heapify(size_t idx)
{
    if(2*(idx+1)>store_.size())
    {
        return;
    }
    size_t betterChild=2*idx+1;
    if(2*(idx+1)+1<=store_.size())
    {
        size_t rChild=betterChild+1;
        if(c_(store_[rChild].first,store_[betterChild].first))
        {
            betterChild=rChild;
        }
    }
    if(c_(store_[betterChild].first,store_[idx].first))
    {
        std::pair<double, T> temp=store_[idx];
        store_[idx]=store_[betterChild];
        store_[betterChild]=temp;
        keyToLocation_[store_[idx].second]=idx;
        keyToLocation_[store_[betterChild].second]=betterChild;

        heapify(betterChild);
    }
}



template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    // You complete.
    store_.push_back(std::make_pair(priority,item));
    trickleUp(store_.size()-1);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete
    size_t position=keyToLocation_[item];
    store_[position].first=priority;
    trickleUp(position);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }

    // You complete
    return store_[0].second;
}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    // You complete
    store_[0]=store_.back();
    store_.pop_back();
    heapify(0);

}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}


#endif

