/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/06 09:51:04 by xamartin         ###   ########lyon.fr   */
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
	int	nt = this->p->size - (this->get_number_index(this->p->length, this->p->grid, 0) / this->p->size);

	for (int i = 0; i < this->p->length; i++)
	{
		for (int j = i + 1; j < this->p->length; j++)
			if (this->p->grid[j] && this->p->grid[j] < this->p->grid[i])
				ni++;
	}
	
	if (((this->p->size % 2) && (ni % 2)) ||
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
	std::vector<int>	g_;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
	std::generate(g_.begin(), g_.end(), [n = 0] () mutable { return n++; });
	std::shuffle(std::begin(g_), std::end(g_), e);
	if (!this->_is_solvable())
	{
		std::cout << "Generated Puzzle unsolvable | genarating new one" << std::endl;
		std::shuffle(std::begin(g_), std::end(g_), e);
		this->_generate_puzzle();
		this->p->grid = std::move(g_);
		return ;
	}
	this->p->grid = std::move(g_);
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
	this->s->grid[this->get_number_index(this->s->length, this->s->grid, this->s->length)] = 0;
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
	std::vector<int> t_ = {0, 2, 3, 1, 4, 5, 8, 7, 6};
	this->p->grid = t_;
	
	this->s->_("soluce");
	this->a_star(*(this->p), *(this->s));
	std::cout << "Exit Solve" << std::endl;
}
