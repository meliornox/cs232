#!/bin/sh
# Theodore Bigelow
# This script file tests the states of computers in the Unix Lab 
#     at Calvin College.
# CS232 Project 2, Spring 2017
# Assignment description can be found at
#     https://cs.calvin.edu/courses/cs/232/assignments/2/index.html
#
# In order for this script to work, first add an ssh key as follows:
#   $ ssh-keygen -t rsa -b 2048
# Press enter three times for a key without password, or
#   press enter and then enter a password twice to use a password
# This script uses a password-less script.
#
# Used stackoverflow.com for help with command usage
#     thegeekstuff.com for elif
#     superuser.com for users and number of users

# Make variable for file with the computer names in it that we're reading from
infile="computers.txt"
# Make variable for file that will store the names of open computers
outfile="open.txt"
# Make variables that store a pattern to check against so we can determine
#     whether a machine is off or in Windows or a junk name
off="No route to host"
windows="Connection timed out"
junk="Could not resolve hostname"

# Put lines from the input file into a variable
lines=`cat $infile`

# Delete the file listing open computers if it already exists
if [ -f $outfile ] ; then
    rm $outfile
fi

# Loop for every line in the file, storing the current line as a variable
for line in $lines ; do
	# Make the bash ssh into the computer whose name is the current line
	# When sshed into the other computer, list the users on that computer.
	# Put the error from the first line in error.txt
	# put the output of the second into output.txt
	
	# -n must be used when it is run in the background, like we're doing
	# -o enables use of:
	#     StrictHostKeyChecking would display the servers public key if we left 
	#         it on
	#     ConnectTimeout sets a number of seconds after which the ssh will fail,
	#         in this situation this will happen when the machine is in Windows.
	#         If we had another OS on here, like Mac, we could not check if we
	#         were in Windows or Mac with a timer.
    ssh -n -o StrictHostKeyChecking=no -o ConnectTimeout=5 $line 'users' 2> error.txt 1> output.txt

    # Put the error and output of the previous line in their own variables.
	#     sh doesn't like to put line output in variables directly, so we do it
	#     like this.
    read error < error.txt
    read output < output.txt

    # Sidenote- #6 in the Plan of Action and the line stating that we must list
	# the state of each computer for the assignment conflicted, I went with the
	# more involved side. In order to just list the computers that are free and
	# in Linux delete the next four lines of code. The computers that aren't in
	# Windows, aren't off, and don't have users logged in are stored in a file.
	
	# If the string we specified in off up at the top of the file is in the error
	#     from ssh, we know the computer is off
    if echo "$error" | grep -q "$off"; then
        echo "$line is off"
    # If the string we specified in windows up at the top of the file is in the
	#     error from ssh, we know the computer is in windows
    elif echo "$error" | grep -q "$windows"; then
        echo "$line is in Windows"
    # If error is empty (-z) (we don't use -a here since the buffer will be
	#     blank on success and that will be written to the file, so it will always
	#     exist) and output exists and isn't empty (-a and -z) we know the 
	#     computer is on, in Linux, and has no users logged on.
    elif [ -z "$error" -a -z "$output" ]; then
        echo "$line is open and in Linux"
    # Store the output in the file specified at the top of the page
        echo "$line" >> $outfile
    # If the string we specified in junk up at the top of the file is in the
	#     error from ssh, we know the computer name is not valid
    elif echo "$error" | grep -q "$junk"; then
        echo "$line is not a computer name"
    # The only other option is that there are users logged on to a computer 
	#     that is on and in Linux.
    else
        echo "$line is in Linux but has users logged into it"
    fi
done