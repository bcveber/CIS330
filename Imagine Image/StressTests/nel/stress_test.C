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
    PNMreader reader1("../images/puddles.pnm");
    PNMreader reader2("../images/hank.pnm");
    PNMreader reader3("../images/tux.pnm");
    PNMreader reader4("../images/question_marks.pnm");

    Shrinker s;
    LRCombine lr1;
    LRCombine lr2;
    TBCombine tb1;
    Mirror mr1;
    Rotate r1;
    Rotate r2;
    Subtract sub1;
    Grayscale gr1;
    Blur br1;
    Blur br2;

    s.SetInput(reader2.GetOutput());
    s.SetInput2(reader4.GetOutput());

    mr1.SetInput(s.GetOutput());
    
    lr1.SetInput(mr1.GetOutput());

    lr1.SetInput(s.GetOutput());
    
    gr1.SetInput(reader2.GetOutput());

    lr2.SetInput2(gr1.GetOutput());


    br2.SetInput(reader3.GetOutput());

    sub1.SetInput(br2.GetOutput());
    sub1.SetInput2(reader1.GetOutput());

    r1.SetInput(sub1.GetOutput());
    r2.SetInput(r1.GetOutput());





    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = r2.GetOutput();

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
