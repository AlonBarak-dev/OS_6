# Operating Systems - Ex 6. <br>

The sixth assignment of the course Operating Systems at Ariel University. <br>
Presented by: <br>
Alon Barak & Idan Philosoph. <br>

In this repository you can find an implementation of different Design Patterns in C/C++. <br>
Such as: <br>
- Guard <br>
- Singleton <br>
- Reactor <br>
- Active Object <br>

## How to Run the Active Object Pipline: Ques 1-3 <br>

1. Compile the Code:
```ruby
make all
``` 
2. Run the Server:
```ruby
./main
``` 
3. Run The Client:
```ruby
./client 127.0.0.1
```
4. Send Commands from the Client to the Server and wait for response. <br>
5. Example: <br>
```ruby
Please enter a command:
Hello   <input>
iFMMP   <output>
```


## How to Run the Guard: Ques 4 <br>

1. Compile the Code:
```ruby
make all
```
2. Run the Guard Main:
```ruby
./guard
```


## How to Run the Singleton: Ques 5 <br>

1. Compile the Code:
```ruby
make all
```
2. Run the Singleton Code:
```ruby
./singleton
```


## How to Run the Reactor Server & Client: Ques 6

### Server:
1. Compile the Code:
```ruby
make all
```
2. Run the Poll-Server:
```ruby
./pollserver
```

### Client:
1. Compile the Code:
```ruby
make all
```
2. Run the Client:
```ruby
./client 127.0.0.1
```


## How to Build the Shared Library:
```ruby
make OS6
```

## External Resources: <br>

- https://beej.us <br>
- https://www.geeksforgeeks.org/queue-linked-list-implementation/  <br>



### P.S. 
Please ignore the warnings & errors during the Compilation of the Shared Library, it Occours because of the multiple defenitions of Main.<br>
One can just comment the mains and Compile the Shared Library. <br>
Also, please ignore any warnings during Compilation, Thanks.

