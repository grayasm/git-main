/* It is very possible for O(N) code to run faster than O(1) code for speicific
   inputs.
   For this reason, we drop the constants in runtime. An algorithm that one
   might have described as O(2N) is actually O(N).
   
   Many people resist doing this. They will see code that has two (non-nested)
   for loops and continue this O(2N). They think they're begin more "precise".
   They're not.
*/

// Min and Max 1
int min = Integer.MAX_VALUE;
int max = Integer.MIN_VALUE;
for (int x : array) {
    if (x < min) min = x;
    if (x > max) max = x;
}


// Min and Max 2
int min = Integer.MAX_VALUE;
int max = Integer.MIN_VALUE;
for (int x : array) {
    if (x < min) min = x;
}
for (int x : array) {
    if (x > max) max = x;
}

