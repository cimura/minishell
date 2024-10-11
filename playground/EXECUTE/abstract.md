statement		::=	<command_line> '|' <command_line>
				|	<command_line>

command_line	::=	<command>
				|	<command> <redirect> <file>
				|	<command_line><command_line>

<redirect>		::=	'>' or '>>' or '<' or '<<'