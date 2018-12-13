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
	
	 // note: filename must be "../images/image_name.pnm"
    PNMreader tux("../images/tux.pnm");  
    PNMreader gnu("../images/gnu.pnm");

	 Color gnuVPad(691, 124, 255, 255, 255);
	 Color tuxVPad(525, 127, 255, 255, 255);
	 Color tuxHPad(83, 692, 255, 255, 255);
	 Color gnu1VPad(691, 1, 255, 255, 255); //dang odd dimensions..
	 Color gnu1HPad(1, 692, 255, 255, 255);
	 Color tux1HPad(1, 692, 255, 255, 255);

	 Color pow2HPad(166, 1024, 255, 255, 255);
	 Color pow2VPad(692, 166, 255, 255, 255);
	 //Color 1HPad(525, 1, 255, 255, 255);
	 Color fullWhite(691, 691, 255, 255, 255);

	 TBCombine gnuPadTop;
	 TBCombine gnuPadTop2;
	 TBCombine gnuPadTop3;
	 TBCombine gnuPadBottom;
	 TBCombine gnuPadBottom2;
	 LRCombine gnuPadRight;
	 LRCombine gnuPadRight2;
	 LRCombine gnuPadLeft;
	 LRCombine gnuPadLeft2;

	 TBCombine tuxPadTop;
	 TBCombine tuxPadTop2;
	 TBCombine tuxPadBottom;
	 TBCombine tuxPadBottom2;
	 LRCombine tuxPadLeft;
	 LRCombine tuxPadLeft2;
	 LRCombine tuxPadRight;
	 LRCombine tuxPadRight2;
	 LRCombine tuxEvenH;

	 Subtract gnuTux;
	 Subtract gnuTuxInvert;

	 gnuPadTop.SetInput(gnu1VPad.GetOutput());
	 gnuPadTop.SetInput2(gnu.GetOutput());
	 gnuPadTop2.SetInput(gnuVPad.GetOutput());
	 gnuPadTop2.SetInput2(gnuPadTop.GetOutput());
	 gnuPadBottom.SetInput(gnuPadTop2.GetOutput());
	 gnuPadBottom.SetInput2(gnuVPad.GetOutput());

	 gnuPadRight.SetInput(gnuPadBottom.GetOutput());
	 gnuPadRight.SetInput2(gnu1HPad.GetOutput());
	 Image* squareGnu = gnuPadRight.GetOutput();
	 
	 gnuPadBottom2.SetInput(squareGnu);
	 gnuPadBottom2.SetInput2(pow2VPad.GetOutput());
	 gnuPadTop3.SetInput(pow2VPad.GetOutput());
	 gnuPadTop3.SetInput2(gnuPadBottom2.GetOutput());

	 gnuPadRight2.SetInput(gnuPadTop3.GetOutput());
	 gnuPadRight2.SetInput2(pow2HPad.GetOutput());
	 gnuPadLeft2.SetInput(pow2HPad.GetOutput());
	 gnuPadLeft2.SetInput2(gnuPadRight2.GetOutput());
	 Image* squareGnu2 = gnuPadLeft2.GetOutput();


	 tuxPadTop.SetInput(tuxVPad.GetOutput());
	 tuxPadTop.SetInput2(tux.GetOutput());
	 tuxPadBottom.SetInput(tuxPadTop.GetOutput());
	 tuxPadBottom.SetInput2(tuxVPad.GetOutput());
	 
	 tuxEvenH.SetInput(tuxPadBottom.GetOutput());
	 tuxEvenH.SetInput2(tux1HPad.GetOutput());
	 tuxPadLeft.SetInput(tuxHPad.GetOutput());
	 tuxPadLeft.SetInput2(tuxEvenH.GetOutput());
	 tuxPadRight.SetInput(tuxPadLeft.GetOutput());
	 tuxPadRight.SetInput2(tuxHPad.GetOutput());
	 Image* squareTux = tuxPadRight.GetOutput();

	 tuxPadBottom2.SetInput(squareTux);
	 tuxPadBottom2.SetInput2(pow2VPad.GetOutput());
	 tuxPadTop2.SetInput(pow2VPad.GetOutput());
	 tuxPadTop2.SetInput2(tuxPadBottom2.GetOutput());

	 tuxPadRight2.SetInput(tuxPadTop2.GetOutput());
	 tuxPadRight2.SetInput2(pow2HPad.GetOutput());
	 tuxPadLeft2.SetInput(pow2HPad.GetOutput());
	 tuxPadLeft2.SetInput2(tuxPadRight2.GetOutput());
	 Image* squareTux2 = tuxPadLeft2.GetOutput();

	 gnuTux.SetInput2(squareGnu2);
	 gnuTux.SetInput(squareTux2);
	 Image* daemon = gnuTux.GetOutput(); // now that's just disturbing

	 /*
	 static int iters=0;
	 struct Func {
		 static Image* func(Image* inp, int* iters) {
			 Shrinker* sh = new Shrinker();
			 TBCombine* tb = new TBCombine();
			 sh->SetInput(inp);
			 *iters = *iters+1;
			 std::cerr << *iters << std::endl;
			 if (*iters < 5) {
			 	tb->SetInput(func(sh->GetOutput(), iters));
			 	std::cerr << "setting input1" << std::endl;
			}
			else {
				tb->SetInput2(inp);
			 	std::cerr << "setting input2" << std::endl;
				return tb->GetOutput();
			}
		 }
	 };
	 */
	 Image *finalImage = daemon;

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
