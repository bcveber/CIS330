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
    PNMreader reader("../images/question_marks.pnm");  // note: filename must be "../images/image_name.pnm"

    Color green(357,352,0,128,0);
    Color gold(357,352,255,215,0);
    Color orange(357,352,255,165,0);
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    LRCombine lr4;
    LRCombine lr5;
    LRCombine lr6;
    Mirror mr1;
    Mirror mr2;
    TBCombine tb1;
    TBCombine tb2;
    TBCombine tb3;
    Shrinker shrinker;

    //middle graph
    lr1.SetInput(reader.GetOutput());
    lr1.SetInput2(green.GetOutput());
    mr1.SetInput(reader.GetOutput());
    lr2.SetInput(green.GetOutput());
    lr2.SetInput2(mr1.GetOutput());
    tb1.SetInput(lr1.GetOutput());
    tb1.SetInput2(lr2.GetOutput());
    shrinker.SetInput(tb1.GetOutput());
    //first row
    lr3.SetInput(gold.GetOutput());
    lr3.SetInput2(reader.GetOutput());
    lr4.SetInput(lr3.GetOutput());
    lr4.SetInput2(orange.GetOutput());
    //second row
    lr5.SetInput(mr1.GetOutput());
    lr5.SetInput2(shrinker.GetOutput());
    lr6.SetInput(lr5.GetOutput());
    lr6.SetInput2(reader.GetOutput());
    //first + second row = combine rows
    tb2.SetInput(lr4.GetOutput());
    tb2.SetInput2(lr6.GetOutput());
    //third row
    mr2.SetInput(lr4.GetOutput());
    // combine rows + thrid row
    tb3.SetInput(tb2.GetOutput());
    tb3.SetInput2(mr2.GetOutput());
    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb3.GetOutput();

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
