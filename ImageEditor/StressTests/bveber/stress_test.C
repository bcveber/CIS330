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
    PNMreader reader("../images/tux.pnm");  // note: filename must be "../images/image_name.pnm"


    /*   TODO: fill in fun stuff here   */
    Shrinker s0, s1, s2;
    s0.SetInput(reader.GetOutput());
    s1.SetInput(s0.GetOutput());
    s2.SetInput(s1.GetOutput());

    LRCombine lr0, lr1, lr2;
    lr0.SetInput(s2.GetOutput());
    lr0.SetInput2(s2.GetOutput());

    lr1.SetInput(lr0.GetOutput());
    lr1.SetInput2(lr0.GetOutput());

    lr2.SetInput(lr1.GetOutput());
    lr2.SetInput2(lr1.GetOutput());

    TBCombine tb0, tb1, tb2;
    tb0.SetInput(lr2.GetOutput());
    tb0.SetInput2(lr2.GetOutput());

    tb1.SetInput(tb0.GetOutput());
    tb1.SetInput2(tb0.GetOutput());

    tb2.SetInput(tb1.GetOutput());
    tb2.SetInput2(tb1.GetOutput());


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb2.GetOutput();

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
