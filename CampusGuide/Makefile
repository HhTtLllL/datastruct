obj = guide_main.o Guide_UI.o Guide_Account_Pre.o Guide_group_Pre.o
CC = gcc
target = guide_main


$(target):$(obj)
	gcc $(obj) -o $(target) -lmysqlclient

%.o : %.c
	gcc -c $< -o $@ -lmysqlclient

clean:
	rm *.o

#guide_main.o:guide_main.cpp
#	gcc -c guide_main.cpp

#Guide_UI.o:Guide_UI.cpp
#	gcc -c Guide_UI.cpp

#Guide_Account_Pre.o:Guide_Account_Pre.cpp
#	gcc -c Guide_Account_Pre.cpp

