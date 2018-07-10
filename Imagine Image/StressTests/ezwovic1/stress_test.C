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

    PNMreader reader("../images/hank.pnm");  // note: filename must be "../images/image_name.pnm"

	 static Blur* bprev = new Blur();
	 bprev->SetInput(reader.GetOutput());
	 static LRCombine* lrprev = new LRCombine();
	 lrprev->SetInput(reader.GetOutput());

	 for (int i=0; i<50; i++) {
		 // this will go out of scope at each iteration, so we must put it on the heap
		 // it should be freed outside the student modifiable section, so.. this will leak
		 Blur* bnext = new Blur();

		 if (i%10==0) {
			 LRCombine* lrnext = new LRCombine();
			 lrprev->SetInput2(bprev->GetOutput());
			 lrnext->SetInput(lrprev->GetOutput());
			 lrprev = lrnext;
		 }
		 bnext->SetInput(bprev->GetOutput());
		 bprev = bnext;
	 }
	 lrprev->SetInput2(bprev->GetOutput());

	 // photobooth gone wrong?
	 Image *finalImage = lrprev->GetOutput();

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
