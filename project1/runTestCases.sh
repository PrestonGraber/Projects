gcc -o crawler crawler.c -Wall
./crawler "https://users.pfw.edu/chenz/testweb/page_000001.html" 10 899 > results.txt
./crawler "https://users.pfw.edu/chenz/testweb/page_000010.html" 5 983 >> results.txt
./crawler "https://users.pfw.edu/chenz/testweb/page_000003.html" 4 187 >> results.txt
./crawler "https://users.pfw.edu/chenz/testweb/page_000003.html" 10 1550698386 >> results.txt
./crawler "https://users.pfw.edu/chenz/testweb/page_000008.html" 5 1550698622 >> results.txt
