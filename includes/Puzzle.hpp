/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 16:08:02 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE_HPP
# define PUZZLE_HPP

# include <random>
# include <algorithm>

# include "ArgParser.hpp"


class Puzzle
{

	public:
		int					size;
		std::vector<int>	h_n;
		std::vector<int>	grid;
		
		
		typedef std::vector<int>	(Puzzle::*mptr)(const int z, Puzzle p);
		mptr moves[4] = {&Puzzle::move_left, &Puzzle::move_up, &Puzzle::move_right, &Puzzle::move_down};

		Puzzle(const int s);
		Puzzle(Puzzle *obj);
		Puzzle(const int s, const std::vector<int> g);
		virtual ~Puzzle(void);

		std::vector<int>	move_left(const int z, Puzzle p);
		std::vector<int>	move_up(const int z, Puzzle p);
		std::vector<int>	move_right(const int z, Puzzle p);
		std::vector<int>	move_down(const int z, Puzzle p);
		
		std::vector<int>	run(int i, const int z, Puzzle p);
	private:

};

#endif