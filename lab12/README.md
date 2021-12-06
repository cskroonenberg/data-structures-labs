1, GradingScript.py
python3 GradingScript.py [myGraph.h] [input_folder_name] [output_folder_name]
eg. python3 GradingScript.py myGraph_x123y456.h sample_input sample_output

2, How to compile your code
g++ -std=c++11 MainTest.cpp -o Stu_lab12
./Stu_lab12 data > case

alias run='python3 GradingScript.py myGraph.h sample_input sample_output && rm -r sample_output/sample_output'
alias single='g++ -std=c++11 MainTest.cpp -o single && ./single sample_input/data0'

alias test='g++ -std=c++11 test.cpp -o test && ./test'