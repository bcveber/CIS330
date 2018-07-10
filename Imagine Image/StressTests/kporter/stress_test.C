#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>
#include <logging.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cerr;
using std::endl;
using std::ofstream;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <username>" << endl;
        exit(EXIT_FAILURE);
    }

    char event[1024];
    sprintf(event, "Entered program from %s\n", argv[1]);
    Logger::LogEvent(event);



    /* ================================ */
    /* START STUDENT MODIFIABLE SECTION */
    /* ================================ */

    /* you may want one or more readers! */
    PNMreader reader("../images/question_marks.pnm");  // note: filename must be "../images/image_name.pnm"


    //Make 9 Shrinkers
	Shrinker s1;
	Shrinker s2;
	Shrinker s3;
	Shrinker s4;
	Shrinker s5;
	Shrinker s6;
	Shrinker s7;
	Shrinker s8;
	Shrinker s9;

    //Set Shrinkers output in descending order, with s1 taking reader
	s1.SetInput(reader.GetOutput()); //Output size will be 178 x 176
	s2.SetInput(s1.GetOutput()); //Output size will be 89 x 88
	s3.SetInput(s2.GetOutput()); //Output size will be 44 x 44
	s4.SetInput(s3.GetOutput()); //Output size will be 22 x 22
	s5.SetInput(s4.GetOutput()); //Output size will be 11 x 11
	s6.SetInput(s5.GetOutput()); //Output size should be 5 x 5
	s7.SetInput(s6.GetOutput()); //Output size should be 2 x 2
	s8.SetInput(s7.GetOutput()); //Output size should be 1 x 1
	s9.SetInput(s8.GetOutput()); //Output size should be 0 x 0
				     //Should either throw a catchable error
				     //or safely produce 0x0 image

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = s9.GetOutput();

    /* ================================ */
    /*  END STUDENT MODIFIABLE SECTION  */
    /* ================================ */



    try
    {
        finalImage->Update();
    }
    catch (DataFlowException &)
    {
        ofstream ofile("my_exception");
        if (ofile.fail())
        {
             cerr << "Something is wrong ... can't open my_exception"
                  << " for opening" << endl;
             exit(EXIT_FAILURE);
        }
        ofile << "Exception found!" << endl;
        exit(EXIT_SUCCESS);
    }

    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");

    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
