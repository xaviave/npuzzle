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
** Private Methods
*/

/*
** Public Methods
*/

PyNode	*NPuzzleHandler::list_to_pynode(std::list<Node> data_path)
{
	std::list<Node>::iterator it = data_path.begin();
	PyNode *py_path = new PyNode[data_path.size()];

	for (size_t i = 0; i < data_path.size(); i++)
	{
		py_path[i].t_states = 10;
		py_path[i].m_states = -24;
		py_path[i].grid = it->grid.data();
		it++;
	}
	std::cout << data_path.size() << std::endl;
	return (py_path);
}


PyNode	*NPuzzleHandler::solve()
{
	this->s->_("soluce");
	this->p->_("puzzle");
	std::list<Node> data_path = this->a_star(*(this->p), *(this->s));
	return (this->list_to_pynode(data_path));
}
