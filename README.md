# ft_ls

I've recreated the ls shell command including the -R flag to recursively descend directories

I used a n-ary tree structure that allows my performance to be quicker than the system ls in many cases.

The node insertion for the children of each node is done with an O(n) time max, when n is the size of the list of children.

I ensured that all memory was freed during the sorting process, allowing my LS to descend enormous directories with no difficulty.
