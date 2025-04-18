/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:52:54 by jnunes            #+#    #+#             */
/*   Updated: 2024/10/02 13:53:54 by jnunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>

class PmergeMe
{
    private:
        PmergeMe();
        int _val;
        int _pair;
    public:
        ~PmergeMe();
        PmergeMe(int val, int pair);
        PmergeMe(const PmergeMe& other);
        int getPair() const;
        int getVal() const;
        void setPair(int pair);
	PmergeMe& operator=(const PmergeMe& other);
};
