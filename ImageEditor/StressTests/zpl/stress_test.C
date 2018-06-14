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

    /* Read in an image file */
    PNMreader reader("../images/deschutes.pnm");  // note: filename must be "../images/image_name.pnm"

    /* Repeatedly shrink the image, probably beyond smallest possible size */
    Shrinker sr1;
    Shrinker sr2;
    Shrinker sr3;
    Shrinker sr4;
    Shrinker sr5;
    Shrinker sr6;
    Shrinker sr7;
    Shrinker sr8;
    Shrinker sr9;
    Shrinker sr10;
    Shrinker sr11;
    Shrinker sr12;
    Shrinker sr13;
    Shrinker sr14;
    Shrinker sr15;
    Shrinker sr16;

    sr1.SetInput(reader.GetOutput());
    sr2.SetInput(sr1.GetOutput());
    sr3.SetInput(sr2.GetOutput());
    sr4.SetInput(sr3.GetOutput());
    sr5.SetInput(sr4.GetOutput());
    sr6.SetInput(sr5.GetOutput());
    sr7.SetInput(sr6.GetOutput());
    sr8.SetInput(sr7.GetOutput());
    sr9.SetInput(sr8.GetOutput());
    sr10.SetInput(sr9.GetOutput());
    sr11.SetInput(sr10.GetOutput());
    sr12.SetInput(sr11.GetOutput());
    sr13.SetInput(sr12.GetOutput());
    sr14.SetInput(sr13.GetOutput());
    sr15.SetInput(sr14.GetOutput());
    sr16.SetInput(sr15.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = sr16.GetOutput();

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
