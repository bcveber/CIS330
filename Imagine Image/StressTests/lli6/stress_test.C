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

    //Shrinker sr;  // this test should cause an exception
    //s.SetInput(reader.GetOutput());
    Shrinker s1;
    Shrinker s2;
    LRCombine lr1;
    LRCombine lr2;
    TBCombine tb1;
    TBCombine tb2;
    //Mirror mr;
    Grayscale gs;
    s1.SetInput(reader.GetOutput());

    lr1.SetInput(s1.GetOutput());
    lr1.SetInput2(s1.GetOutput());

    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(lr1.GetOutput());

    s2.SetInput(tb1.GetOutput());

    lr2.SetInput(s2.GetOutput());
    lr2.SetInput2(s1.GetOutput());

    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput2(lr1.GetOutput());

    //mr.SetInput(sb.GetOutput());

    gs.SetInput(tb2.GetOutput());



    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = gs.GetOutput();

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
