# Campus-Resource-Management
This project was created as a reservation system to help manage and keep track of the resources students on a college campus use frequently. The Campus Resource Management system allows users to create reservations and cancel reservations as well as adding and removing students from the waitlist. Users can also view the waiting list and the list of resources available. 

# Compiling
To compile this program, please use `g++ -Iinclude src/main.cpp src/Reservation.cpp src/ReservationManager.cpp src/Resource.cpp -o program_name` in the linux terminal and run the program using `./program_name`. <program_name> can be changed to whatever you wish to name the final output file.
# Testing

Test 1.
Tested viewing resources. Displayed all 20 resources from the file.	

Test 2.
Searched for student 1001 and it showed Alice Smith's reservation only. Only her reservation appeared.

Test 3.
Searched for student 9999. Showed a message that no reservations were found. The message appeared.

Test 4.
Searched for a student with two reservations. Showed both matching reservations and both appeared.

Test 5.
Sorted by resource ID. Put the resource IDs in ascending order and the IDs appeared in order.

Test 6.
Sorted by resource name. Put the resource names in alphabetical order. Names appeared in order.

Test 7.
Sorted by resource type. Put resource types in alphabetical order. They appeared in order.

Test 8.
Sorted by availability. Put availability labels in alphabetical order. Available appeared before Unavailable.

Test 9.
Requested unavailable resource R103. Added the student to its waiting list. Showed 1 waiting student and 3 total current requests for R103. The student appeared in the waiting list and both counts were correct.

Test 10. 
Entered invalid menu choices or student IDs. Reject invalid numbers and allow the user to continue. The program showed error messages and could exit normally.