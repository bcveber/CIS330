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

    PNMreader reader("../images/deschutes.pnm");  // note: filename must be "../images/image_name.pnm"
	 Color white(601,396, 255, 255, 255);
	 Color gray(601,396, 130, 130, 130);
	 Color blueish(601,396, 6, 100, 190);
	 Subtract sub;
	 Grayscale gs;
	 Subtract sub2;
	 Subtract sub3;
	 Subtract sub4;

	 static Blur* bprev = new Blur();
	 bprev->SetInput(reader.GetOutput());
	 //Blur bprev;
	 //bprev.SetInput(reader.GetOutput());

	 for (int i=0; i<50; i++) {
		 // this will go out of scope at each iteration, so we must put it on the heap
		 // it should be freed outside the student modifiable section, so.. this will leak
		 Blur* bnext = new Blur();

		 bnext->SetInput(bprev->GetOutput());
		 bprev = bnext;
	 }
	 Image* blurred = bprev->GetOutput();


	 gs.SetInput(blurred);

	 sub.SetInput(white.GetOutput());
	 sub.SetInput2(gs.GetOutput());

	 sub4.SetInput(sub.GetOutput());
	 sub4.SetInput2(gray.GetOutput());

	 sub2.SetInput(blueish.GetOutput());
	 sub2.SetInput2(sub4.GetOutput());
	 Image* colorInverse = sub2.GetOutput();
	 
	 sub3.SetInput(reader.GetOutput());
	 sub3.SetInput2(sub2.GetOutput());



    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
	 Image *finalImage = sub3.GetOutput();

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
