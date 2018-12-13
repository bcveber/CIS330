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
    PNMreader reader("../images/tux.pnm");  // note: filename must be "../images/image_name.pnm"

    Shrinker s1;
    TBCombine tb1;
    LRCombine lr1;

    s1.SetInput(reader.GetOutput());
	tb1.SetInput(s1.GetOutput());
	tb1.SetInput2(s1.GetOutput());
	lr1.SetInput(tb1.GetOutput());
	lr1.SetInput2(tb1.GetOutput());

	Shrinker s2;
    TBCombine tb2;
    LRCombine lr2;

    s2.SetInput(lr1.GetOutput());
	tb2.SetInput(s2.GetOutput());
	tb2.SetInput2(s2.GetOutput());
	lr2.SetInput(tb2.GetOutput());
	lr2.SetInput2(tb2.GetOutput());

	Shrinker s3;
    TBCombine tb3;
    LRCombine lr3;

    s3.SetInput(lr2.GetOutput());
	tb3.SetInput(s3.GetOutput());
	tb3.SetInput2(s3.GetOutput());
	lr3.SetInput(tb3.GetOutput());
	lr3.SetInput2(tb3.GetOutput());

	Shrinker s4;
    TBCombine tb4;
    LRCombine lr4;

    s4.SetInput(lr3.GetOutput());
	tb4.SetInput(s4.GetOutput());
	tb4.SetInput2(s4.GetOutput());
	lr4.SetInput(tb4.GetOutput());
	lr4.SetInput2(tb4.GetOutput());

	Shrinker s5;
    TBCombine tb5;
    LRCombine lr5;

    s5.SetInput(lr4.GetOutput());
	tb5.SetInput(s5.GetOutput());
	tb5.SetInput2(s5.GetOutput());
	lr5.SetInput(tb5.GetOutput());
	lr5.SetInput2(tb5.GetOutput());

	Shrinker s6;
    TBCombine tb6;
    LRCombine lr6;

    s6.SetInput(lr5.GetOutput());
	tb6.SetInput(s6.GetOutput());
	tb6.SetInput2(s6.GetOutput());
	lr6.SetInput(tb6.GetOutput());
	lr6.SetInput2(tb6.GetOutput());

    // Comment from Andy:
    //   I think the use of blender here is OK because this should be an exception
    //   rather producing a checksum
	Blender  blender;
    blender.SetFactor(0.5);

    blender.SetInput(lr6.GetOutput());
    blender.SetInput2(reader.GetOutput());

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = blender.GetOutput();

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
