g++ ./task3_dir/task3.cpp -o ./task3_dir/task3
time ./task3_dir/task3 $1 > ./task3_dir/t3_answers/testcase$1.txt
if test $1 -lt 3
then
    python3 ./task3_dir/task3_vis.py $1
fi
