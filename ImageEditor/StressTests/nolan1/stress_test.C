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

    //TEST for color function
    //The output should somewhat resemble the united states flag

    Color redcolor(1786, 1344, 200, 0, 0);
    Color bluecolor(1786, 1344, 0, 0, 200);
    Color blackcolor(1786, 1344, 0, 0, 0);
    Color whitecolor(1786, 1344, 255, 255, 255);
    Shrinker shrinkerls;
    Shrinker shrinkerstar;
    Shrinker shrinkerRED;
    Shrinker shrinkerBLUE;
    Shrinker shrinkerWHITE;
    Shrinker shrinkerstripe;
    Shrinker shrinkerbw;
    LRCombine lrcombinebw;
    LRCombine lrcombinewb;
    LRCombine lrcombinestriper;
    LRCombine lrcombinestripew;
    LRCombine lrcombinelongstripe;
    LRCombine lrcombiness;
    LRCombine lrcombinestar;
    TBCombine tbcombinebw;
    TBCombine tbcombinestripe;
    TBCombine tbcombinefinal;
    TBCombine tbcombiness;

    shrinkerRED.SetInput(redcolor.GetOutput());
    shrinkerBLUE.SetInput(bluecolor.GetOutput());
    shrinkerWHITE.SetInput(whitecolor.GetOutput());

    lrcombinebw.SetInput(shrinkerBLUE.GetOutput());
    lrcombinebw.SetInput2(shrinkerWHITE.GetOutput());
    lrcombinewb.SetInput(shrinkerWHITE.GetOutput());
    lrcombinewb.SetInput2(shrinkerBLUE.GetOutput());

    lrcombinestriper.SetInput(shrinkerRED.GetOutput());
    lrcombinestriper.SetInput2(shrinkerRED.GetOutput());
    lrcombinestripew.SetInput(shrinkerWHITE.GetOutput());
    lrcombinestripew.SetInput2(shrinkerWHITE.GetOutput());

    lrcombinelongstripe.SetInput(tbcombinestripe.GetOutput());
    lrcombinelongstripe.SetInput2(tbcombinestripe.GetOutput());

    tbcombinestripe.SetInput(lrcombinestriper.GetOutput());
    tbcombinestripe.SetInput2(lrcombinestripew.GetOutput());

    tbcombinebw.SetInput(lrcombinebw.GetOutput());
    tbcombinebw.SetInput2(lrcombinewb.GetOutput());

    shrinkerstripe.SetInput(tbcombinestripe.GetOutput());
    shrinkerbw.SetInput(tbcombinebw.GetOutput());
    shrinkerls.SetInput(lrcombinelongstripe.GetOutput());

    lrcombinestar.SetInput(shrinkerbw.GetOutput());
    lrcombinestar.SetInput2(shrinkerbw.GetOutput());
    tbcombiness.SetInput(lrcombinestar.GetOutput());
    tbcombiness.SetInput2(lrcombinestar.GetOutput());

    shrinkerstar.SetInput(tbcombiness.GetOutput());

    lrcombiness.SetInput(shrinkerstar.GetOutput());
    lrcombiness.SetInput2(shrinkerstripe.GetOutput());

    tbcombinefinal.SetInput(lrcombiness.GetOutput());
    tbcombinefinal.SetInput2(shrinkerls.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tbcombinefinal.GetOutput();

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
