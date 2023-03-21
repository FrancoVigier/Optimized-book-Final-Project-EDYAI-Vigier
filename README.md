# Optimized-book-Final-Project-EDYAI-Vigier
Book of people that are entered by .csv and allows us to operate with it in a way that maximizes execution times and computational complexity. Data Structure and Algorithm I

This project uses totally generic data structures (void*), we use hash table with rebalance area with linked list,
stack, double linked list and we work with the load factor of the table buckets so that they are not overloaded and 
generate an imbalance. We put full emphasis on the complexity of the operations.

# Operations
When we operate with the book, we can do the following things:
- Search: we search for a user in the book
- Add: add a user to the workbook
- Delete: delete a user from the workbook
- Edit: edit a user in the workbook
- Save: save the current workbook to a .csv file
- Load: load a .csv file
- Undo: undo the changes, we use a generic stack to do rollbacks
- Redo: roll back the undone changes, we use a generic stack that depends on the previous one mentioned above.
- AND/OR search: search by a range of parameters
- Save Sorted: we save the current book in order by some parameter. For that I use merge sort and alter the table.
- Sum problem: we insert a number and it will look for that number as the sum of the ages of a subset of users in
               the whole hash table, returning them. I use dynamic programming
