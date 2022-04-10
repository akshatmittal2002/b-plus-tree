# B-Plus-Tree
Implementation of `B-Plus Tree` in C++.<br>
B+ tree will have two parameters: `d` and `t`<br>
- A leaf or `data node` has capacity to store `2d` records. Each leaf node should contain `at least d` records, except when there is only one leaf node in the B+ tree.
- A non-leaf or `index node` has capacity to store `2t+1` keys. Each non-leaf node should contain `at least t` keys, except when there is only one non-leaf node in the B+ tree.

### Input:
`Line 1` contains the value of `d` for the tree.<br>
`Line 2` contains the value of `t` for the tree.<br>
`Line 3 onwards` descibes various operation to be performed on given tree.<br>
&emsp;`1` : Insert new value<br>
&emsp;`2` : Give the output<br>
&emsp;`3` : Exit<br>

### Output:
For operation `2`, output will be one line containing following things separated by `space` and terminated by `\n`:<br>

- Number of Index Nodes
- Number of Data Nodes
- Content of Root Node
