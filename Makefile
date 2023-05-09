firstpart:  smsh2.c splitline.c
	gcc -o smsh2 smsh2.c splitline.c execute.c
	./smsh2

prefirst: smsh1.c splitline.c execute.c
	gcc -o smsh1 splitline.c execute.c smsh1.c
	./smsh1