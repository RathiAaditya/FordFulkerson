g++ ./task1_dir/task1.cpp -o ./task1_dir/task1
# time ./task1_dir/task1 $1 > ./task1_dir/t1_answers/testcase$1.txt
time ./task1_dir/task1 $1
if test $1 -lt 5
then
    python3 ./task1_dir/t1_vis.py $1
fi


# g++ ./task1_dir/t1_ds.cpp -o ./task1_dir/t1ds
# # time ./task1_dir/t1ds $1 > ./task1_dir/t1_answers/testcase$1.txt
# time ./task1_dir/t1ds $1
# # if test $1 -lt 5
# # then
# #     python3 ./task1_dir/t1_vis.py $1
# # fi