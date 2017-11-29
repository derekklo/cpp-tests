Problem Statement
    	
Maya is thinking of hosting a new kind of the Single Round Match (SRM). Maya has invited n members who are willing to participate as groups (members are numbered as 1, 2, ..., n). Each member will belong to exactly one group, and each group must have at least one member in it.

Each member i is willing to participate only if the group the member belongs to has exactly t[i] members in it. Maya wants to make sure that everyone participates, but she is unsure if that is possible. Help Maya figure out if there is a way to assign members to groups such that everyone is happy with the size of their group. If it is possible, return the number of groups needed. If it is impossible, return -1.

 
Definition
    	
Class:	GroupSRMDiv2
Method:	FindGroups
Parameters:	int[]
Returns:	int
Method signature:	int FindGroups(int[] t)
(be sure your method is public)
    
 
Constraints
-	t will contain between 1 and 500 elements, inclusive.
-	Each element in t will be between 1 and 500, inclusive.
 
Examples
0)	
    	
{1,1}
Returns: 2
1)	
    	
{1,2}
Returns: -1
2)	
    	
{2,2}
Returns: 1
3)	
    	
{2,2,3,3,3}
Returns: 2
4)	
    	
{3,3,2,2,2}
Returns: -1
5)	
    	
{2,3,2,3,2,3,2,1,1,2,2}
Returns: 6
