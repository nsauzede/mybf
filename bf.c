#include <stdio.h>
#include <malloc.h>
#include <string.h>

//#define DEBUG

#define BFSIZE 30000

#ifdef DEBUG
#define dprintf(...) do{printf(__VA_ARGS__);fflush( stdout);}while(0)
#else
#define dprintf(...)
#endif

// ><+-[],.
int bf( const char *_prg)
{
	unsigned int size = BFSIZE, ptr = 0;
	unsigned char *mem = malloc( size);
	char *prg = (char *)_prg;
	unsigned int nesting = 0;
	memset( mem, 0, size);
	dprintf( "<brainf*ck>\n");
	if (prg)
	while (*prg)
	{
		dprintf( "%s: ptr=%d mem=%d nest=%d insn='%c'\n", __func__, ptr, (int)mem[ptr % size], nesting, *prg);
		switch (*prg++)
		{
			case '>':
				if (ptr < (size - 1))
					ptr++;
				break;
			case '<':
				if (ptr > 0)
					ptr--;
				break;
			case '+':
				mem[ptr % size]++;
				break;
			case '-':
				mem[ptr % size]--;
				break;
			case '[':
				if (mem[ptr % size])
				{
					nesting++;
				}
				break;
			case ']':
				if (nesting)
				{
					nesting--;
					if (mem[ptr % size])
					{
						while ((*prg != '[') && (prg > _prg))
							prg--;
					}
				}
				break;
			case ',':
				mem[ptr % size] = getchar();
				break;
			case '.':
				putchar( mem[ptr % size]);
				break;
			default:
				break;
		}
	}
	printf( "\n");
	dprintf( "\n</brainf*ck>\n");
	dprintf( "%s: ptr=%d mem=%d nest=%d\n", __func__, ptr, (int)mem[ptr % size], nesting);
	for (ptr = 0; ptr < 10; ptr++)
	{
		dprintf( "%d ", mem[ptr % size]);
	}
	dprintf( "...\n");
	free( mem);
	return 0;
}

int main( int argc, char *argv[])
{
// b0		: current mem block
// b1		: next mem block (eg: >)
// n,m		: (n*+) (value)
// n+m		: nm (eg: 2+3, ++ +++)
// n*m		: >n[<m>-]< (eg: 2*3, >++[<+++>-]<)
// x		: (expr) (eg: n, n+m, n*m)
// x+n		: xn
// b0+n		: n
// b0+b1	: >[<+>-]
// x*y		: >x[<y>-]<
// b0*x 	: [>x<-]>

// move to n	: [(n*>)+(n*<)-]
// set m to n	: m[(n*>)+(n*<)-]
// copy to n	: [(n*>)+>+(n+1*)<-](n+1*>)[(n+1*<)+(n+1*>)-]
// add b1 to b0	: (+++++>+++<) >[<+>-]<

	char *bfprg = argv[1];
//	bfprg = ">++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";// n 110
//	bfprg = "> > >++[<+++++>-]<+ [<+++++>-]< [<++>-]< .";// n 110 (2*5+1)*5*2 ok
//	bfprg = "> >+++++[<+++++++++++>-]< [<++>-]<.";	// n 110 2*5*11 ok
	bfprg = 
	">++++++++++[<+++++++++++>-]<."				// n 110 10*11 ok
	"-----."		// i 105
	"------."		// c 99
	"++++++++++++."		// o 111
	;

//	bfprg = ">+++++[<+++++++++++>-]<.";			// 5*11 ok
//	bfprg = ">>++[<+++++>-]<+[<+++++>-]<.";// (2*5+1)*5 ok
//	bfprg = ">++[<+++++>-]<+.";// 2*5+1 ok
//	bfprg = ">++[<+++++>-]<.";// 2*5 ok

	bfprg = ">++++[<++++++++>-]<[.+]";

	dprintf( "hello brainf*ck\n");
	bf( bfprg);
	
	return 0;
}
