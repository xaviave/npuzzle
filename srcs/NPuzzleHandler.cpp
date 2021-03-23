/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/23 15:45:29 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzleHandler.hpp"

/*
** Constructor - Destructor Methods
*/

NPuzzleHandler::NPuzzleHandler(const int s_, const std::string &file_name) : puzzle_file(file_name)
{
	p = new Puzzle(s_);
	s = new Puzzle(s_);
}

NPuzzleHandler::~NPuzzleHandler(void)
{
	delete p;
	delete s;
}

/*
** Private Methods
*/

int		NPuzzleHandler::_is_solvable() const
{
	/*
	NI for number of inversion
	NT for 0 Position from bottom (y)
	
	Puzzle is solvable if:
		- SIZE % 2 == 1 AND NI % 2 == 0
		- SIZE % 2 == 0 AND (
				( NT % 2 == 0 AND NI % 2 == 1)
			OR
				( NT == 1 AND NI % 2 == 0) 
			)
	*/
	int	ni = 0;
	int	nt = this->p->size - (this->get_number_index(this->p->grid, 0) / this->p->size);

	for (int i = 0; i < this->p->length; i++)
	{
		for (int _ = i + 1; (this->p->grid[i] && _ < this->p->length); _++)
			if (this->p->grid[_] && this->p->grid[_] < this->p->grid[i])
				ni++;
	}
	
	if (((this->p->size % 2) && !(ni % 2)) ||
		(!(this->p->size % 2) &&
		((!(nt % 2) && (ni % 2)) ||
		((nt % 2)  && !(ni % 2)))))
		return (1);
	return (0);
}

void	NPuzzleHandler::_parse_file()
{
	std::cout << "Exit Parser - puzzle file open and parsed" << std::endl;
}

void	NPuzzleHandler::_generate_puzzle()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
	std::generate(this->p->grid.begin(), this->p->grid.end(), [n = 0] () mutable { return n++; });
	std::shuffle(std::begin(this->p->grid), std::end(this->p->grid), e);
	if (!this->_is_solvable())
	{
		std::cout << "Generated Puzzle unsolvable | genarating new one" << std::endl;
		std::shuffle(std::begin(this->p->grid), std::end(this->p->grid), e);
		this->_generate_puzzle();
		return ;
	}
}

void	NPuzzleHandler::_generate_solution()
{
	int nu = 1;
	int sr = 0;
	int sc = 0;
	int r = this->s->size - 1;
	int c = this->s->size - 1;

    while(sr <= r && sc <= c)
	{
        for (int i = sc; i <= c; i++)
            this->s->grid[sr * this->s->size + i] = nu++;
        sr++;
        for (int i = sr; i <= r; i++)
            this->s->grid[i * this->s->size + c] = nu++;
        c--;
        if (sr <= r)
		{
            for (int i = c; i >= sc; i--)
                this->s->grid[r * this->s->size + i] = nu++;
            r--;
        }
        if (sc <= c)
		{
            for (int i = r; i >= sr; i--)
                this->s->grid[i * this->s->size + sc] = nu++;
            sc++;
        }
    }
	this->s->grid[this->get_number_index(this->s->grid, this->s->length)] = 0;
}

/*
** Public Methods
*/

void	NPuzzleHandler::parser()
{
	this->_generate_solution();
	std::cout << "Enter Parser" << std::endl;
	if (!this->puzzle_file.empty())
		this->_parse_file();
	else
	{
		this->_generate_puzzle();
		std::cout << "Exit Parser - Puzzle generated" << std::endl;
	}
}

void	NPuzzleHandler::solve()
{
	/*
	// unsolvable

	this->p->size = 4;
	this->p->length = 16;
	this->p->grid = {3, 9, 1, 15, 14, 11, 4, 6, 13, 0, 10, 12, 2, 7, 8, 5};

	// solvable
	this->p->grid = {1, 8, 2, 0, 4, 3, 7, 6, 5};
	this->p->grid = {4, 1, 3, 0, 8, 6, 7, 2, 5};
	this->p->grid = {4, 1, 3, 7, 5, 8, 2, 0, 6};

	this->p->size = 4;
	this->p->length = 16;
	this->p->grid = {6, 13, 7, 10, 8, 9, 11, 0, 15, 2, 12, 5, 14 ,3, 1, 4};
	this->p->grid = {13, 2, 10, 3, 1, 12, 8, 4, 5, 0, 9, 6, 15, 14, 11, 7};
	

	// hard 4x4
	this->p->size = 4;
	this->p->length = 16;
	this->p->grid = {8,  7,  1, 11, 4, 13,  3,  2, 5, 12,  9, 14, 6, 10,  0, 15};
	
	// linear conflict
	this->p->grid = {6, 3, 1, 4, 8, 0, 2, 5, 7};
	this->p->grid = {6, 3, 1, 2, 8, 0, 4, 5, 7};
	*/
	this->s->_("soluce");
	this->a_star(this->p, this->s);
	std::cout << "Exit Solve" << std::endl;
}
