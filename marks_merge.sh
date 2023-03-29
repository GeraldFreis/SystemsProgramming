#!/bin/bash

# getting the number of lines in each file
n1=$(cat $1 | wc -l)+1;
n2=$(cat $2 | wc -l)+1;
rm outfile1.txt;
touch outfile1.txt;

for (( i=2; i<=$n1; i++))
do

    student1=$(sed -n "${i}p" < $1);
    student2=$(sed -n "${i}p" < $2);
    # getting student ID
    # student1ID=$(cut -d ',' -f1 | cat $);
    student1ID=${student1:0:8};
    student2ID=${student2:0:8};

    if ((student1ID == student2ID))
    then
        # echo ${student2:9:10};
        student1+=${student2:8:10};
        echo $student1
        
    else
        student2Exam=${student2:8:10};
        student2Changed=$student2ID+',-'+$student2Exam;
        echo $student2Changed
        student1+=',-'
        echo $student1
        echo 'here'
    fi
    # echo $student1;
    # echo $student2
done
