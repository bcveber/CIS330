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
    PNMreader reader("../images/puddles.pnm");  
	
	Shrinker s;
	LRCombine lr1;
	LRCombine lr2;
	TBCombine tb;
	TBCombine tb2;
	Mirror mr;
	Mirror mr2;
	Rotate rt1;
	Rotate rt2;
	Rotate rt3;
	Subtract sb;
	Blur blr;
	Color gold(1786, 2688, 255, 215, 0);
	Color green(3572, 2688, 10, 64, 40);
	
	mr.SetInput(reader.GetOutput());
	rt1.SetInput(reader.GetOutput());
	tb.SetInput(mr.GetOutput());
	tb.SetInput2(rt1.GetOutput());
	lr1.SetInput(tb.GetOutput());
	lr1.SetInput2(gold.GetOutput());
	mr2.SetInput(lr1.GetOutput());
	sb.SetInput(mr2.GetOutput());
	sb.SetInput(green.GetOutput());
	lr2.SetInput(mr2.GetOutput());
	lr2.SetInput2(sb.GetOutput());
	rt2.SetInput(lr2.GetOutput());
	rt3.SetInput(rt2.GetOutput());
	tb2.SetInput(lr2.GetOutput());
	tb2.SetInput2(rt3.GetOutput());
	blr.SetInput(tb2.GetOutput());
	s.SetInput(blr.GetOutput());  // this test creates a valid image

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = s.GetOutput();

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
