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
    PNMreader reader2("../images/hank.pnm");
    Mirror mr;
    Grayscale gray;
    LRCombine lr;
    TBCombine tb;
    LRCombine lr2;
    TBCombine tb2;
    Blur blur1;
    Blur blur2;
    Blur blur3;
    Blur blur4;
    Blur blur5;
    Blur blur6;
    Blur blur7;
    Blur blur8;
    Blur blurlast;
    LRCombine lr3;

    mr.SetInput(reader2.GetOutput());
    gray.SetInput(mr.GetOutput());
    lr.SetInput(gray.GetOutput());
    lr.SetInput2(gray.GetOutput());
    tb.SetInput(lr.GetOutput());
    tb.SetInput2(lr.GetOutput());
    lr2.SetInput(tb.GetOutput());
    lr2.SetInput2(tb.GetOutput());
    tb2.SetInput(lr2.GetOutput());
    tb2.SetInput2(lr2.GetOutput());
    blur1.SetInput(tb2.GetOutput());
    blur2.SetInput(blur1.GetOutput());
    blur3.SetInput(blur2.GetOutput());
    blur4.SetInput(blur3.GetOutput());
    blur5.SetInput(blur4.GetOutput());
    blur6.SetInput(blur5.GetOutput());
    blur7.SetInput(blur6.GetOutput());
    blur8.SetInput(blur7.GetOutput());
    blurlast.SetInput(blur8.GetOutput());
    lr3.SetInput(tb2.GetOutput());
    lr3.SetInput2(blurlast.GetOutput());




    /*   TODO: fill in fun stuff here   */


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = lr3.GetOutput(); // Should return a valid image

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
