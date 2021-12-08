import sys
import assembler as ASM

def main():

	running = True

	# ! WARNING !
	# If you recieve input in C++, you also have to consider EOF
	# (end-of-file) or else the tests will not pass in CodeGrade.
	# You won't notice this problem in the terminal on your local
	# computer.
	# In order to handle EOF in C++, you can use
	# 	std::cin.good()
	# to check if there is more to read in the input "buffer".
	# Use it to let the application leave the loop when CodeGrade
	# is finished giving input.
	while running: # and std::cin.good()	(for example)

		args = input("> ").split()

		if args[0] == "run" and len(args) > 1 and len(args) <= (ASM.REGISTER_SIZE+2):
			# Initialize registers, default all to 0
			# The all until last index is free to use by
			# the executable .asm files for storing values.
			# The last index is used as the 'next command index',
			# which is the next command to execute in the command list
			registers = [0] * ASM.REGISTER_SIZE

			# Read default values of registers in arguments (if any)
			for i in range(2, len(args)):
				registers[i-2] = int(args[i])

			# Initialize an empty command list
			#
			# The command list is a list of lists,
			# with each sub-list containing a "formatted command"
			# for easy reading and usage by indexing.
			#
			# Example of appearance:
			# [ ["MOV", "R0", "#3"], ["MOV", "R1", "#-15"], ["ADD", "R0", "R0", "R1"] ]
			commandList = []

			# Try to build the command list
			if not ASM.BuildCommandList(commandList, args[1]):
				print(f"Error: Could not open file '{args[1]}'. Try again.")

			else:
				# Execute all commands until 'next command index' is
				# out of range (of indices in the command list)
				while ASM.PeekNextCommandIndex(registers) < len(commandList):
					command = commandList[ASM.GetAndStepCommandIndex(registers)]
					
					if (command[0] == "MOV"):
						ASM.MOV(command, registers)

					elif (command[0] == "ADD"):
						ASM.ADD(command, registers)
					elif (command[0] == "SUB"):
						ASM.SUB(command, registers)
					
					elif (command[0] == "JEQ"):
						ASM.JEQ(command, registers)
					elif (command[0] == "JGT"):
						ASM.JGT(command, registers)
					elif (command[0] == "JLT"):
						ASM.JLT(command, registers)

				# Print all the registers, separated by a space
				reg_line = ""
				for i in range(ASM.REGISTER_SIZE):
					reg_line += str(registers[i]) + " "
				print(reg_line)

		elif args[0] == "exit":
			print("Goodbye!")
			running = False

		else: # args[0] is not "run" or "exit"
			print("Error: Invalid command or number of arguments. Try again.")
			print("---------------------------------------------------")
			print("Available commands:\n")
			print("> run program.asm (R0) (R1) ... (R7)")
			print("\tExecutes a program where 'program.asm' is the name")
			print("\tof the assembly file and (R0), (R1), ... (R7) is")
			print("\tthe optional initial values for the registers R0,")
			print("\tR1, ... R7.")
			print("> exit")
			print("\tCloses the application.")
			print("---------------------------------------------------")

if __name__ == "__main__":
	main()