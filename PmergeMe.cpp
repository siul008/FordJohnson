/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:52:46 by jnunes            #+#    #+#             */
/*   Updated: 2024/09/10 11:04:45 by jnunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(int val, int pair) : _val(val), _pair(pair)
{
	
}

PmergeMe::~PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe& other) :_val(other._val), _pair(other._pair)
{
    
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
	{
        _val = other._val;
        _pair = other._pair;
	}
	return (*this);
}

int PmergeMe::getPair() const
{
    return (_pair);
}
int PmergeMe::getVal() const
{
    return (_val);
}

void PmergeMe::setPair(int pair)
{
    _pair = pair;
}


