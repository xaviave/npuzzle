/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/08 16:47:07 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLEHANDLER_HPP
# define NPUZZLEHANDLER_HPP

# include <string>
# include <random>

# include "Node.hpp"
# include "Solver.hpp"


class NPuzzleHandler : public Solver
{
	public:
		// Variables
		Node		    *p;
		Node		    *s;
		std::list<Node> path;

		// Constructor - Destructor
		NPuzzleHandler(Node p_, Node s_, std::list<Node> path_);
		virtual ~NPuzzleHandler(void);

		// Methods
		void	solve();
};

#endif