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

    PNMreader reader((char*) "../images/hank.pnm"); // "../images/hank.pnm"
    Rotate rotate1;
    Rotate rotate2;
    Rotate rotate3;
    Rotate rotate4;
    TBCombine tb1;
    TBCombine tb2;
    TBCombine tb3;
    LRCombine lr1;
    LRCombine lr2;
    Color green(484, 321, 50, 100, 50);
    Color yellow(484, 321, 210, 210, 0);

    rotate1.SetInput(reader.GetOutput());
    rotate2.SetInput(rotate1.GetOutput());

    tb1.SetInput(reader.GetOutput());
    tb1.SetInput2(rotate2.GetOutput());

    tb2.SetInput(green.GetOutput());
    tb2.SetInput2(rotate1.GetOutput());

    tb3.SetInput(tb2.GetOutput());
    tb3.SetInput2(yellow.GetOutput());

    lr1.SetInput(tb1.GetOutput());
    lr1.SetInput2(tb3.GetOutput());

    rotate3.SetInput(tb3.GetOutput());
    rotate4.SetInput(rotate3.GetOutput());

    lr2.SetInput(rotate4.GetOutput());
    lr2.SetInput2(lr1.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = lr2.GetOutput();

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
