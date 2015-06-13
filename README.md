# Experiments
Collection of different experiments. Mostly different classes doing different things.

# What are they?
## Property
I'm a fan of C#'s Properties. They're a nice way to handle modifying the behavior of getting and setting private members, rather than writing full blown getter and setter functions. Plus, they allow for nice syntax.
So, that's what Property does.
You give it two functions, (uses std::function internally. lambdas are recommended). And it does the rest. 
To "get", use function call syntax: "()". To set, use assignment syntax: "=".
And that's it!

main.cpp has an example.
