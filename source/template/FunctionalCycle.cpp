//Check Cycle
a = succ(x);
b = succ(succ(x));
while (a != b) {
a = succ(a);
b = succ(succ(b));
}

//Find the starting point of cycle
a = x;
while (a != b) {
a = succ(a);
b = succ(b);
}
first = a;

//Get Cycle Length
b = succ(a);
length = 1;
while (a != b) {
b = succ(b);
length++;
}
