find_missing_ints
=================

This is an interview problem that Naichen used, and I thought I would try to implement it, just to see how feasible it is.

The interview question is thus:

You are given a very large file full of integers, one per line. These integers are shuffled but are within a specified range. Find out if there are any numbers missing in that range, and if so, provide one missing number. Provide the Big-O notation for your solution.

This implements the solution he's looking for O(N). If it was searching a file with a range of 0..MAX_UINT, it would use about 2GB of ram to store the bit array.
