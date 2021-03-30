/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/29 13:35:07 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLEHANDLER_HPP
# define NPUZZLEHANDLER_HPP

# include <string>
# include <random>

# include "Puzzle.hpp"
# include "Solver.hpp"


class NPuzzleHandler : public Solver
{
	public:
		// Variables
		Puzzle		*p;
		Puzzle		*s;
		std::string	puzzle_file;

		// Constructor - Destructor
		NPuzzleHandler(const int s, const std::string &file_name);
		virtual ~NPuzzleHandler(void);

		// Override Methods

		// Methods
		void	parser();
		void	solve();
	private:
		void	_parse_file();
		void 	_generate_puzzle();
		void 	_generate_solution();
		int		_is_solvable() const;

};

#endif