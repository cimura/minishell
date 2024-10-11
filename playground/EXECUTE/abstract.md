statement		::=	<command_line> '|' <command_line>
				|	<command_line>

command_line	::=	<command>
				|	<command> <redirect> <file>
				|	<command_line><command_line>

<redirect>		::=	'>' or '>>' or '<' or '<<'


// cat infile > tmp1 > tmp2の場合が抜けてる？？
