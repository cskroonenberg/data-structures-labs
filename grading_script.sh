#!/bin/bash

g++ -std=c++11 MainTest.cpp -o Lab1

for loop in 0 1 2 3 4 5 6 7 8 9
do
    #./Lab1 data$loop > result$loop
    ./Lab1 sample_input/data$loop > result$loop
done

# g++ -std=c++11 MainTesth392x566.cpp -o StuLab1

# for loop in 0 1 2 3 4 5 6 7 8 9
# do
#     ./StuLab1 data$loop > stu_result$loop
# done

#start to grade
function match()
{
    #score = 0
    score=0
    for loop in 0 1 2 3 4 5 6 7 8 9
    do
        #Array3=$(diff result$loop right_result$loop)
        Array3=($(diff result$loop sample_output/right_result$loop))
        data_1=( ${#Array3[*]} )
        echo $data_1
        if [ $data_1 == 0 ]
        then 
            score=`expr $score + 10`
        else 
            score=`expr $score + 0`
        fi
    done
    echo $score
}
match
