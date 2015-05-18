# Ce script permet de tester notre projet



echo "Building the make .. "

cmake . > /dev/null

echo "Building the script .. "

make > /dev/null

read -p "--> Press [Enter] to continue... "
echo "Test of Question number 4 with solution "
read -p "--> Press [Enter] to continue..."

./projq4.out "4 ;3 ;10 ;30 ;100 ;100 ;2 ;4 ;1; 1; 1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;1,3 ;2,4;"

read -p "--> Press [Enter] to continue..."
echo "Test of Question number 4 without solution :"
read -p "--> Press [Enter] to continue..."

./projq4.out "1 ;3 ;1 ;10 ;50 ;2 ;2 ;2 ;1,2 ;1 ;1 ;2 ;"



read -p "--> Press [Enter] to continue..."
echo " Question 5 : Examen with duration "
read -p "Press [Enter] to continue..."

./projq5.out "12 ;3 ;10 ;30 ;100 ;100 ;2 ;4 ;1; 1; 1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;1,3 ;2,4; 2; 4; 2; 3;"


read -p "--> Press [Enter] to continue..."
echo " Question 6 : "
read -p "--> Press [Enter] to continue..."

./projq6.out "24 ;3 ;10 ;30 ;100 ;100 ;2 ;4 ;1; 1; 1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;1,3 ;2,4; 2; 4; 2; 3;"

read -p "--> Press [Enter] to continue..."
echo " Question 7 : "
read -p "--> Press [Enter] to continue..."

./projq7.out


read -p "--> Press [Enter] to continue..."
echo " Question 9 : "
read -p "--> Press [Enter] to continue..."

./projq9.out "11;3;128;118;148;15;4;4;1,2;2,4;2,3;1,4;3,1;1,1;4,4;3,1;1,3;1,1;4,1;3,4;4,2;4,3;2,1;3;1;2;3;2;2;3;2;"

# TODO