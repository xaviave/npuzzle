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

#include "../includes/NPuzzleHandler.hpp"

/*
** Constructor - Destructor Methods
*/

NPuzzleHandler::NPuzzleHandler(Node *p_, Node *s_) : p(p_), s(s_), path()
{
}

NPuzzleHandler::~NPuzzleHandler(void)
{
	delete p;
	delete s;
}

/*
** Public Methods
*/


int     NPuzzleHandler::get_length() const
{
    return (this->p->length);
}

std::vector<int>    NPuzzleHandler::get_path_grid(int pos) const
{
    int             i = -1;

    for (auto x: this->path)
        if (++i == pos)
            return (x.grid);
    return (this->path.end()->grid);
}

void    NPuzzleHandler::solve()
{
	this->path = this->a_star(*(this->p), *(this->s));
}
