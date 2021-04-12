/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/09 11:19:24 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzleHandler.hpp"

/*
** Constructor - Destructor Methods
*/

NPuzzleHandler::NPuzzleHandler(Node p_, Node s_, std::list<Node> path_ = {}) : p(new Node(p_.size, p_.grid)), s(new Node(s_.size, s_.grid)), path(path_)
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
** Private Methods
*/

/*
** Public Methods
*/

//
//PyNode	*NPuzzleHandler::list_to_pynode(std::list<Node> data_path)
//{
//	std::list<Node>::iterator it = data_path.begin();
//	PyNode *py_path = new PyNode[data_path.size()];
//
//	for (size_t i = 0; i < data_path.size(); i++)
//	{
//		py_path[i].grid = it->grid.data();
//		it++;
//	}
//	std::cout << data_path.size() << std::endl;
//	return (py_path);
//}


void    NPuzzleHandler::solve()
{
	this->s->_("soluce");
	this->p->_("puzzle");
	this->path = this->a_star(*(this->p), *(this->s));
	std::cout << "CPP path size: " << this->path.size() << std::endl;
}
