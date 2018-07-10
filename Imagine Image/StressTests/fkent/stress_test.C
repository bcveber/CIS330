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

    Mirror m1;
    Mirror m2;
    Rotate r1;
    Rotate r2;
    Rotate r3;
    LRCombine lr1;
    LRCombine lr2;
    LRCombine lr3;
    LRCombine lr4;
    LRCombine lr5;
    TBCombine tb1;
    TBCombine tb2;
    TBCombine tb3;
    TBCombine tb4;
    Blur blr1;
    Blur blr2;
    Blur blr3;
    Blur blr4;
    Blur blr5;
    Blur blr6;
    Blur blr7;
    Blur blr8;
    Blur blr9;
    Blur blr10;
    Blur blr11;
    Blur blr12;
    Blur blr13;
    Blur blr14;
    Blur blr15;
    Blur blr16;
    Blur blr17;
    Blur blr18;
    Blur blr19;
    Blur blr20;
    Blur blr21;
    Blur blr22;
    Shrinker s1;
    Shrinker s2;
    Shrinker s3;
    Shrinker s4;
    Shrinker s5;
    Blender b;
    b.SetFactor(0.45);
    
	m1.SetInput(reader.GetOutput());
	r1.SetInput(m1.GetOutput());
	r2.SetInput(r1.GetOutput());
	m2.SetInput(r2.GetOutput());
	
	//extreme blurring
	blr1.SetInput(m2.GetOutput());
	blr2.SetInput(r2.GetOutput());
	blr3.SetInput(blr1.GetOutput());
	blr4.SetInput(blr2.GetOutput());
	blr5.SetInput(blr3.GetOutput());
	blr6.SetInput(blr4.GetOutput());
	blr7.SetInput(blr5.GetOutput());
	blr8.SetInput(blr6.GetOutput());
	blr9.SetInput(blr7.GetOutput());
	blr10.SetInput(blr8.GetOutput());
	blr11.SetInput(blr9.GetOutput());
	blr12.SetInput(blr10.GetOutput());
	blr13.SetInput(blr11.GetOutput());
	blr14.SetInput(blr12.GetOutput());
	blr15.SetInput(blr13.GetOutput());
	blr16.SetInput(blr14.GetOutput());
	blr17.SetInput(blr15.GetOutput());
	blr18.SetInput(blr16.GetOutput());
	blr19.SetInput(blr17.GetOutput());
	blr20.SetInput(blr18.GetOutput());
	blr21.SetInput(blr19.GetOutput());
	blr22.SetInput(blr20.GetOutput());

	lr1.SetInput(reader.GetOutput());
	lr1.SetInput2(m1.GetOutput());
	
	s1.SetInput(lr1.GetOutput());
	
	lr2.SetInput(blr21.GetOutput());
	lr2.SetInput2(blr22.GetOutput());
	
	s2.SetInput(lr2.GetOutput());
	
	tb1.SetInput(s1.GetOutput());
	tb1.SetInput2(s2.GetOutput());
	
	s3.SetInput(tb1.GetOutput());
	//
	
	lr3.SetInput(s3.GetOutput());
	lr3.SetInput2(s3.GetOutput());
	
	tb2.SetInput(lr3.GetOutput());
	tb2.SetInput2(lr3.GetOutput());
	
	s4.SetInput(tb2.GetOutput());
	
	lr4.SetInput(s4.GetOutput());
	lr4.SetInput2(s4.GetOutput());
   
    tb3.SetInput(lr4.GetOutput());
	tb3.SetInput2(lr4.GetOutput());
	
	s5.SetInput(tb3.GetOutput());
	
	lr5.SetInput(s5.GetOutput());
	lr5.SetInput2(s5.GetOutput());
   
    tb4.SetInput(lr5.GetOutput());
	tb4.SetInput2(lr5.GetOutput());
	
  	b.SetInput(reader.GetOutput());
    b.SetInput2(tb4.GetOutput());
    

    /* make "finalImage" be the image at the bottom of your pipeline */
    /* the code below will call update on finalImage                 */
    Image *finalImage = b.GetOutput();

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
