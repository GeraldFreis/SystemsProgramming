part1:  smsh2.c splitline.c
	gcc -o smsh2 smsh2.c splitline.c
	./smsh2
	
part2: smsh3.c splitline.c
	gcc -o smsh3 smsh3.c splitline.c
	
prefirst: smsh1.c splitline.c execute.c
	gcc -o smsh1 splitline.c execute.c smsh1.c
	./smsh1