/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/17 16:45:00 by xamartin         ###   ########lyon.fr   */
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
		Puzzle		*solution;
		std::string	puzzle_file;

		// Constructor - Destructor
		NPuzzleHandler(const int s, const std::string &file_name);
		virtual ~NPuzzleHandler(void);

		// Override Methods

		// Methods
		int		parser();
		int		solve();
	private:
		int		_random_from_range(int start, int end) const;
		int		_parse_file();
		int 	_generate_puzzle();
		void 	_generate_solution();

};

#endif