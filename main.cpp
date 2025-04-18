/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:52:34 by jnunes            #+#    #+#             */
/*   Updated: 2024/10/11 14:10:52 by jnunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>

long long GroupSize(bool reset)
{
    static long long nbr = 1;
    static long long ret = 0;
    if (reset)
    {
        nbr = 1;
        ret = 0;
        return (0);
    }

    ret = pow(2, nbr) - ret;
    nbr++;
    return (ret);
}

void printList(const std::list<int>& vec) 
{
    for (std::list<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) 
        std::cout << *it << " "; 
    std::cout << std::endl;
}
int GetPairList(std::list<PmergeMe> &seq, int num)
{
    for (std::list<PmergeMe>::iterator it = seq.begin(); it != seq.end(); ++it)
    {
        if (it->getVal() == num) 
        {
            int pair = it->getPair();
            it->setPair(-1); 
            return pair;
        }
    }
    std::cout << "Error" << std::endl;
    return (-1);
}

void mergeInsertionSortList(std::list<PmergeMe>& sequence, std::list<int>& result) 
{
    size_t n = sequence.size();
    std::list<std::list<PmergeMe>* > vecs;
    std::list<int> newResult;
    int remainder = -1;
    std::list<PmergeMe> newSequence;

    for (std::list<PmergeMe>::iterator it = sequence.begin(); it != sequence.end(); ++it) 
    {
        newResult.push_back(it->getVal());
    }
    result = newResult;

    if (n <= 1) 
        return;

    std::list<PmergeMe>::iterator it = sequence.begin();
    while (it != sequence.end()) 
    {
        std::list<PmergeMe>::iterator nextIt = it;
        ++nextIt;
        if (nextIt != sequence.end()) 
        { 
            if (it->getVal() < nextIt->getVal()) 
            {
                newSequence.push_back(PmergeMe(nextIt->getVal(), it->getVal()));
            } 
            else 
            {
                newSequence.push_back(PmergeMe(it->getVal(), nextIt->getVal()));
            }
            it = nextIt;
            ++it; 
        } 
        else 
        {
            break;
        }
    }

    if (n % 2 != 0) 
    {
        std::list<PmergeMe>::iterator lastIt = sequence.end();
        --lastIt; 
        remainder = lastIt->getVal();
    }

 
    mergeInsertionSortList(newSequence, result);

    int pair = GetPairList(newSequence, result.front());
    result.insert(result.begin(), pair);
    long long m = newSequence.size() - 1;
    if (m > 0)
    {
        std::list<PmergeMe>* vec = new std::list<PmergeMe>();
        vecs.push_back(vec);

        long long groupSize = GroupSize(false);
        long long currentGroupCount = 0;

        std::list<PmergeMe>::iterator it = newSequence.begin();
        while (it != newSequence.end()) 
        {
            if (it->getPair() != -1) 
            {
                if (currentGroupCount >= groupSize) 
                {
                    vecs.push_back(new std::list<PmergeMe>());  
                    currentGroupCount = 0;                 
                    groupSize = GroupSize(false);
                }

                vecs.back()->push_back(*it);
                currentGroupCount++;
            }
            ++it; 
        }
        GroupSize(true);

        if (!vecs.empty() && !vecs.back()->empty()) 
        {
            vecs.back()->reverse();  
        }

        for (std::list<std::list<PmergeMe>*>::iterator groupIt = vecs.begin(); groupIt != vecs.end(); ++groupIt) 
        {
            std::list<PmergeMe>* currentGroup = *groupIt;
            
            for (std::list<PmergeMe>::iterator elemIt = currentGroup->begin(); elemIt != currentGroup->end(); ++elemIt) 
            {
                std::list<int>::iterator maxSearch = std::find(result.begin(), result.end(), elemIt->getVal());
                std::list<int>::iterator pos = std::lower_bound(result.begin(), maxSearch, (elemIt)->getPair());
                result.insert(pos, elemIt->getPair());
            }
        }


        for (std::list<std::list<PmergeMe>*>::iterator it = vecs.begin(); it != vecs.end(); ++it) 
        {
            delete *it; 
        }
    } 
    if (remainder != -1) 
    {
        std::list<int>::iterator pos = std::lower_bound(result.begin(), result.end(), remainder);
        result.insert(pos, remainder);
    }
}

void sortList(std::list<int>& nbr) 
{

    std::list<PmergeMe> sequence;

    for (std::list<int>::iterator it = nbr.begin(); it != nbr.end(); ++it) 
    {
        sequence.push_back(PmergeMe(*it, 0));
    }

    std::list<int> result;
    mergeInsertionSortList(sequence, result);

    nbr = result;
}

void printVectorMerge(const std::vector<PmergeMe>& vec) 
{
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << " Val : " << vec[i].getVal() << " Pair : " << vec[i].getPair();
    std::cout << std::endl;
}


void printVector(const std::vector<int>& vec) 
{
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

int GetPair(std::vector<PmergeMe> &seq, int num)
{
    for (size_t i = 0; i < seq.size(); i++)
    {
        if (seq[i].getVal() == num)
        {
            int pair = seq[i].getPair();
            seq[i] = PmergeMe(seq[i].getVal(), -1);
            return (pair);
        }
    }
    std::cout << "Error" << std::endl;
    return (-1);
}

void printVecs(std::vector<std::vector<int>* > vecs)
{
    for (size_t i = 0; i < vecs.size(); i++)
    {
        for (size_t y = 0; y < vecs[i]->size(); y++)
        {
            std::cout << vecs[i]->at(y) << ", ";
        }
        std::cout << std::endl;
    }
}
void mergeInsertionSort(std::vector<PmergeMe>& sequence, std::vector<int>& result) 
{
    size_t n = sequence.size();
    std::vector<std::vector<PmergeMe>* > vecs;
    std::vector<int> newResult(sequence.size());
    int remainder = -1;
    std::vector<PmergeMe> newSequence;

    for (size_t i = 0; i < sequence.size(); i++)
    {
        newResult[i] = sequence[i].getVal();
    }
    result = newResult;
    if (n <= 1)
    {

        return;
    } 


    for (size_t i = 0; i + 1 < n; i += 2) 
    {
        if (sequence[i].getVal() < sequence[i + 1].getVal())
            newSequence.push_back(PmergeMe(sequence[i + 1].getVal(), sequence[i].getVal()));
        else
            newSequence.push_back(PmergeMe(sequence[i].getVal(), sequence[i + 1].getVal()));
    }
    if (n % 2 != 0) 
        remainder = sequence[sequence.size() - 1].getVal();
    mergeInsertionSort(newSequence, result);


    int pair = GetPair(newSequence, result[0]);
    result.insert(result.begin(), pair);
    long long m = newSequence.size() - 1;
    if (m > 0)
    {
        while (m > 0)
        {
            int groupSize = GroupSize(false);      
            std::vector<PmergeMe>* vec = new std::vector<PmergeMe>();
            vec->reserve(groupSize);
            vecs.push_back(vec);
            m -= groupSize;
        }
        GroupSize(true);
        size_t y = 0;
        for (size_t i = 0; i < newSequence.size(); i++)
        {
           if (newSequence[i].getPair() != -1)
           {
                if (vecs[y]->size() >= vecs[y]->capacity())
                {
                    std::reverse(vecs[y]->begin(), vecs[y]->end());
                    y++;
                }
                vecs[y]->insert(vecs[y]->end(), newSequence[i]);
           }
        }
        std::reverse(vecs[y]->begin(), vecs[y]->end());
        for (y = 0; y < vecs.size(); y++)
        {
            for (size_t z = 0; z < vecs[y]->size(); z++)
            {
                std::vector<int>::iterator maxSearch = std::find(result.begin(), result.end(), vecs[y]->at(z).getVal());
                std::vector<int>::iterator pos = std::lower_bound(result.begin(), maxSearch, vecs[y]->at(z).getPair());
                result.insert(pos, vecs[y]->at(z).getPair());
            }
        }

        for (size_t i = 0; i < vecs.size(); i++)
        {
            delete vecs[i];
        }
    }
    if (remainder != -1)
    {
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), remainder);
        result.insert(pos, remainder);
    }
}

void sort(std::vector<int>& nbr) 
{
    size_t n = nbr.size();

    std::vector<PmergeMe> sequence;

    for (size_t i = 0; i < n; i++) 
    {
        sequence.push_back(PmergeMe(nbr[i], -1));
    }

    std::vector<int> result;
    mergeInsertionSort(sequence, result);

    nbr = result;
}


int main(int argc, char **args)
{
    if (argc < 2)
    {
        std::cerr << "Not enough arguments" << std::endl;
        return (1);
    }
    
    std::string input;
    for (int i = 1; i < argc; ++i)
    {
        if (i > 1)
            input += " ";
        input += args[i];
    }

    std::vector<int> numbersVector;
    std::list<int> numbersList;
    std::stringstream ss(input);
    std::string ipt;

    for (int i = 1; i < argc; i++)
    {
        std::istringstream ss_elem(args[i]);
        std::string value_str;
        while (std::getline(ss_elem, value_str, ' '))
        {
            int value;
            if (!(std::istringstream(value_str) >> value) || value < 0)
                throw std::invalid_argument("Error: invalid value");
            numbersVector.push_back(value);
            numbersList.push_back(value);
        }
    }

    timespec startList, endList;
    timespec startVec, endVec;

    std::cout << "Before: ";
    printList(numbersList);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &startVec);
    sort(numbersVector);
    clock_gettime(CLOCK_MONOTONIC_RAW, &endVec);

    clock_gettime(CLOCK_MONOTONIC_RAW, &startList);
    sortList(numbersList);
    clock_gettime(CLOCK_MONOTONIC_RAW, &endList);   

    std::cout << "After:  ";
    printList(numbersList);

    long secondsVec = endVec.tv_sec - startVec.tv_sec;
    long nanosecondsVec = endVec.tv_nsec - startVec.tv_nsec;
    if (nanosecondsVec < 0) 
    {
        secondsVec--;
        nanosecondsVec += 1000000000;
    }

    long totalMillisecondsVec = secondsVec * 1000 + nanosecondsVec / 1000000;

    std::cout << "Time to process a range of " << numbersVector.size() 
              << " elements with std::vector: " 
              << secondsVec << "." 
              << totalMillisecondsVec << " sec" << std::endl;
    
    long secondsList = endList.tv_sec - startList.tv_sec;
    long nanosecondsList = endList.tv_nsec - startList.tv_nsec;
    if (nanosecondsList < 0) 
    {
        secondsList--;
        nanosecondsList += 1000000000;
    }

    long totalMillisecondsList = secondsList * 1000 + nanosecondsList / 1000000;

    std::cout << "Time to process a range of " << numbersList.size() 
              << " elements with std::list:   " 
              << secondsList << "." 
              << totalMillisecondsList << " sec" << std::endl;



    return 0;
}
