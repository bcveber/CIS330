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
    PNMreader reader("../images/gnu.pnm");  // note: filename must be "../images/image_name.pnm"

    Shrinker shrinker1;
    Shrinker shrinker2;
    Shrinker shrinker3;
    LRCombine lrcombine1;
    LRCombine lrcombine2;
    LRCombine lrcombine3;
    TBCombine tbcombine1;
    TBCombine tbcombine2;
    TBCombine tbcombine3;
    TBCombine tbcombine4;

    shrinker1.SetInput(reader.GetOutput());

    lrcombine1.SetInput(shrinker1.GetOutput());
    lrcombine1.SetInput2(shrinker1.GetOutput());

    tbcombine1.SetInput(lrcombine1.GetOutput());
    tbcombine1.SetInput2(lrcombine1.GetOutput());

    shrinker2.SetInput(tbcombine1.GetOutput());

    lrcombine2.SetInput(shrinker2.GetOutput());
    lrcombine2.SetInput2(shrinker2.GetOutput());

    tbcombine2.SetInput(lrcombine1.GetOutput());
    tbcombine2.SetInput2(lrcombine1.GetOutput());
	
    tbcombine3.SetInput(tbcombine2.GetOutput());
    tbcombine3.SetInput2(tbcombine2.GetOutput());

    tbcombine4.SetInput(tbcombine3.GetOutput());
    tbcombine4.SetInput2(tbcombine3.GetOutput());

    shrinker3.SetInput(tbcombine4.GetOutput());

    lrcombine3.SetInput(shrinker3.GetOutput());
    lrcombine3.SetInput2(shrinker3.GetOutput());

    Image *finalImage = lrcombine3.GetOutput();

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
