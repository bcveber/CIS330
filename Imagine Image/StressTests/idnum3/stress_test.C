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
    Shrinker shrinker;
    Shrinker shrinker2;
    LRCombine lrconcat;
    TBCombine tbconcat;
    TBCombine tbconcat2;
    Blender blender;
    blender.SetFactor(.75);
    Mirror mirror;
    Rotate rotate;
    Subtract subtract;
    Grayscale grayscale;

    mirror.SetInput(reader.GetOutput());

    lrconcat.SetInput(reader.GetOutput());
    lrconcat.SetInput2(mirror.GetOutput());

    tbconcat.SetInput(lrconcat.GetOutput());
    tbconcat.SetInput2(lrconcat.GetOutput());

    blender.SetInput(tbconcat.GetOutput());
    blender.SetInput2(tbconcat.GetOutput());

    grayscale.SetInput(blender.GetOutput());

    subtract.SetInput(blender.GetOutput());
    subtract.SetInput2(grayscale.GetOutput());

    shrinker.SetInput(subtract.GetOutput());
    shrinker2.SetInput(grayscale.GetOutput());

    tbconcat2.SetInput(shrinker.GetOutput());
    tbconcat2.SetInput2(shrinker2.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tbconcat2.GetOutput();

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
