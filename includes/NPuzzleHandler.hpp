/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 15:03:58 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLEHANDLER_HPP
# define NPUZZLEHANDLER_HPP

# include <random>
# include <algorithm>

# include "ArgParser.hpp"
# include "Puzzle.hpp"
# include "Solver.hpp"


class NPuzzleHandler : public ArgParser, public Solver
{
	public:
		Puzzle 		*p;
		std::string	puzzle_file;

		NPuzzleHandler(const std::string &name);
		virtual ~NPuzzleHandler(void);

		void	print_usage() const;
		int		parse_command_line(int ac, char **av);
		
		int		parser();
		int		solve();
	private:
		bool	_is_number(const std::string &s);
		int		_random_from_range(int start, int end) const;
		
		int		_parse_file(const std::string &file_name);
		int 	_generate_puzzle(const int size);

};

#endif