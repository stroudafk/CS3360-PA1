## Programming Assingment 1

This program outputs to files rather than the terminal, since the output may not be visible in the in
the terminal past 1000 lines.

*Note: This program will output to two files with the names 'problem1.txt' and 'problem2.txt'. It's 
best to run this in its own directory/folder to prevent overwriting any pre-existing data.*

To compile and run:
```
g++ -o run PA1.cpp
./run
```

Or, with no arguments:
```
g++ PA1.cpp
./a.out
```

Also optional: pulling the whole directory from github into your root (or working directory if
you keep student work separate from other items in the Linux server)

```
git pull https://github.com/stroudafk/CS3360-PA1
g++ -o run PA1.cpp
./run
```
See the results by opening problem1.txt and problem2.txt for the outputs (respective to the problem number).
```
vim problem1.txt
vim problem2.txt
```

#### Problem 1 Explanation
To generate the interarrival times, I used the formula -(1/lambda)(ln(z)),
where Z is a randomly generated number between 0 and 1, and 2 is lambda.
-(1/2)(ln(rand()/RAND-MAX))

To generate the service times which follow an exponential distribution, I used the formula -(1/lambda)(ln(1-y)), where y is a random number between 1 and 0.


#### Problem 2 Explanation
Part 2

Lambda is 1/500, as we're expecting on average one failure for, 500 hours.


