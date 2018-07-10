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
    PNMreader reader("../images/puddles.pnm");  // note: filename must be "../images/image_name.pnm
    int readWidth = 1786; 
    int readHeight= 1344;
    int index = 0;
    Color r(readWidth, readHeight, 0, 200, 200);
    Subtract onlyR;
    LRCombine lr1;
    Color oppOrange(readWidth, readHeight, 0, 102, 255);
    Subtract makeOrange;
    LRCombine lr2;
    TBCombine tb1;
    Color oppYellow(readWidth, readHeight, 0, 0, 31);
    Subtract makeYellow;
    LRCombine lr3;
    TBCombine tb2;
    Color oppGreen(readWidth, readHeight, 200, 0, 200);
    Subtract makeGreen;
    LRCombine lr4;
    TBCombine tb3;
    Color oppBlue(readWidth, readHeight, 200, 200, 0);
    Subtract makeBlue;
    LRCombine lr5;
    TBCombine tb4;
    Color oppPurple(readWidth, readHeight, 127, 255, 127);
    Subtract makePurple;
    LRCombine lr6;
    TBCombine tb5;

    onlyR.SetInput(reader.GetOutput());
    onlyR.SetInput2(r.GetOutput());
    lr1.SetInput(onlyR.GetOutput());
    lr1.SetInput2(r.GetOutput());

    makeOrange.SetInput(onlyR.GetOutput());
    makeOrange.SetInput2(oppOrange.GetOutput());
    lr2.SetInput(makeOrange.GetOutput());
    lr2.SetInput2(oppOrange.GetOutput());
    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput(lr2.GetOutput());

    makeYellow.SetInput(oppYellow.GetOutput());
    makeYellow.SetInput2(oppOrange.GetOutput());
    lr3.SetInput(makeYellow.GetOutput());
    lr3.SetInput2(oppYellow.GetOutput());
    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput(lr3.GetOutput());

    makeGreen.SetInput2(oppGreen.GetOutput());
    lr4.SetInput(makeGreen.GetOutput());
    lr4.SetInput2(oppGreen.GetOutput());
    tb3.SetInput(lr3.GetOutput());
    tb3.SetInput(lr4.GetOutput());

    makeBlue.SetInput(oppBlue.GetOutput());
    makeBlue.SetInput2(oppBlue.GetOutput());
    lr5.SetInput(makeBlue.GetOutput());
    lr5.SetInput2(oppBlue.GetOutput());
    tb4.SetInput(lr4.GetOutput());
    tb4.SetInput(lr5.GetOutput());

    makePurple.SetInput(oppPurple.GetOutput());
    makePurple.SetInput2(oppPurple.GetOutput());
    lr6.SetInput(makePurple.GetOutput());
    lr6.SetInput2(oppPurple.GetOutput());
    tb5.SetInput(lr5.GetOutput());
    tb5.SetInput(lr6.GetOutput());

    //tb5.GetOutput() -> Update();

    /*   TODO: fill in fun stuff here   */


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb5.GetOutput();

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
