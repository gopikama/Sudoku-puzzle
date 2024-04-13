import ast
import numpy as np
import time
from memory_profiler import memory_usage

# this class represents each node (which is a sudoku configuration) during the program run
class SudokuState:
    def __init__(self, configuration, gn, fn, parent):
        #instance of the sudoku board during the game
        self.configuration=configuration
        # g(n) value of the sudoku board instance
        self.gn=gn
        # f(n) value of the sudoku board instance
        self.fn=fn
        # parent of the sudoku board instance
        self.parent=parent
        #children of the node
        self.children=[]

class Sudoku:                              
    #find first unfilled position and the number of possible values that can occupy that cell to generate successors
    def generate_successor_configuration(self,sudoku_board):
        # Define the possible values
        possible_values = set([1, 2, 3, 4, 5, 6, 7, 8, 9])
        successors=[]

        #where is a numpy function which returns position where values are equal to given value(0 in this case)
        first_zero_position = np.where(sudoku_board == 0)
        zero_row = first_zero_position[0][0]
        zero_column = first_zero_position[1][0]

        row_values = set(sudoku_board[zero_row, :])
        col_values = set(sudoku_board[:, zero_column])
        subgrid_values = set(sudoku_board[(zero_row//3)*3:(zero_row//3)*3+3, (zero_column//3)*3:(zero_column//3)*3+3].flatten())

        # Combine the values in the same row, column, and subgrid
        combined_values = row_values.union(col_values, subgrid_values)
                    
        # Subtract the combined values from the possible values- works like set theory
        remaining_values = possible_values - combined_values
        
        for value in remaining_values:
            new_sudoku=sudoku_board.copy()
            new_sudoku[zero_row][zero_column]=value
            # DEBUG STATEMENT print(new_sudoku[zero_row][zero_column],"replaced value at",zero_row," ",zero_column)
            # DEBUG STATEMENT print(new_sudoku)
            successors.append(np.array(new_sudoku))
      
                      
        return successors
    
    #the heuristic used is candidate reduction   
    def heuristic(self,sudoku_board):
        sum_remaining = 0
    
        # Define the possible values
        possible_values = set([1, 2, 3, 4, 5, 6, 7, 8, 9])
    
        # Iterate over each cell in the matrix
        for i in range(9):
            for j in range(9):
                # Skip if the cell already has a value
                if sudoku_board[i][j] == 0:
                   
                    # Find values in the same row
                    row_values = set(sudoku_board[i, :])
                    
                    # Find values in the same column
                    col_values = set(sudoku_board[:, j])
                    
                    # Find values in the same subgrid
                    subgrid_values = set(sudoku_board[(i//3)*3:(i//3)*3+3, (j//3)*3:(j//3)*3+3].flatten())
                    
                    # Combine the values in the same row, column, and subgrid
                    combined_values = row_values.union(col_values, subgrid_values)
                    
                    # Subtract the combined values from the possible values
                    remaining_values = possible_values - combined_values
                    
                    # Add the size of the remaining values to the sum, 
                    # That is, these many values can still be tried. All possibilities for each unfilled cell is filled up
                    sum_remaining += len(remaining_values)
                

        return sum_remaining
  
    def main(self):
        # DEBUG STATEMENT initilaizing a sudoku board with 9*9 size all zeroes,datatype : integer
        # DEBUG STATEMENT initial_sudoku_board = np.zeros((9,9),dtype=int)

        # Prompt the user to enter the 2D array as a string
        array_str = input("Enter the 2D array representing sudoku board: \n")
        array_2d = eval(array_str)
        
        # Converting to a numpy array
        initial_sudoku_board = np.array(array_2d,dtype=int)
        print("Entered sudoku board is:\n")
        print(initial_sudoku_board)


        
        # DEBUG STATEMENT print("heuritstic",self.heuristic(initial_sudoku_board))

        #initializing the first node and adding to open list to initiate A*final algorithm
        gn=0
        parent_node=None
        child=None
        node=SudokuState(initial_sudoku_board,gn,self.heuristic(initial_sudoku_board)+gn,parent_node)
        
        open_list=[]
        closed_list=[]
        open_list.append(node)

        best_node=node
        best_path=[]
        successors=[]
        
        # performance parameters
        no_of_nodes_generated=0
        no_of_nodes_expanded=0
        start_time = time.time()

        # A* final algorithm
        while(self.heuristic(best_node.configuration)!=0):
            if open_list:
                # sort open list and get the first node from open list with the best f(n) value to be expanded
                open_list.sort(key=lambda x:x.fn)
                # DEBUG STATEMENT print("Open List:", [node.fn for node in open_list])  
                # DEBUG STATEMENT print("Open List:", [node.fn for node in open_list])
                best_node=open_list[0]
                # DEBUG STATEMENT print("This node expanded",best_node.configuration)
                # DEBUG STATEMENT print("This node heuristic\n",self.heuristic(best_node.configuration))
                best_path.append(best_node)
                closed_list.append(open_list.pop(0))

                if(self.heuristic(best_node.configuration)==0):
                    print("breaking here??")
                    break  
                else:
                    #each time we generate successors gn for successors will be incremented by one and successor list is cleared
                    # DEBUG STATEMENT print(" successors!")
                    no_of_nodes_expanded+=1
                    successors.clear()
                    gn=gn+1

                    # generating successors of the node if its not the final configuration node
                    successor_configuration=self.generate_successor_configuration((best_node.configuration)) 
                    for successor_config in successor_configuration:    
                        successor=SudokuState(successor_config,gn,self.heuristic(successor_config)+gn,best_node)
                        successors.append(successor)
                        no_of_nodes_generated+=1
                    best_node.children.extend(successors)    

                    for successor in successors:
                        #check in open if this successor is already present but not processed
                        in_open_list=False
                        for node in open_list:
                            if(np.array_equal(node.configuration,successor.configuration)):
                                in_open_list=True
                                OLD=node
                                successors.remove(successor) 
                                successors.append(OLD)
                                if(successor.gn<OLD.gn):
                                    OLD.parent=best_node
                                    OLD.gn=successor.gn 
                                    OLD.fn=OLD.gn+ self.heuritic(OLD.configuration)
                        #checking if successor is present in closed list   
                        if(not(in_open_list)):
                            for node in closed_list:
                                if(np.array_equal(node.configuration,successor.configuration)):
                                    OLD=node
                                    # DEBUG STATEMENT successors.remove(successor)
                                    successors.append(OLD) 
                                    if(successor.gn<OLD.gn):
                                        OLD.parent=best_node
                                        OLD.gn=successor.gn
                                        OLD.fn=OLD.gn+ self.heuritic(OLD.configuration)
                                    stack = [OLD]
                                    # propogating g(n) value to children
                                    while stack:
                                        current_node = stack.pop()
                                        for child in current_node.children: 
                                            if child.gn > current_node.gn + 1:
                                                child.gn = current_node.gn + 1
                                                child.fn = child.gn + self.heuristic(child.configuration)
                                                stack.append(child)
                    
                    open_list.extend(successors)
                    open_list.sort(key=lambda x:x.fn)
                    
            else:
                print("Failure, not a valid input")
                break    
        end_time = time.time()

        # displaying results
        print("\n Path to last node:")
        for config in best_path:
            print(config.configuration)
        
        print("\n Last node:")
        print(best_node.configuration)
        
        execution_time = (end_time - start_time)


        total_memory_usage = memory_usage(-1, interval=1)
        

        effective_branching_factor=no_of_nodes_generated/gn

        # Create the table
        parameters = [
        ["Execution time (ET)", f"{execution_time} second"],
        ["No of nodes generated (NG)", f"{no_of_nodes_generated}"],
        ["No of nodes expanded (NE)", f"{no_of_nodes_expanded}"],
        ["Depth of the tree (D)", f"{gn}"],
        ["Effective branching factor (b*)", f"{effective_branching_factor}"],
        ["Memory usage:",f"{total_memory_usage[0]}"]
        ]
  
        # Print the table
        for row in parameters:
            print("{:<40} {:<30}".format(*row))
                              
if __name__=="__main__":
    sudoku=Sudoku()
    sudoku.main() 
   
     