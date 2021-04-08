/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/08 16:47:07 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzleHandler.hpp"

/*
** Constructor - Destructor Methods
*/

NPuzzleHandler::NPuzzleHandler(Node p_, Node s_) : p(new Node(p_.size, p_.grid)), s(new Node(s_.size, s_.grid))
{
	std::cout << "[DEBUG]:NPuzzleHandler Constructor | addr: " << this << std::endl;
}

NPuzzleHandler::~NPuzzleHandler(void)
{
	delete p;
	delete s;
	std::cout << "[DEBUG]:NPuzzleHandler Destructor | addr: " << this << std::endl;
}

/*
** Public Methods
*/

void	NPuzzleHandler::solve()
{
	this->s->_("soluce");
	this->p->_("puzzle");
	this->a_star(*(this->p), *(this->s));
	std::cout << "Exit Solve" << std::endl;
}
