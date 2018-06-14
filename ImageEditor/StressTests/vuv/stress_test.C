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

int main(int argc,char *argv[])
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
    PNMreader reader1("../images/deschutes.pnm");
    PNMreader reader2("../images/gnu.pnm");
    PNMreader reader3("../images/hank.pnm");
    PNMreader reader4("../images/question_marks.pnm");
    //PNMreader reader5("../images/tux.pnm");
    /*   TODO: fill in fun stuff here   */
    Shrinker shr1;
    Shrinker shr2;
    LRCombine lrcom1;
    LRCombine lrcom2;
    TBCombine tbcom1;
    TBCombine tbcom2;
    // shrinking puddles and deschutes to shr1,shr2
    shr1.SetInput(reader.GetOutput());
    shr2.SetInput(reader1.GetOutput());
    // lrcombining half of puddles and half of deschutes
    lrcom1.SetInput(shr1.GetOutput());
    lrcom1.SetInput2(shr2.GetOutput());
    // 2nd lrcombining gnu and lrcom2, 
    // this should cause exception, Heighs must match
   	lrcom2.SetInput(reader2.GetOutput());
   	lrcom2.SetInput2(lrcom1.GetOutput());
   	// tbcombining lrcom2 and hank
   	// exceptions here too, since lrcom2 didnt work, no input1
   	tbcom1.SetInput(lrcom2.GetOutput());
   	tbcom1.SetInput2(reader3.GetOutput());
   	// 2nd tbcombining question_marks and tbcom1
   	// exceptions again, no input2, since tbcom1 didnt work
   	tbcom2.SetInput(reader4.GetOutput());
   	tbcom2.SetInput2(tbcom1.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tbcom2.GetOutput();

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

    /*
    CheckSum cs;
    cs.SetInput(finalImage);
    cs.OutputCheckSum("my_checksum");
    */
    if (argc == 3)
    {
        PNMwriter writer;
        writer.SetInput(finalImage);
        writer.Write("3H.pnm");
    }
    Logger::Finalize();
}
