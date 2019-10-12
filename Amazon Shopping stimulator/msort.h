#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

template<class T, class Comparator>
void mergeSort(vector<T>& myArray,Comparator comp)
{
    int start=0;
    int end=(int)(myArray.size()-1);
    helper(myArray,start,end,comp);
}

//helper function
template<class T, class Comparator>
void helper(vector<T>& myArray,int start,int end,Comparator comp)
{
    if(start+1==end)
    {
        merge(myArray,start,end,start,comp);
    }
    else if(start<end)
    {
        int med=floor((start+end)/2);//was 1+end
        helper(myArray,start,med,comp);
        helper(myArray,med+1,end,comp);
        merge(myArray,start,end,med,comp);
    }
}

template<class T, class Comparator>
void merge(vector<T>& myArray,int start,int end,int med,Comparator comp)
{
    vector<T> temp;
    int i=start,j=med+1,k=0;
    while(i<=med||j<=end)
    {
        if(i<=med &&(j>end||comp(myArray[i],myArray[j])))
        {
            temp.push_back(myArray[i]);
            i++;
            k++;
        }
        else
        {
            temp.push_back(myArray[j]);
            j++;
            k++; 
        }
    }
    for(k=0;k<end+1-start;k++)
    {
        myArray[k+start]=temp[k];
    }
}