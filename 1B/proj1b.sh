#sources: 

#1) For how to use touch - https://stackoverflow.com/questions/17986615/one-command-to-create-a-directory-and-file-inside-it-linux-commad

#include <stdio.h>

		    #note -- this code assumes that all assuming that access is all there, 		    #i.e. no sudo needed (sudo would be needed for many, I can change if 		    needed). 

cd /        	    #changes current directory to root directory
mkdir Dir1 Dir2     #make the 1st and 2nd directory


cd Dir2     	    #go to 2nd directory to create File2
touch File2         #create File2
chmod 640 File2     #640 permission for File2

cd /    	    #go back to root

cd Dir1    	    #go to first directory to create File1
touch File1         #create File1 with touch command
chmod 400 File1     #400 permission for File1

mkdir Dir3          #make Dir3 within Dir1
cd Dir3 	    #go to dir3 to make Dir4 inside it

mkdir Dir4     	    #make dir4 within Dir3
cd Dir4		    #go to Dir4 to put files in
touch File3    	    #create File3
chmod 200 File3     #200 permission for file3
touch File4         #create File4
chmod 666 File4     #666 permission for file4

#Apply permissions to folders at the end since we are done editing/adding to them
#could not apply many of the changes/additions if we were to do this as we went along the script
cd ../    	    #go back to Dir3
chmod 750 Dir4      #750 permission for Dir4
cd ../		    #go back to Dir 1
chmod 000 Dir3 	    #000 permission for Dir3
cd /		    #go back to root directory
chmod 770 Dir1      #770 permission for Dir1
chmod 775 Dir2      #775 permission for Dir2
