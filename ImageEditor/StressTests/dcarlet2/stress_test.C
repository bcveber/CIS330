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

    Transpose transpose;

    Shrinker shrinker;

    Blender blender;

    LRCombine lrcombine1;

    TBCombine tbcombine1;

    shrinker.SetInput(reader.GetOutput())

    transpose.SetInput(shrinker.GetOutput());

    lrcombine1.SetInput(transpose.GetOutput());
    lrcombine1.SetInput2(transpose.GetOutput());

    tbcombine1.SetInput(lrcombine1.GetOutput());
    tbcombine1.SetInput2(lrcombine1.GetOutput());

    blender.SetFactor(0.60);
    blender.SetInput(tbcombine1.GetOutput());
    blender.SetInput(reader.GetOutput());


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = some_filter.GetOutput();

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
