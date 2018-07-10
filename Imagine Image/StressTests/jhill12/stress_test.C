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
    PNMreader reader("../images/hank.pnm");  // note: filename must be "../images/image_name.pnm"
    //PNMreader2 reader("../images/hank.pnm")	
    
    /*   TODO: fill in fun stuff here   */
    LRCombine lrconcat;
    TBCombine tbconcat;
    Shrinker shrinker;

	LRCombine lrconcat1;
    TBCombine tbconcat1;
    Shrinker shrinker1;

	LRCombine lrconcat2;
    TBCombine tbconcat2;
    Shrinker shrinker2;

	LRCombine lrconcat3;
    TBCombine tbconcat3;
    Shrinker  shrinker3;

	LRCombine lrconcat4;
    TBCombine tbconcat4;
    Shrinker shrinker4; 

	lrconcat.SetInput(reader.GetOutput());
	lrconcat.SetInput2(reader.GetOutput());
	tbconcat.SetInput(lrconcat.GetOutput());
	tbconcat.SetInput2(lrconcat.GetOutput());
	shrinker.SetInput(tbconcat.GetOutput());
	
	lrconcat1.SetInput(shrinker.GetOutput());
	lrconcat1.SetInput2(shrinker.GetOutput());
	tbconcat1.SetInput(lrconcat.GetOutput());
	tbconcat1.SetInput2(lrconcat.GetOutput());
	shrinker1.SetInput(tbconcat.GetOutput());

	lrconcat2.SetInput(shrinker1.GetOutput());
	lrconcat2.SetInput2(shrinker1.GetOutput());
	tbconcat2.SetInput(lrconcat1.GetOutput());
	tbconcat2.SetInput2(lrconcat1.GetOutput());
	shrinker2.SetInput(tbconcat1.GetOutput());

	lrconcat3.SetInput(shrinker2.GetOutput());
	lrconcat3.SetInput2(shrinker2.GetOutput());
	tbconcat3.SetInput(lrconcat2.GetOutput());
	tbconcat3.SetInput2(lrconcat2.GetOutput());
	//shrinker3.SetInput(tbconcat2.GetOutput());

	lrconcat4.SetInput(tbconcat3.GetOutput());
	lrconcat4.SetInput2(tbconcat3.GetOutput());
	tbconcat4.SetInput(lrconcat3.GetOutput());
	tbconcat4.SetInput2(lrconcat3.GetOutput());
	//shrinker4.SetInput(tbconcat3.GetOutput());

	
	/*for(int i =0; i<4; i++){	
	
	lrconcat.SetInput(shrinker.GetOutput());
	lrconcat.SetInput2(tbconcat.GetOutput());
	tbconcat.SetInput(lrconcat.GetOutput());
	tbconcat.SetInput2(lrconcat.GetOutput());
	shrinker.SetInput(tbconcat.GetOutput());
	}
	*/
	
    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = tbconcat4.GetOutput();

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
