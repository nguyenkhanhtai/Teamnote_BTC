
Types of Constraints
Keep in mind that:

(x V y) = ((¬x => y) ^ (¬y => x))
1. Forcing a variable to be true

If we want to force x  to be true, it is equivalent to adding a clause (x V x).

2. Exactly one variable must be true

This is equivalent to (x V y) ^ (¬x V ¬y).

3. At least one variable must be true

This is just a clause (x V y).

4. Both variables must have the same value
This is equivalent to (¬x V y) ^ (x V ¬y).