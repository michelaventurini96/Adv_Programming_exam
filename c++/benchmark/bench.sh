#MEASURE BST BALANCED AND NOT BALANCED AND NOT OPT
for num in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
	 g++ -D NUM=$num bst.cc -o bst10
  ./bst10 >> bst_not_opt.csv
  ./bst10 >> bst_not_opt.csv
 	./bst10 >> bst_not_opt.csv
 	./bst10 >> bst_not_opt.csv
 	./bst10 >> bst_not_opt.csv

	rm bst10
done

#MEASURE BST BALANCED AND NOT BALANCED AND OPT
for num in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
	g++ -D NUM=$num bst.cc -O3 -o bst10
  ./bst10 >> bst_opt.csv
  ./bst10 >> bst_opt.csv
 	./bst10 >> bst_opt.csv
 	./bst10 >> bst_opt.csv
 	./bst10 >> bst_opt.csv

	rm bst10
done

cat bst_not_opt.csv | grep "^b" >> bal_not_opt.csv
cat bst_not_opt.csv | grep "^notb" >> notbal_not_opt.csv

cat bst_opt.csv | grep "^b" >> bal_opt.csv
cat bst_opt.csv | grep "^notb" >> notbal_opt.csv

#MEASURE MAP NOT OPT
for num in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
	g++ -D NUM=$num std_map.cc -o map10
	./map10 >> map_not_opt.csv
	./map10 >> map_not_opt.csv
	./map10 >> map_not_opt.csv
	./map10 >> map_not_opt.csv
	./map10 >> map_not_opt.csv

	rm map10
done

#MEASURE MAP OPT
for num in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
	g++ -D NUM=$num -O3 std_map.cc -o map10
	./map10 >> map_opt.csv
	./map10 >> map_opt.csv
	./map10 >> map_opt.csv
	./map10 >> map_opt.csv
	./map10 >> map_opt.csv

	rm map10
done
