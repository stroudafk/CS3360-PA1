To generate the interarrival times, I used the formula -(1/lambda)(ln(z)),
where Z is a randomly generated number between 0 and 1, and 2 is lambda.
-(1/2)(ln(rand()/RAND-MAX))

To generate the service times which follow an exponential distribution, I used the formula -(1/lambda)(ln(1-y)), where y is a random number between 1 and 0.

Part 2

Lambda is 1/500, as we're expecting on average one failure for, 500 hours.


