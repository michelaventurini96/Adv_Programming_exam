mkdir res

#----------------------------------- BST ---------------------------------------
#MEASURE BST BALANCED AND NOT BALANCED AND NOT OPT
for num in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
	g++ -D NUM=$num bst.cc -o bst
  ./bst >> res/bst_not_opt.csv
	./bst >> res/bst_not_opt.csv
	./bst >> res/bst_not_opt.csv
	rm bst
done

cat res/bst_not_opt.csv | grep "^b" >> res/bal_not_opt.csv
cat res/bst_not_opt.csv | grep "^notb" >> res/notbal_not_opt.csv

#MEASURE BST BALANCED AND NOT BALANCED AND OPT
for num in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
	g++ -D NUM=$num bst.cc -O3 -o bst
  ./bst >> res/bst_opt.csv
	./bst >> res/bst_opt.csv
	./bst >> res/bst_opt.csv
	rm bst
done

cat res/bst_opt.csv | grep "^b" >> res/bal_opt.csv
cat res/bst_opt.csv | grep "^notb" >> res/notbal_opt.csv

#---------------------------- LIST --------------------------------------
#MEASURE LIST BST BALANCED AND NOT BALANCED AND NOT OPT
for num in 10000 20000 30000 40000 50000; do
	 g++ -D NUM=$num list.cc -o list
  ./list >> res/list_not_opt.csv
	./list >> res/list_not_opt.csv
	./list >> res/list_not_opt.csv
	rm list
done

cat res/list_not_opt.csv | grep "^b" >> res/list_bal_not_opt.csv
cat res/list_not_opt.csv | grep "^notb" >> res/list_notbal_not_opt.csv

# #MEASURE BST BALANCED AND NOT BALANCED AND OPT
for num in 10000 20000 30000 40000 50000; do
	g++ -D NUM=$num list.cc -O3 -o list
  ./list >> res/list_opt.csv
	./list >> res/list_opt.csv
	./list >> res/list_opt.csv
	rm list
done

cat res/list_opt.csv | grep "^b" >> res/list_bal_opt.csv
cat res/list_opt.csv | grep "^notb" >> res/list_notbal_opt.csv

#------------------------------ MAP --------------------------
#MEASURE MAP NOT OPT
for num in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
	g++ -D NUM=$num std_map.cc -o map
	./map >> res/map_not_opt.csv
	./map >> res/map_not_opt.csv
	./map >> res/map_not_opt.csv
	rm map
done

#MEASURE MAP OPT
for num in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
	g++ -D NUM=$num -O3 std_map.cc -o map
	./map >> res/map_opt.csv
	./map >> res/map_opt.csv
	./map >> res/map_opt.csv
	rm map
done
