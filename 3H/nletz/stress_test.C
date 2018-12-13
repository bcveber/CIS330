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
    PNMreader reader("../images/hank.pnm");  // note: filename must be "../images/image_name.pnm"

    LRCombine lrcombine1;
    LRCombine lrcombine2;
    LRCombine lrcombine3;
    LRCombine lrcombine4;

    lrcombine1.SetInput(reader.GetOutput());
    lrcombine1.SetInput2(reader.GetOutput());
    lrcombine2.SetInput(reader.GetOutput());
    lrcombine2.SetInput2(reader.GetOutput());
    lrcombine3.SetInput(reader.GetOutput());
    lrcombine3.SetInput2(reader.GetOutput());
    lrcombine4.SetInput(reader.GetOutput());
    lrcombine4.SetInput2(reader.GetOutput());

    TBCombine tbcombine1;
    TBCombine tbcombine2;

    tbcombine1.SetInput(lrcombine1.GetOutput());
    tbcombine1.SetInput2(lrcombine2.GetOutput());

    tbcombine2.SetInput(lrcombine3.GetOutput());
    tbcombine2.SetInput2(lrcombine4.GetOutput());

    LRCombine lrcombine5;

    lrcombine5.SetInput(tbcombine1.GetOutput());
    lrcombine5.SetInput2(tbcombine2.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = lrcombine5.GetOutput();

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
