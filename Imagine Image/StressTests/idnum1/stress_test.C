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

    /* you may want one or more readers! r*/
    PNMreader reader((char*) "../images/puddles.pnm");  // note: filename must be "../images/image_name.pnm"

    //PNMreader reader(argv[1]);
    Shrinker sr;
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    LRCombine lr4;
    LRCombine lr5;
    LRCombine lr6;
    TBCombine tb1;
    TBCombine tb2;
    TBCombine tb3;
    Blur br1;
    Blur br2;
    Blur br3;
    Subtract sb;
    Rotate rt1;
    Rotate rt2;
    Rotate rt3;
    Rotate rt4;
    Mirror mr;
    Grayscale gs;

    Color green(893, 672, 10, 64, 40);
    Color gold(893, 672, 255, 215, 0);

	mr.SetInput(reader.GetOutput());

	sb.SetInput(reader.GetOutput());
	sb.SetInput2(mr.GetOutput());

	sr.SetInput(sb.GetOutput());

	lr1.SetInput(sr.GetOutput());
	lr1.SetInput2(sr.GetOutput());

	tb1.SetInput(sb.GetOutput());
	tb1.SetInput2(lr1.GetOutput());
	
		
	tb1.SetInput(tb1.GetOutput());
	tb1.SetInput2(tb1.GetOutput());


    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tb1.GetOutput();

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
        writer.Write((char*) "3H.pnm");
    }
    Logger::Finalize();
}
