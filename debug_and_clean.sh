#!/bin/bash

echo "which program ?"
read PROGRAM

if [ $PROGRAM != "clean" ] ; then
echo $ARG_PHILO
fi

if [ $PROGRAM = "call" ] ; then
make -C philo_one
valgrind --tool=callgrind ./philo_one/philo_one 4 410 200 200
kcachegrind callgrind.out*
rm callgrind.out*
fi

if [ $PROGRAM = "1" ] ; then
make -C philo_one
./philo_one/philo_one 4 410 200 200 > debug_2.txt
./philo_one/philo_one 5 800 200 200 > debug_1.txt
# cat debug.txt | grep "<   1>" > one_one.txt
# cat debug.txt | grep "<   2>" > one_two.txt
# cat debug.txt | grep "<   3>" > one_three.txt
# cat debug.txt | grep "<   4>" > one_four.txt
elif [ $PROGRAM = "2" ] ; then
make -C philo_two
./philo_two/philo_two $ARG_PHILO > debug.txt
cat debug.txt | grep "<   1>" > two_one.txt
cat debug.txt | grep "<   2>" > two_two.txt
cat debug.txt | grep "<   3>" > two_three.txt
cat debug.txt | grep "<   4>" > two_four.txt
elif [ $PROGRAM = "3" ] ; then
make -C philo_three
./philo_three/philo_three $ARG_PHILO > debug.txt
cat debug.txt | grep "<   1>" > three_one.txt
cat debug.txt | grep "<   2>" > three_two.txt
cat debug.txt | grep "<   3>" > three_three.txt
cat debug.txt | grep "<   4>" > three_four.txt
elif [ $PROGRAM = "clean" ] ; then
make -C philo_one fclean
make -C philo_two fclean
make -C philo_three fclean
rm -rf *.txt
fi