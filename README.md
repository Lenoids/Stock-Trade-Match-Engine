# User manual for the stock trade match engine assignment by Dong Haokun, Luke
# 2023-08-09


# Designing method:

# 1. main.cpp is the entrance for the program, a endless loop to ensure the socket listening process. A new OrderManage object is created in main.cpp and start to receive, add, match new orders.
# 2. The main part of engine is the OrderManage Class, its function includes adding new order, matching orders, delete empty orders, print orders and receive new orders.
# 3. Every order is a object including 4 properties: ID, type, price and quantity.
# 4. TCP connection is fulfiled by tcpsocket.cpp and tcpserver.cpp, referenced by [“Asynchronous Sockets for C++”](https://github.com/eminfedar/async-sockets-cpp) (https://github.com/eminfedar/async-sockets-cpp), which is a thread-based, non-blocking asynchronous client-server classes in C++ for TCP.
# 5. We use 127.0.0.1 and port 8888 for the tcp connection.

# Compile and run:

# 1. The program is compiled and run under Linux. 
# 2. Compile requirements: I used g++ 9.4.0, lower version is also availale.
# 3. Compile command:    
# 	$ g++ basesocket.cpp Order.cpp OrderManage.cpp tcpserver.cpp tcpsocket.cpp main.cpp -o main -lpthread
# 	$ g++ basesocket.cpp tcpserver.cpp tcpsocket.cpp client.cpp -o test -lpthread
    
# 4. Run command:
# 	$ ./main &
#	$ ./test
    
# 5. main and test refered to the matchEngine function and test function respectively

# Test and data generate:

# 1. The test is completed by creating multiple number of threads acting as clients to make trading, sending fixed format of message.
# 2. The tcp connection message format is: ID,type,price,quantity
# example: if you want make a trade that sell stock in price 9, quantity 20, send:
#         1001,sell,9,20
#         to the match engine server(127.0.0.1, port 8888), 1001 is the ID.
        
# 3. The client.cpp offers a test example of generating different trade with different price and quantity. Execute ./test and you will see:
    
#     Welcome to the makeEngine test, please input the number of clients you want to create(0-999):
    
#     After entering the number, also the number of threads created, it will shows:
    
#     Please input the number of trade every clients make:
    
#     which inputs the number of every thread will send to the match engine server.
