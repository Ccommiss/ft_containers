#ifndef LOL_HPP
# define LOL_HPP

# include <iostream>
# include <string>

class Lol
{

	public:

		Lol();
		Lol( Lol const & src );
		~Lol();

		Lol &		operator=( Lol const & rhs );

	private:

};

std::ostream &			operator<<( std::ostream & o, Lol const & i );

#endif /* ************************************************************* LOL_H */