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
    PNMreader reader("../images/puddles.pnm");  // note: filename must be "../images/image_name.pnm"


    /*   TODO: fill in fun stuff here   */
    TBCombine tb;
    TBCombine tb2;
    LRCombine lr;
    LRCombine lr2;
    tb.SetInput(reader.GetOutput());
    Color blue(1786, 675, 0, 191, 255);
    Color black(1786, 681, 0, 0, 0);
    tb2.SetInput(black.GetOutput());
    tb2.SetInput2(blue.GetOutput());
    tb.SetInput2(tb2.GetOutput());
    Color green(900, 2700, 10, 64, 40);
    Color yellow(902, 2700, 255, 255, 0);
    lr2.SetInput(yellow.GetOutput());
    lr2.SetInput2(green.GetOutput());
    lr.SetInput(tb.GetOutput());
    lr.SetInput2(lr2.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = lr.GetOutput();

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
