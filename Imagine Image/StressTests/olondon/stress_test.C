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
    Color greeny(400, 400,34,177,76);
	PNMwriter writer;
	
	TBCombine tb1;
	TBCombine tb2;
	TBCombine tb3;
	TBCombine tb4;
	TBCombine tb5;
	TBCombine tb6;	
	
	LRCombine lr1;
	LRCombine lr2;
	LRCombine lr3;
	LRCombine lr4;
	LRCombine lr5;
	LRCombine lr6;
	
	Shrinker s1;
	Shrinker s2;
	Shrinker s3;
	Shrinker s4;
	Shrinker s5;
	Shrinker s6;
	
	tb1.SetInput(greeny.GetOutput());
	tb1.SetInput2(greeny.GetOutput());
	lr1.SetInput(tb1.GetOutput());
	lr1.SetInput2(tb1.GetOutput());//2x2
	
	tb2.SetInput(lr1.GetOutput());
	tb2.SetInput2(lr1.GetOutput());
	lr2.SetInput(tb2.GetOutput());
	lr2.SetInput2(tb2.GetOutput());//4x4
	
	tb3.SetInput(lr2.GetOutput());
	tb3.SetInput2(lr2.GetOutput());
	lr3.SetInput(tb3.GetOutput());
	lr3.SetInput2(tb3.GetOutput());//8x8
	
	tb4.SetInput(lr3.GetOutput());
	tb4.SetInput2(lr3.GetOutput());
	lr4.SetInput(tb4.GetOutput());
	lr4.SetInput2(tb4.GetOutput());//16x16 (6400^2)
	
	tb5.SetInput(lr4.GetOutput());
	tb5.SetInput2(lr4.GetOutput());
	lr5.SetInput(tb5.GetOutput());
	lr5.SetInput2(tb5.GetOutput());//32x32 (12800^2)
	
	tb6.SetInput(lr5.GetOutput());
	tb6.SetInput2(lr5.GetOutput());
	lr6.SetInput(tb6.GetOutput());
	lr6.SetInput2(tb6.GetOutput());//64 (12800^2)
	
	s1.SetInput(lr6.GetOutput());//32
	s2.SetInput(s1.GetOutput());//16
	s3.SetInput(s2.GetOutput());//8
	s4.SetInput(s3.GetOutput());//4
	s5.SetInput(s4.GetOutput());//2
	s6.SetInput(s5.GetOutput());//1
	
    /*   TODO: fill in fun stuff here   */
	

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = s6.GetOutput();

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
