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


    Shrinker shrinker1;
    Shrinker shrinker2;
    Shrinker shrinker3;


    TBCombine tbcombine1;
    TBCombine tbcombine2;
    TBCombine tbcombine3;


    shrinker1.SetInput(reader.GetOutput());


    tbcombine1.SetInput(shrinker1.GetOutput());
    tbcombine1.SetInput2(shrinker1.GetOutput());

    shrinker2.SetInput(tbcombine1.GetOutput());


    tbcombine2.SetInput(shrinker2.GetOutput());
    tbcombine2.SetInput2(shrinker2.GetOutput());

    shrinker3.SetInput(tbcombine2.GetOutput());

    tbcombine3.SetInput(shrinker3.GetOutput());
    tbcombine3.SetInput2(shrinker3.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tbcombine3.GetOutput();

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
