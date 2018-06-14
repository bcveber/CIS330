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
    Grayscale gs;
    Shrinker sr;
    Shrinker sr2;
    Shrinker sr3;
    Shrinker sr4;
    TBCombine tb;
    TBCombine tb2;
    LRCombine lr; 
    LRCombine lr2; 
    Mirror mr;

    sr.SetInput(reader.GetOutput());
    sr2.SetInput(sr.GetOutput());
    sr3.SetInput(sr2.GetOutput());
    gs.SetInput(sr3.GetOutput());
    
    lr.SetInput(sr3.GetOutput());
    lr.SetInput2(gs.GetOutput());

    mr.SetInput(lr.GetOutput());

    tb.SetInput(mr.GetOutput());
    tb.SetInput2(lr.GetOutput());

    lr2.SetInput(tb.GetOutput());
    lr2.SetInput2(tb.GetOutput());
    
    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput2(lr2.GetOutput());



    /*   TODO: fill in fun stuff here   */


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
