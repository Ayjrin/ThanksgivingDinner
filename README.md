# ThanksgivingDinner
Project for CS41 - Data Structures and Algorithms
## GOAL: 
you are hosting a thanksgiving dinner, you are in charge of determining the venue, guest list, who is bringing what food, as well as who is picking up whom. what data structures in C++ would you use to represent and stor the various components for this senario? what operations would those structures need?

## SOLUTION:
- class guest
	- guest name
	- first favorite food
	- second favorite food
	- third favorite food
	- food being brought
	- location on a (x,y) plane
	- int car size
	- bool RSVP
		- method to change rsvp by user input to call in main
	- size of table
	- bool host

- make a way to read this data from the console, in a line, delimeted by returns and loop through taking more guest data until 10 guests are input


- class guest list
	- guest name in linked list 
	- host guest
		- set host to guest with biggest table
	- food being brought
		- traverse linked list to create a list of food being brought. 
		- if no one is bringing the guests first favorite food, set food being brought to first favroite food
		- if no one is bringing the guests second favorite food, set food being brought to second favroite food
		- if no one is bringing the guests third favorite food, set food being brought to third favroite food
		- else, set food being brought to first favorite food
	- carpool - Traveling Salesman Problem
		- implement a complete graph for 10 nodes that have an x,y coordinate and make the edge weight equal to the distance between the two nodes using pythagoras's therom
		- populate the graph with distance values
		- find biggest car
		- if biggest car is host, return
		- vector to store order of guests for TSP
		- TSP that bad boy
		- if the car is full, move on
		- output
			carpool driver: driver name
			- guest name - food being brought

	- output host



## output format:

Host: host name

carpool driver: driver name
- guest name - food being brought
- guest name - food being brought

Guests Not Attending
	- all guests who RSVP'ed false
